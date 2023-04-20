#include <stdint.h>

//#define GPIO0 ((NRF_GPIO_REGS0*)__GPIO_BASE_ADDRESS__) //gpio 0 base adress
//#define GPIO1 ((NRF_GPIO_REGS1*)__GPIO_BASE_ADDRESS__) //gpio 1 base adress
#define GPIO0 ((NRF_GPIO_REGS0*)0x50000000) //gpio 0 base adress
#define GPIO1 ((NRF_GPIO_REGS1*)0x50000300) //gpio 1 base adress
// ^ref table 6.8.2 in Product spesification nRF52833

const int BUTTON_A_PIN = 14;
const int BUTTON_B_PIN = 23;


typedef struct {
	// psuedo : GPIO_base // 0x00 = 0

	volatile uint32_t RESERVED0[321];
	// 0x504 = 1284; 1284/4 = 321;

	volatile uint32_t OUT; // 0x504
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t LATCH;
	volatile uint32_t DETECTMODE; // 0x524
	volatile uint32_t RESERVED1_0[118]; // lol, this should not be 119.
	// 0x700 = 1792
	// 0x524 = 1316
	// 1792 - 1316 = 476; 476/4 = 119; 
	volatile uint32_t PIN_CNF[32]; // 0x700 
} NRF_GPIO_REGS0;

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t LATCH;
	volatile uint32_t DETECTMODE;
	volatile uint32_t RESERVED1_1[118];
	volatile uint32_t PIN_CNF[10];
} NRF_GPIO_REGS1;


void enable_matrix(){

	// Rows
	GPIO0->DIRSET = (1 << 21); // set pin as output
	GPIO0->OUTSET = (1 << 21); // set pin as high

	GPIO0->DIRSET = (1 << 22);
	GPIO0->OUTSET = (1 << 22);

	GPIO0->DIRSET = (1 << 15); // ????
	GPIO0->OUTSET = (1 << 15);

	GPIO0->DIRSET = (1 << 24); // ????
	GPIO0->OUTSET = (1 << 24);

	GPIO0->DIRSET = (1 << 19);
	GPIO0->OUTSET = (1 << 19);

	// Cols - want to set these low
	GPIO0->DIRSET = (1 << 28);
	GPIO0->OUTCLR = (1 << 28); 

	GPIO0->DIRSET = (1 << 11);
	GPIO0->OUTCLR = (1 << 11);

	GPIO0->DIRSET = (1 << 31);
	GPIO0->OUTCLR = (1 << 31);

	GPIO1->DIRSET = (1 << 5);
	GPIO1->OUTCLR = (1 << 5);

	GPIO0->DIRSET = (1 << 30);
	GPIO0->OUTCLR = (1 << 30);

	// Enabling rows 1 through 5.
	//GPIO0->OUTSET=(1<<21);
	//GPIO0->OUTSET=(1<<22);
	//GPIO0->OUTSET=(1<<15);
	//GPIO0->OUTSET=(1<<24);
	//GPIO0->OUTSET=(1<<19);

	//GPIO0->OUTSET=(1<<0);
	//GPIO0->OUTSET=(1<<1);
	//GPIO0->OUTSET=(1<<2);
	//GPIO0->OUTSET=(1<<3);
	//GPIO0->OUTSET=(1<<4);
	//GPIO0->OUTSET=(1<<5); // Error: 511 (probably caused by USB DAPLink, something to do with the debugger setup)
	//GPIO1->OUTSET=(1<<5);
	//GPIO0->OUTSET=(1<<6);
	//GPIO0->OUTSET=(1<<7);
	//GPIO0->OUTSET=(1<<8);
	//GPIO0->OUTSET=(1<<9); // 511 
	//GPIO0->OUTSET=(1<<10);
	//GPIO0->OUTSET=(1<<11);
	//GPIO0->OUTSET=(1<<12);
	//GPIO0->OUTSET=(1<<13);
	//GPIO0->OUTSET=(1<<14);
	//GPIO0->OUTSET=(1<<15);
	//GPIO0->OUTSET=(1<<16);
	//GPIO0->OUTSET=(1<<17);
	//GPIO0->OUTSET=(1<<18);
	//*GPIO0->OUTSET=(1<<19);
	//GPIO0->OUTSET=(1<<20); // Mic enable
	//*GPIO0->OUTSET=(1<<21);
	//*GPIO0->OUTSET=(1<<22);
	//GPIO0->OUTSET=(1<<23);
	//GPIO0->OUTSET=(1<<24);
	//GPIO0->OUTSET=(1<<25);
	//GPIO0->OUTSET=(1<<26);
	//GPIO0->OUTSET=(1<<27);
	//GPIO0->OUTSET=(1<<28);
	//GPIO0->OUTSET=(1<<29);
	//GPIO0->OUTSET=(1<<30);
	//GPIO0->OUTSET=(1<<31);


}


void init_matrix(){
	GPIO0->DIRSET = (1 << 21); // set pin as output
	GPIO0->DIRSET = (1 << 22);
	GPIO0->DIRSET = (1 << 15); // Row won't light up
	GPIO0->DIRSET = (1 << 24); // Row won't light up
	GPIO0->DIRSET = (1 << 19);

	// Cols
	GPIO0->DIRSET = (1 << 28);
	GPIO0->DIRSET = (1 << 11);
	GPIO0->DIRSET = (1 << 31);
	GPIO1->DIRSET = (1 << 5);
	GPIO0->DIRSET = (1 << 30);

}


void disable_matrix(){

	// Rows	
	GPIO0->OUTCLR = (1 << 21); // set pin as low
	GPIO0->OUTCLR = (1 << 22);
	GPIO0->OUTCLR = (1 << 15); // Row won't light up
	GPIO0->OUTCLR = (1 << 24); // Row won't light up
	GPIO0->OUTCLR = (1 << 19);

	// Cols - want to set these low
	GPIO0->OUTSET = (1 << 28); 
	GPIO0->OUTSET = (1 << 11);
	GPIO0->OUTSET = (1 << 31);
	GPIO1->OUTSET = (1 << 5);
	GPIO0->OUTSET = (1 << 30);
}


void disable_matrix2(){

	// Rows	
	GPIO0->OUTCLR = (1 << 21); // set pin as low
	GPIO0->OUTCLR = (1 << 22);
	GPIO0->OUTCLR = (1 << 15); // Row won't light up
	GPIO0->OUTCLR = (1 << 24); // Row won't light up
	GPIO0->OUTCLR = (1 << 19);

	// Cols - want to set these low
	GPIO0->OUTCLR = (1 << 28); 
	GPIO0->OUTCLR = (1 << 11);
	GPIO0->OUTCLR = (1 << 31);
	GPIO1->OUTCLR = (1 << 5);
	GPIO0->OUTCLR = (1 << 30);
}

void init_buttons(){
	GPIO0->DIRCLR = (1 << BUTTON_A_PIN); // set button pin as input
	GPIO0->DIRCLR = (1 << BUTTON_B_PIN);
}

int button_press_a(){
	return (!(GPIO0->IN & (1 << BUTTON_A_PIN)));
}

int button_press_b(){
	return (!(GPIO0->IN & (1 << BUTTON_B_PIN)));
}

// From 2_uart 

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




void main_loopV1(){
	int sleep = 0;
	enable_matrix();
	if (!(GPIO0->IN & (1 << BUTTON_B_PIN))){ // sann når eg trykker
		
		disable_matrix2();
		sleep = 10000000;
		while(--sleep);
	}

	if (!(GPIO0->IN & (1 << BUTTON_A_PIN))){ // sann når eg trykker
		
		//disable_matrix2();
		sleep = 100;
		while(--sleep);
	}
}


int main_loopV2(int state){

	if (state == 1){
		enable_matrix();
	} else {
		disable_matrix2();
	}	

	
	if (!(GPIO0->IN & (1 << BUTTON_B_PIN))){ // sann når eg trykker
		if (state == 1){
			state = 0;
		} else {
			state = 1;
		}
		int sleep = 1500000;
		while(--sleep);
	}
	return state;
}

int main(){

	// Configure leds (dere må sjekke selv hvilken GPIO modul de ulike knappene tilhører)
	GPIO0->PIN_CNF[21] = 1; //Row 1
	GPIO0->PIN_CNF[22] = 1; //Row 2
	GPIO0->PIN_CNF[15] = 1; //Row 3 ?
	GPIO0->PIN_CNF[24] = 1; //Row 4 ?
	GPIO0->PIN_CNF[19] = 1; //Row 5

	GPIO0->PIN_CNF[28] = 1; //Col 1
	GPIO0->PIN_CNF[11] = 1; //Col 2
	GPIO0->PIN_CNF[31] = 1; //Col 3
	GPIO1->PIN_CNF[5] = 1;  //Col 4
	GPIO0->PIN_CNF[30] = 1; //Col 5 

	init_matrix(); // Setting rows and cloumns as output.

	

	gpio_init();
	
	// Configure buttons (dere må sjekke selv hvilken GPIO modul de ulike knappene tilhører)
	//__GPIOX__->PIN_CNF[__BUTTON_A_PIN__] = 0; // button A 
	//__GPIOX__->PIN_CNF[__BUTTON_B_PIN__] = 0; // button B

	GPIO0->PIN_CNF[BUTTON_A_PIN] = 0; // button A, configure as input
	GPIO0->PIN_CNF[BUTTON_B_PIN] = 0; // button B
	
	

	init_buttons();

	int sleep = 0;
	int state = 0;
	while(1){
		
		/* Check if button B is pressed;
		 * turn on LED matrix if it is. */

		/* Check if button A is pressed;
		 * turn off LED matrix if it is. */

		if (button_press_b())
		{
			state=1;
		}
		if (button_press_a())
		{
			state=0;
		}
		
		if (state==1)
		{
			gpio_lights_on();
		} else {
			gpio_lights_off();
		}
		
		


		sleep = 100;
		while(--sleep);
	}
	return 0;
}


