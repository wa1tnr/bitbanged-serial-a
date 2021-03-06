/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef ATMEL_START_PINS_H_INCLUDED
#define ATMEL_START_PINS_H_INCLUDED

#include <hal_gpio.h>

// SAMD51 has 14 pin functions

#define GPIO_PIN_FUNCTION_A 0
#define GPIO_PIN_FUNCTION_B 1
#define GPIO_PIN_FUNCTION_C 2
#define GPIO_PIN_FUNCTION_D 3
#define GPIO_PIN_FUNCTION_E 4
#define GPIO_PIN_FUNCTION_F 5
#define GPIO_PIN_FUNCTION_G 6
#define GPIO_PIN_FUNCTION_H 7
#define GPIO_PIN_FUNCTION_I 8
#define GPIO_PIN_FUNCTION_J 9
#define GPIO_PIN_FUNCTION_K 10
#define GPIO_PIN_FUNCTION_L 11
#define GPIO_PIN_FUNCTION_M 12
#define GPIO_PIN_FUNCTION_N 13
#define D4   GPIO(GPIO_PORTA, 14)
#define D6   GPIO(GPIO_PORTA, 18) // alias PA18
#define PA18 GPIO(GPIO_PORTA, 18) // alias D6
#define D9   GPIO(GPIO_PORTA, 19)
#define D11  GPIO(GPIO_PORTA, 21) // alias PA21
#define PA21 GPIO(GPIO_PORTA, 21) // alias D11
#define PA22 GPIO(GPIO_PORTA, 22) // alias D13
#define D13  GPIO(GPIO_PORTA, 22) // alias PA22
#define PB03 GPIO(GPIO_PORTB, 3)
#define PA17 GPIO(GPIO_PORTA, 17)
#define PB17 GPIO(GPIO_PORTB, 17)

#endif // ATMEL_START_PINS_H_INCLUDED
