#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define SLEEP_TIME 500

#define led_r DT_ALIAS(led0)   
#define led_g DT_ALIAS(led1)
#define led_b DT_ALIAS(led2)

static const struct gpio_dt_spec red = GPIO_DT_SPEC_GET(led_r, gpios);
static const struct gpio_dt_spec green = GPIO_DT_SPEC_GET(led_g, gpios);
static const struct gpio_dt_spec blue = GPIO_DT_SPEC_GET(led_b, gpios);

int main(void) {
	int count = 1;
	bool on = true;
	int time = 0,
	second = 0,
	minute = 0, 
	hour = 0;

	if ((!gpio_is_ready_dt(&red)) || (!gpio_is_ready_dt(&green)) || (!gpio_is_ready_dt(&blue))) {
		return 0;
	}

	gpio_pin_configure_dt(&red, GPIO_OUTPUT_ACTIVE);
	gpio_pin_configure_dt(&green, GPIO_OUTPUT_ACTIVE);
	gpio_pin_configure_dt(&blue, GPIO_OUTPUT_ACTIVE);
 
	while(time < 20) {
		k_msleep(SLEEP_TIME);
		on = !on;
		gpio_pin_set_dt(&red, on);
		gpio_pin_set_dt(&green, on);
		gpio_pin_set_dt(&blue, on);
		if ((count % 2) == 0){
			time = count / 2;
			hour = time / 3600;
			time %= 3600;
			minute = time / 60;
			second = time % 60;

			printf("%02d : %02d : %02d\n", hour, minute, second);		}
		count++;
	}


	return 0;
}
