#include <nrf.h>
#include <nrf_delay.h>


static uint16_t pwm_seq[8] = {23,30,10,46,100,50,40,100};

static void my_setup_pwm(int pin_no)
{
    NRF_PWM0->PSEL.OUT[0] = (pin_no << PWM_PSEL_OUT_PIN_Pos) |
                            (PWM_PSEL_OUT_CONNECT_Connected <<
                                                     PWM_PSEL_OUT_CONNECT_Pos);
    //NRF_PWM0->PSEL.OUT[1] = (28 << PWM_PSEL_OUT_PIN_Pos) |
    //                        (PWM_PSEL_OUT_CONNECT_Connected <<
    //                                                 PWM_PSEL_OUT_CONNECT_Pos);
    NRF_PWM0->ENABLE      = (PWM_ENABLE_ENABLE_Enabled << PWM_ENABLE_ENABLE_Pos);
    NRF_PWM0->MODE        = (PWM_MODE_UPDOWN_Up << PWM_MODE_UPDOWN_Pos);
    NRF_PWM0->PRESCALER   = (PWM_PRESCALER_PRESCALER_DIV_16 <<
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

    my_setup_pwm(27);

    while(1) {
        NRF_PWM0->TASKS_SEQSTART[0] = 1;
        nrf_delay_ms(10);
        NRF_PWM0->TASKS_NEXTSTEP = 1;
        nrf_delay_ms(5);
        NRF_PWM0->TASKS_STOP = 1;
        nrf_delay_ms(5);
    }

}

