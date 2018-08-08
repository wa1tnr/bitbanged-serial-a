// Wed Aug  1 04:18:10 UTC 2018
// main.c
#include "atmel_start.h"
#include "gpio_local.h"

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
	while (1) {
            flicker_LED();
            short_timer();
	}
}

int main(void) {
    atmel_start_init();
    // SystemInit(); // recent work used this rather than atmel_start_init()
    // SysTick_Config(4000000);
    init_act_LED();
    nmain();
    while (1) {
    }
}
