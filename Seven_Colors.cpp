#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define SLEEP_TIME 500

#define led_r DT_ALIAS(led0)   
#define led_g DT_ALIAS(led1)
#define led_b DT_ALIAS(led2)

static const struct gpio_dt_spec leds[] = {
	GPIO_DT_SPEC_GET(led_r, gpios),
	GPIO_DT_SPEC_GET(led_g, gpios),
	GPIO_DT_SPEC_GET(led_b, gpios)
};


void show_color(bool red, bool green, bool blue) {

	gpio_pin_set_dt(&leds[0], red);
	gpio_pin_set_dt(&leds[1], green);
	gpio_pin_set_dt(&leds[2], blue);

}

int main(void) {

	bool on = true;
	int count = 0;

	if ((!gpio_is_ready_dt(&leds[0])) || (!gpio_is_ready_dt(&leds[1])) || (!gpio_is_ready_dt(&leds[2]))) {
		return 0;
	}

	gpio_pin_configure_dt(&leds[0], GPIO_OUTPUT_ACTIVE);
	gpio_pin_configure_dt(&leds[1], GPIO_OUTPUT_ACTIVE);
	gpio_pin_configure_dt(&leds[2], GPIO_OUTPUT_ACTIVE);
 
	while(1) {
		
		show_color(true, false, false);    // red
		k_msleep(SLEEP_TIME);
		show_color(true, true, false);     // yellow
		k_msleep(SLEEP_TIME);
		show_color(false, true, false);    // green
		k_msleep(SLEEP_TIME);
		show_color(false, true, true);    // cyan
		k_msleep(SLEEP_TIME);
		show_color(false, false, true);    // blue
		k_msleep(SLEEP_TIME);
		show_color(true, false, true);    // magenta
		k_msleep(SLEEP_TIME);
		show_color(true, true, true);     // white
		k_msleep(SLEEP_TIME);
	}

	return 0;
}


