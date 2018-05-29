#include <nrf.h>
#include <nrf_delay.h>



int main()
{

    NRF_P0->PIN_CNF[27] = 0x00000003;


    while(1) {
        nrf_delay_us(20);
        NRF_P0->OUTSET = (1 << 27);
        nrf_delay_ms(1);
        NRF_P0->OUTCLR = (1 << 27);
    }
}

