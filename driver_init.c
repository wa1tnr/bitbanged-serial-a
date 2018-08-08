/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_init.h"
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hal_init.h>

#include <hpl_rtc_base.h>

struct timer_descriptor TIMER_0;
struct timer_descriptor TIMER_1;
struct timer_descriptor TIMER_2;

/**
 * \brief Timer initialization function
 *
 * Enables Timer peripheral, clocks and initializes Timer driver
 */
static void TIMER_0_init(void)
{
	hri_mclk_set_APBAMASK_RTC_bit(MCLK);
	timer_init(&TIMER_0, RTC, _rtc_get_timer());
}

void delay_driver_init(void)
{
	delay_init(SysTick);
}

/**
 * \brief Timer initialization function
 *
 * Enables Timer peripheral, clocks and initializes Timer driver
 */
static void TIMER_1_init(void)
{
	hri_mclk_set_APBAMASK_TC0_bit(MCLK);
	hri_gclk_write_PCHCTRL_reg(GCLK, TC0_GCLK_ID, CONF_GCLK_TC0_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));

	timer_init(&TIMER_1, TC0, _tc_get_timer());
}

/**
 * \brief Timer initialization function
 *
 * Enables Timer peripheral, clocks and initializes Timer driver
 */
static void TIMER_2_init(void)
{
	hri_mclk_set_APBAMASK_TC1_bit(MCLK);
	hri_gclk_write_PCHCTRL_reg(GCLK, TC1_GCLK_ID, CONF_GCLK_TC1_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));

	timer_init(&TIMER_2, TC1, _tc_get_timer());
}

void system_init(void)
{
	init_mcu();

	// GPIO on PA14

	// Set pin direction to input
	gpio_set_pin_direction(D4, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(D4,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_UP);

	gpio_set_pin_function(D4, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA18

	// Set pin direction to output
	gpio_set_pin_direction(D6, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(D6,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(D6, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA19

	// Set pin direction to output
	gpio_set_pin_direction(D9, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(D9,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(D9, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA21

	// Set pin direction to output
	gpio_set_pin_direction(D11, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(D11,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	gpio_set_pin_function(D11, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA23

	// Set pin direction to output
	gpio_set_pin_direction(D13, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(D13,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(D13, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB03

	// Set pin direction to output
	gpio_set_pin_direction(PB03, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(PB03,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(PB03, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB16

	// Set pin direction to output
	gpio_set_pin_direction(PB16, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(PB16,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	gpio_set_pin_function(PB16, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB17

	// Set pin direction to input
	gpio_set_pin_direction(PB17, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(PB17,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_UP);

	gpio_set_pin_function(PB17, GPIO_PIN_FUNCTION_OFF);

	TIMER_0_init();

	delay_driver_init();

	TIMER_1_init();
	TIMER_2_init();
}
