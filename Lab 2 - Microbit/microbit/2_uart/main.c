#include <stdint.h>
#include "gpio.h"
#include "uart.h"
#include <stdio.h>

const int BUTTON_A_PIN = 14;
const int BUTTON_B_PIN = 23;

void init_buttons(){
	GPIO0->DIRCLR = (1 << BUTTON_A_PIN); // set button pin as input
	GPIO0->DIRCLR = (1 << BUTTON_B_PIN);
}

int button_press_a(){ // Doesnt work? Appareantly it does.
	return (!(GPIO0->IN & (1 << BUTTON_A_PIN)));
}

int button_press_b(){
	return (!(GPIO0->IN & (1 << BUTTON_B_PIN)));
}

void burst_flash(){
	gpio_init();
	int sleep = 0;
	gpio_lights_on();
	sleep = 300000;
	while (--sleep);
	gpio_lights_off();
	sleep = 300000;
	while (--sleep);
	gpio_lights_on();
	sleep = 300000;
	while (--sleep);
	gpio_lights_off();
}

int toggle_LEDs(int led_state){
	if (led_state == 1){
		gpio_lights_on();
		led_state = 0;
	} else {
		gpio_lights_off();
		led_state = 1;
	}
	return led_state;
	
}


ssize_t _write(int fd, const void *buf, size_t count){
	char * letter = (char *)(buf);
	for(int i = 0; i < count; i++){
		uart_send(*letter);
		letter++;
	}
	return count;
}


int main(){
	init_buttons();
	uart_init();
	burst_flash(); // flash LEDs on startup.

	iprintf("The average grade in TTK%d was in %d and %d: %c\n\r", 4235, 2019, 2018, 'C');
	
	int sleep;
	int led_state = 0;
	while(1){

		if (button_press_a()){
			uart_send('A');
			burst_flash();
		}

		if (button_press_b()){
			uart_send('B');
			burst_flash();
		}

		if (uart_read() != '\0'){
			led_state = toggle_LEDs(led_state); // checked that works.
		}
	

		sleep = 100;
		while(--sleep);
	}
	return 0;
}
