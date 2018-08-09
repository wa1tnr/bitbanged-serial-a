// Thu Aug  9 06:56:02 UTC 2018
// main.c
// 8 MHz (measured) RC clock (as a guess)
// previous timestamp:
// Wed Aug  1 04:18:10 UTC 2018
#include "atmel_start.h"
#include "gpio_local.h"
#include "driver_init.h"
#include "driver_examples.h"
#include "clock_init.h"

/*
int main(void)
{
	// Initializes MCU, drivers and middleware //
	atmel_start_init();
}
*/

void pins_setup(void) {
    PORT->Group[0].DIRSET.reg  = (uint32_t)(1 << 21); // PA21 //  1 11 pinmode  // D11
}

void uSec(void) {
    for (volatile int i = 1; i < 2; i++) { // needs calibration
        // nothing
    }
}

void short_timer(void) { // human blinkie timescale
    uint32_t on_time  = 2140111222; // it's 2147 something ;)
    for(int j = 2; j>0; j--) {
        for(on_time =       214011; on_time > 0; on_time--) { // 21.4 million
            uSec();
        }
    }
}

void raise_LED_pins(void) { // multiple target boards
    raise_D13_feather(); // Feather M4 Express
}

void lower_LED_pins(void) {
    lower_D13_feather();
}

void blink_LED(void) {
    raise_LED_pins();
    short_timer();
    lower_LED_pins();
    short_timer();
}

void flicker_LED(void) {
    raise_LED_pins();
    short_timer();
    lower_LED_pins();
    short_timer();
}

void blinkLEDfast(void) {
    for(int i = 15; i > 0; i--) {
        blink_LED();
    }
}

void activity_LED_demo(void) {
    blinkLEDfast();
}

void long_long_timer(void) {
    for (int j=4; j>1; j--){
        for (int i=3; i>1; i--){
            short_timer();
        }
    }
}

void nmain(void) {
        raise_LED_pins();
        for (int i=4; i>0; i--) { // blink a while then go into 3.5 MHz loop on D11
            flicker_LED();
            short_timer();
	}
        // fall-thru back to main();
}

/*
void TC1_Handler(void){ // fires rarely, for counting overflows of time-ticker
    // TC1->COUNT32.INTFLAG.bit.OVF = 1; // to clear it
    PORT->Group[0].OUTTGL.reg = (uint32_t)(1 << 21); // PA21 // D11 toggle
}
*/

/*
void SysTick_Handler(void){
    PORT->Group[0].OUTTGL.reg = (uint32_t)(1 << 21); // PA21 // D11 toggle
}
*/

int main(void) {

/*
    // Nice triple, 8 MHZ:
    SystemCoreClockUpdate();
    SystemInit();
    pins_setup();
*/

    SystemCoreClockUpdate(); // might pull in 48 MHz
    SystemInit(); // recent work used this rather than atmel_start_init()
    pins_setup();

    // TIMER_1_example();
    // NVIC_EnableIRQ(TC1_IRQn);

    // SysTick_Config(2); // 1.7 MHz on toggle D11

    // nmain(); // has fall-thru now.

    // atmel_start_init();
    // system_init(); // driver_init.h



    // sytem_init() seemed a possible trouble spot and wasn't used earlier today (heh)
    // system_init(); // driver_init.c
    // NVIC_EnableIRQ(TC1_IRQn);


    // smaller SysTick means ticks come more rapidly
    // SysTick_Config(4000000);
    // init_act_LED();

    // nmain(); // has fall-thru now.

    // clock_init(); // very late in the game
    while (1) {
        PORT->Group[0].OUTTGL.reg = (uint32_t)(1 << 21); // PA21 // D11 toggle
        // 3.5 MHz with no uSec loop
    }
}
