#include <stdint.h>
#include "gpio.h"
#include "uart.h"
#include <stdio.h>
#include ".build_system/nrf.h"
//#include <newlib.h>


// sudo minicom -D /dev/ttyACM0
// sudo dmesg --follow
// sudo picocom -b 9600 --flow h /dev/ttyACM0
// picocom -b 9600 /dev/ttyACM0




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




int main(){
	init_buttons();
	uart_init();
	burst_flash(); // flash LEDs on startup.

	iprintf("The average grade in TTK%d was in %d and %d: %c\n\r", 4235, 2019, 2018, 'C');
	
	int sleep;
	while(1){

		if (button_press_a()){
			uart_send('A');
			burst_flash();
			iprintf("Yippee Ki-Yay");
		}

		if (button_press_b()){
			uart_send('B');
			burst_flash();
		}

		char received_char = uart_read();
		if (received_char != 0){
    		// Process the received character, e.g., print it
    		iprintf("Received character: %c\n", received_char);
    		burst_flash();
		}
	

		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
