#include <nrf.h>
#include <nrf_delay.h>
#include "diseqc_constants.h"

static unsigned char txbuffer[30];

static uint16_t pwm_seq[8] = {46,30,10,91,100,50,40,100};

int flag = 0;

static void my_setup_pwm(int pin_no)
{
    NRF_PWM0->PSEL.OUT[0] = (pin_no << PWM_PSEL_OUT_PIN_Pos) |
                            (PWM_PSEL_OUT_CONNECT_Connected <<
                                                     PWM_PSEL_OUT_CONNECT_Pos);
    //NRF_PWM0->PSEL.OUT[1] = (28 << PWM_PSEL_OUT_PIN_Pos) |
    //                        (PWM_PSEL_OUT_CONNECT_Connected <<
    //                                                 PWM_PSEL_OUT_CONNECT_Pos);
    NRF_PWM0->MODE        = (PWM_MODE_UPDOWN_Up << PWM_MODE_UPDOWN_Pos);
    NRF_PWM0->PRESCALER   = (PWM_PRESCALER_PRESCALER_DIV_8 <<
                                                     PWM_PRESCALER_PRESCALER_Pos);
    //NRF_PWM0->COUNTERTOP  = (100 << PWM_COUNTERTOP_COUNTERTOP_Pos); //1 msec
    NRF_PWM0->LOOP        = (PWM_LOOP_CNT_Disabled << PWM_LOOP_CNT_Pos);
    NRF_PWM0->DECODER   = (PWM_DECODER_LOAD_WaveForm << PWM_DECODER_LOAD_Pos) |
                          (PWM_DECODER_MODE_NextStep << PWM_DECODER_MODE_Pos);
    NRF_PWM0->SEQ[0].PTR  = ((uint32_t)(pwm_seq) << PWM_SEQ_PTR_PTR_Pos);
    NRF_PWM0->SEQ[0].CNT  = ((sizeof(pwm_seq) / sizeof(uint16_t)) <<
                                                     PWM_SEQ_CNT_CNT_Pos);
    NRF_PWM0->SEQ[0].REFRESH  = 0;
    NRF_PWM0->SEQ[0].ENDDELAY = 0;
}

static void enable_pwm()
{
    NRF_PWM0->ENABLE      = (PWM_ENABLE_ENABLE_Enabled << PWM_ENABLE_ENABLE_Pos);
}

static void turn_on_22khz()
{
    NRF_PWM0->TASKS_SEQSTART[0] = 1;
}

static void turn_off_22khz()
{
    NRF_PWM0->TASKS_NEXTSTEP = 1;
}

void wait_for_using_timer_interrupt(int i)
{
    NRF_TIMER0->CC[0] = i;
    NRF_TIMER0->TASKS_CLEAR = 1;
    NRF_TIMER0->TASKS_START = 1;

    flag = 0;
    while (flag == 0) __WFE(); 
}
int val0_5ms = 492;
int val1_0ms = 985;

void send_bit(char val)
{
    if (val) {
        turn_on_22khz();
        wait_for_using_timer_interrupt(val0_5ms); // 0.5 ms
        turn_off_22khz();
        wait_for_using_timer_interrupt(val1_0ms); // 1.0 ms
    }
    else {
        turn_on_22khz();
        wait_for_using_timer_interrupt(val1_0ms); // 986 is 1 ms
        turn_off_22khz();
        wait_for_using_timer_interrupt(val0_5ms); // 0.5 ms
    }
}

void send_byte(unsigned char val)
{
    int i;
    char parity = 1;
    char bit_to_send;
    for(i=0;i<8;i++) {
        bit_to_send = (val >> (7-i)) & 0x01;
        send_bit(bit_to_send);
        parity = parity ^ bit_to_send;
    }
    send_bit(parity);
}

void send_buffer(unsigned char *buffer, int length)
{
    int i;
    for(i=0;i<length;i++) {
        send_byte(buffer[i]);
    }
}


int main()
{

    //NRF_P0->PIN_CNF[27] = 0x00000003;


    //while(1) {
    //    nrf_delay_us(20);
    //    NRF_P0->OUTSET = (1 << 27);
    //    nrf_delay_ms(1);
    //    NRF_P0->OUTCLR = (1 << 27);
    //}


  //  NRF_PWM0->PSEL.OUT[0] = (1 << 27);
  //  NRF_PWM0->ENABLE = 1;
  //  NRF_PWM0->MODE = (PWM_MODE_UPDOWN_Up << PWM_MODE_UPDOWN_Pos);
  //  NRF_PWM0->PRESCALER = (PWM_PRESCALER_PRESCALER_DIV_1 << PWM_PRESCALER_PRESCALER_Pos);
  //  NRF_PWM0->COUNTERTOP = (16000 << PWM_COUNTERTOP_COUNTERTOP_Pos);
  //
  //  NRF_PWM0->TASKS_SEQSTART[0] = 1;

    NVIC_ClearPendingIRQ(TIMER0_IRQn);
    NVIC_EnableIRQ(TIMER0_IRQn);
    NRF_TIMER0->INTENSET = 0x00010000;
    NRF_TIMER0->PRESCALER = 4;
    NRF_CLOCK->TASKS_HFCLKSTART = 1;
    NRF_P0->PIN_CNF[11] = 0x000000C;

    my_setup_pwm(27);
    enable_pwm();

    NRF_TIMER0->TASKS_CLEAR = 1;
    NRF_TIMER0->TASKS_START = 1;

    int packetlength;
    int timeout_in_seconds = 5;
    txbuffer[0] = FRAMING_COMMAND_FROM_MASTER_NO_REPLY_REQUIRED_FIRST;
    //txbuffer[1] = ADDRESS_ANY_POSITIONER;
    txbuffer[1] = ADDRESS_POLAR_POSITIONER;
    txbuffer[2] = 0x69;
    txbuffer[3] = 0;
    txbuffer[4] = 0;
    txbuffer[5] = 0;
    packetlength = 4;

    while(1) {
        while(((NRF_P0->IN) >> 11) & 0x1);
        send_buffer(txbuffer, packetlength);
        nrf_delay_ms(100);
        while((((NRF_P0->IN) >> 11) & 0x1) == 0);
    }

}

void TIMER0_IRQHandler(void)
{
    if(NRF_TIMER0->EVENTS_COMPARE[0]) {
        NRF_TIMER0->EVENTS_COMPARE[0] = 0;
        NRF_TIMER0->TASKS_CLEAR = 0;
        NRF_TIMER0->TASKS_STOP = 0;
        flag = 1;
    }
}
