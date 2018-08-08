// Wed Aug  1 04:18:10 UTC 2018
// main.c
#include "atmel_start.h"
#include "gpio_local.h"
#include "driver_init.h"

/*
int main(void)
{
	// Initializes MCU, drivers and middleware //
	atmel_start_init();

	// Replace with your application code //
	while (1) {
	}
}
*/

void pins_setup(void) {
    // serial pins
    //    input
/*
    PORT->Group[1].DIRCLR.reg = (uint32_t)(1 << 17); // rx is input // PB17
    //    output
    PORT->Group[1].DIRSET.reg = (uint32_t)(1 << 16); // tx output   // PB16

    // gpio outputs
    PORT->Group[0].DIRSET.reg |= (uint32_t)(1 << 18); // PA18 //  1  6 pinmode  // D6
    PORT->Group[0].DIRSET.reg |= (uint32_t)(1 << 23); // PA23 //  1 13 pinmode  // D13
*/
    PORT->Group[0].DIRSET.reg  = (uint32_t)(1 << 21); // PA21 //  1 11 pinmode  // D11
/*

    // gpio raise pin to 3.3v
    PORT->Group[0].OUTSET.reg |= (uint32_t)(1 << 18); // PA18 //  1  6 pinwrite // D6
    PORT->Group[0].OUTSET.reg |= (uint32_t)(1 << 21); // PA21 //  1 11 pinwrite // D11
    PORT->Group[0].OUTSET.reg |= (uint32_t)(1 << 23); // PA23 //  1 13 pinwrite // D13

    // gpio lower pin to Ground
    PORT->Group[0].OUTCLR.reg =  (uint32_t)(1 << 18); // PA18 //  0  6 pinwrite // D6
    PORT->Group[0].OUTCLR.reg |= (uint32_t)(1 << 21); // PA21 //  0 11 pinwrite // D11
    PORT->Group[0].OUTCLR.reg =  (uint32_t)(1 << 23); // PA23 //  0 13 pinwrite // D13

#undef PIN_D11_INPUT
#ifdef PIN_D11_INPUT
    // gpio input pins
    PORT->Group[0].DIRCLR.reg  = (uint32_t)(1 << 21); // PA21 //  0 11 pinmode  // D11
#endif // #ifdef PIN_D11_INPUT

    // gpio output pin toggles
    PORT->Group[0].OUTTGL.reg = (uint32_t)(1 << 18); // PA18 //  D6 toggle
    PORT->Group[0].OUTTGL.reg = (uint32_t)(1 << 21); // PA21 // D11 toggle
    PORT->Group[0].OUTTGL.reg = (uint32_t)(1 << 23); // PA23 // D13 toggle
    // Group[1] means PORTB rather than PORTA (which is Group[0])
    PORT->Group[1].OUTTGL.reg = (uint32_t)(1 <<  3); // PB03 //  D8 toggle  // NEOPIX
*/
}

void uSec(void) {
    for (volatile int i = 1; i < 2; i++) { // needs calibration
        // nothing
    }
}

void short_timer(void) { // human blinkie timescale
    uint32_t on_time  = 2140111222; // it's 2147 something ;)
    for(int j = 2; j>0; j--) {
        for(on_time =       2140112; on_time > 0; on_time--) { // 21.4 million
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
	// while (1) {
        for (int i=4; i>0; i--) { // blink a while then go into 3.5 MHz loop on D11
            flicker_LED();
            short_timer();
	}
        // fall-thru back to main();
}

int main(void) {
    // 660 kHz for a 1 uSec() iteration in the loop:
    // atmel_start_init();
    // system_init(); // driver_init.h
    // SystemInit(); // recent work used this rather than atmel_start_init()

    // test two: add just atmel_start_init():
    // atmel_start_init(); // brings in system_init();

    // test three: just SystemInit():

    // 48 MHz:
    SystemInit(); // recent work used this rather than atmel_start_init()
    pins_setup();

    // clock_init();
    // smaller SysTick means ticks come more rapidly
    // SysTick_Config(4000000);
    init_act_LED();

    nmain(); // has fall-thru now.

    while (1) {
        PORT->Group[0].OUTTGL.reg = (uint32_t)(1 << 21); // PA21 // D11 toggle
        // 3.5 MHz with no uSec loop
    }
}
