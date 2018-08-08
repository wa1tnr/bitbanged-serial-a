#include "driver_init.h" // gives atmel_start_pins.h for D13 and such

void init_act_LED(void) {
    gpio_set_pin_direction(PA23, GPIO_DIRECTION_OUT);
}

void raise_D13_feather(void) { // Feather M4 Express
    gpio_set_pin_level(PA23, true);
}

void lower_D13_feather(void) {
    gpio_set_pin_level(PA23, false);
}
