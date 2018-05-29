#include <nrf.h>
#include <nrf_delay.h>


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
    char bit_to_send;
    for(i=0;i<8;i++) {
        bit_to_send = (val >> (7-i)) & 0x01;
        send_bit(bit_to_send);
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

    my_setup_pwm(27);
    enable_pwm();

    NRF_TIMER0->TASKS_CLEAR = 1;
    NRF_TIMER0->TASKS_START = 1;

    while(1) {
        send_byte(0xa2);
        nrf_delay_ms(100);
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
