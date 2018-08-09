#include "atmel_start.h"
#include "gpio_local.h"

// both pins 20 MHz measured.  D4 signal very weak though.

// #include "driver_init.h"
// #include "driver_examples.h"
// #include "clock_init.h"

// https://www.avrfreaks.net/forum/resolved-samd51-asf4start-clock-fail-debugger-hang

void ClockInit(void)
{
	// CONFIGURE FLASH MEMORY WAIT STATES
	//NVMCTRL->CTRLA.bit.RWS = 5; // 4WS allows up to 119 MHz, 5WS allows 120 MHz
	NVMCTRL->CTRLA.bit.AUTOWS = 1; // automatically determine the necessary wait states

	// CONFIGURE EXTERNAL 32K CRYSTAL OSCILLATOR
	OSC32KCTRL->XOSC32K.bit.CGM = 1; // control gain mode: 1 = standard/XT 2 = high-speed/HS
	OSC32KCTRL->XOSC32K.bit.STARTUP = 0; // oscillator startup time, 0 = 62 ms
	OSC32KCTRL->XOSC32K.bit.ONDEMAND = 0; // always run
	OSC32KCTRL->XOSC32K.bit.XTALEN = 1; // enable crystal driver circuit for XIN32/XOUT32 pins
	OSC32KCTRL->XOSC32K.bit.EN32K = 1; // enable the 32 kHz output clock
	OSC32KCTRL->XOSC32K.bit.ENABLE = 1;

	while (!OSC32KCTRL->STATUS.bit.XOSC32KRDY); // wait until crystal oscillator is stable and ready to be used as a clock source

	OSC32KCTRL->RTCCTRL.bit.RTCSEL = OSC32KCTRL_RTCCTRL_RTCSEL_XOSC32K_Val; // RTC should use the external 32K crystal

	// CONFIGURE MASTER CLOCK
	MCLK->CPUDIV.bit.DIV = 1; // use a divisor of 1 for the master clock

	// CONFIGURE PLL0
	OSCCTRL->Dpll[0].DPLLCTRLB.bit.REFCLK = 1; // use OSC32K as the PLL reference clock
	OSCCTRL->Dpll[0].DPLLRATIO.reg = (3<<16) + 3661; // multiply OSC32K by 3662.11 to get 120 MHz (actual multiplier is LDR + 1 + LDRFRAC/32)

	// errata: When using a low-frequency input clock on FDPLLn, several FDPLL unlocks may occur while the output
	// frequency is stable. Workaround: when using a low-frequency input clock on FDPLLn, enable the lock bypass
	// feature to avoid FDPLL unlocks.
	OSCCTRL->Dpll[0].DPLLCTRLB.bit.LBYPASS = 1; // CLK_DPLL0 output clock is always on, and not dependent on frequency lock
	OSCCTRL->Dpll[0].DPLLCTRLA.bit.ONDEMAND = 0; // always run
	OSCCTRL->Dpll[0].DPLLCTRLA.bit.ENABLE = 1;

	while (!OSCCTRL->Dpll[0].DPLLSTATUS.bit.LOCK) ; // no point in checking DPLLSTATUS.bit.CLKRDY, because LBYPASS is enabled

	// CONFIGURE CLOCK GENERATOR 0
	GCLK->GENCTRL[0].bit.SRC = 7; // use PLL0 as the input
	GCLK->GENCTRL[0].bit.DIV = 1; // divisor 1 for the input clock from the PLL
	GCLK->GENCTRL[0].bit.GENEN = 1;

	// do peripheral clock initialization here...
}


void pins_setup(void) {
    PORT->Group[0].DIRSET.reg  = (uint32_t)(1 << 21); // PA21 //  1 11 pinmode  // D11
    // PORT->Group[0].DIRSET.reg  = (uint32_t)(1 << 14);
    // toggle: // PORT->Group[0].OUTTGL.reg = (uint32_t)(1 << 21); // PA21 // D11 toggle
}


int main(void)
{
    pins_setup();
	ClockInit();

	// configure PA21 (board D11) as GCLK_IO[0] output of main clock generator, to confirm 120 MHz operation
	PORT->Group[GPIO_PORTA].DIRSET.reg = (1 << 14); // set pin as output
	PORT->Group[GPIO_PORTA].PINCFG[14].bit.PMUXEN = 1; // enable the peripheral mux for this pin
	PORT->Group[GPIO_PORTA].PMUX[(14>>1)].bit.PMUXE = MUX_PA14M_GCLK_IO0; // select the GCLK_IO0 peripheral function
	GCLK->GENCTRL[0].bit.OE = 1; // enable output from clock generator 0

/*
 175 #define PIN_PA14M_GCLK_IO0             _L_(14) // < \brief GCLK signal: IO0 on PA14 mux M 
 176 #define MUX_PA14M_GCLK_IO0             _L_(12)
 177 
 178 
 179 #define PINMUX_PA14M_GCLK_IO0      ((PIN_PA14M_GCLK_IO0 << 16) | MUX_PA14M_GCLK_IO0)
 180 #define PORT_PA14M_GCLK_IO0    (_UL_(1) << 14)
 181 #define PIN_PB22M_GCLK_IO0 
*/

/*
	// configure PB14 (board D5)  as GCLK_IO[0] output of main clock generator, to confirm 120 MHz operation
	PORT->Group[GPIO_PORTB].DIRSET.reg = (1 << 14); // set pin as output
	PORT->Group[GPIO_PORTB].PINCFG[14].bit.PMUXEN = 1; // enable the peripheral mux for this pin
	PORT->Group[GPIO_PORTB].PMUX[(14>>1)].bit.PMUXE = MUX_PB14M_GCLK_IO0; // select the GCLK_IO0 peripheral function
	GCLK->GENCTRL[0].bit.OE = 1; // enable output from clock generator 0
*/


	while (1)
	{
		// do something
            PORT->Group[0].OUTTGL.reg = (uint32_t)(1 << 21); // PA21 // D11 toggle
	}
}

/*  ********************** */
/*  ********************** */
/*  ********************** */
/*  ********************** */
/*  ********************** */
/*  ********************** */
/*  ********************** */
/*  ********************** */

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

/*
int main(void) {

//
    // Nice triple, 8 MHZ:
    SystemCoreClockUpdate();
    SystemInit();
    pins_setup();
//

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
*/
