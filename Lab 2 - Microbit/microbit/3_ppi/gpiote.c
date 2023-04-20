#include "gpiote.h"
#include "gpio.h"

const int BUTTON_A_PIN = 14;
const int BUTTON_B_PIN = 23;



void gpio_init(){
	  GPIO0->PIN_CNF[14] = 0; // button A
	  GPIO0->PIN_CNF[23] = 0; // button B

	  // Configure leds
	  GPIO0->PIN_CNF[21] = 1; //Row 1
	  GPIO0->PIN_CNF[22] = 1; //Row 2
	  GPIO0->PIN_CNF[15] = 1; //Row 3
	  GPIO0->PIN_CNF[24] = 1; //Row 4
	  GPIO0->PIN_CNF[19] = 1; //Row 5

	  GPIO0->PIN_CNF[28] = 1; //Col 1
	  GPIO0->PIN_CNF[11] = 1; //Col 2
	  GPIO0->PIN_CNF[31] = 1; //Col 3
	  GPIO1->PIN_CNF[5] = 1;  //Col 4
	  GPIO0->PIN_CNF[30] = 1; //Col 5 
};

void gpio_lights_on(){
   GPIO0->OUTSET = (1<<21);
   GPIO0->OUTSET = (1<<22);
   GPIO0->OUTSET = (1<<15);
   GPIO0->OUTSET = (1<<24);
   GPIO0->OUTSET = (1<<19);
};

void gpio_lights_off(){
   GPIO0->OUTCLR = (1<<21);
   GPIO0->OUTCLR = (1<<22);
   GPIO0->OUTCLR = (1<<15);
   GPIO0->OUTCLR = (1<<24);
   GPIO0->OUTCLR = (1<<19);
};

void init_buttons(){
	GPIO0->DIRCLR = (1 << BUTTON_A_PIN); // set button pin as input
	GPIO0->DIRCLR = (1 << BUTTON_B_PIN);

	GPIO0->PIN_CNF[BUTTON_A_PIN] = 0; // button A, configure as input
	GPIO0->PIN_CNF[BUTTON_B_PIN] = 0; // button B
    // idk, do both
}

int button_press_a(){
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


// ----------^ From previous tasks.

// Bruk en kanal til å lytte til A-knappen. Denne kanalen skal genere en hendelse naar knappen trykkes - altså når spenningen på GPIO-pinnen går fra høy til lav.




void init_GPIOTE(){
  // "Bruk en kanal til å lytte til A-knappen (P0.08) . Denne kanalen skal genere en hendelse naar knappen trykkes - altså når spenningen på GPIO-pinnen går fra høy til lav."
  GPIOTE->CONFIG[0]= (1 | (BUTTON_A_PIN<<8) | (2<<16)); // 0b0...00
    //^ AA=1 (Event mode); BBBBB=BUTTON_A_PIN=14 (pin select); C=0 (port nr.); DD=2 (HiToLo - Generate IN[n] event when falling edge on pin.); E=0 (no effect in event mode);


  //"De fem resterende kanalene skal alle være konfigurert som oppgaver, og koblet til hver sin forsyningspinne for LED-matrisen. Forsyningsspenningen skal veksle hver gang oppgaven aktiveres. Hvilken initialverdi disse GPIOTE-kanalene har er opp til dere.""

    GPIOTE->CONFIG[1] = (3 << 0) | // AA; (Task mode)
                        (21 << 8) | // BBBBB; (pin select; pins 0 through 4.)
                        (0 << 13) | // C; (port nr.)
                        (3 << 16) | // DD; (DD=3 -> Toggle - Generate IN[n] when any change on pin.)
                        (0 << 20); // E; (E=0 -> Initial value of pin before task triggering is low);
    
    // Shortened for remainder:
    GPIOTE->CONFIG[2] = (3 << 0) | (22 << 8) | (3 << 16);
    GPIOTE->CONFIG[3] = (3 << 0) | (15 << 8) | (3 << 16);
    GPIOTE->CONFIG[4] = (3 << 0) | (24 << 8) | (3 << 16);
    GPIOTE->CONFIG[5] = (3 << 0) | (19 << 8) | (3 << 16);

}