#include <nrf.h>
#include <nrf_delay.h>



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

    uint16_t pwm_seq[4] = {50,15,15,20};
    NRF_PWM0->PSEL.OUT[0] = (27 << PWM_PSEL_OUT_PIN_Pos) |
                            (PWM_PSEL_OUT_CONNECT_Connected <<
                                                     PWM_PSEL_OUT_CONNECT_Pos);
    NRF_PWM0->PSEL.OUT[1] = (28 << PWM_PSEL_OUT_PIN_Pos) |
                            (PWM_PSEL_OUT_CONNECT_Connected <<
                                                     PWM_PSEL_OUT_CONNECT_Pos);
    NRF_PWM0->ENABLE      = (PWM_ENABLE_ENABLE_Enabled << PWM_ENABLE_ENABLE_Pos);
    NRF_PWM0->MODE        = (PWM_MODE_UPDOWN_Up << PWM_MODE_UPDOWN_Pos);
    NRF_PWM0->PRESCALER   = (PWM_PRESCALER_PRESCALER_DIV_2 <<
                                                     PWM_PRESCALER_PRESCALER_Pos);
    NRF_PWM0->COUNTERTOP  = (100 << PWM_COUNTERTOP_COUNTERTOP_Pos); //1 msec
    NRF_PWM0->LOOP        = (PWM_LOOP_CNT_Disabled << PWM_LOOP_CNT_Pos);
    NRF_PWM0->DECODER   = (PWM_DECODER_LOAD_Individual << PWM_DECODER_LOAD_Pos) |
                          (PWM_DECODER_MODE_RefreshCount << PWM_DECODER_MODE_Pos);
    NRF_PWM0->SEQ[0].PTR  = ((uint32_t)(pwm_seq) << PWM_SEQ_PTR_PTR_Pos);
    NRF_PWM0->SEQ[0].CNT  = ((sizeof(pwm_seq) / sizeof(uint16_t)) <<
                                                     PWM_SEQ_CNT_CNT_Pos);
    NRF_PWM0->SEQ[0].REFRESH  = 0;
    NRF_PWM0->SEQ[0].ENDDELAY = 0;
    NRF_PWM0->TASKS_SEQSTART[0] = 1;

}

