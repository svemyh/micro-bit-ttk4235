/*

Target MCU -> nRF52833-QIAA
Interface MCU -> nRF52820-QDAA-R

UART_INT_RX - Interface MCU, 31 -> P0.08
			- Target MCU, L1 -> P0.06

UART_INT_TX - Interface MCU, 32 -> P0.29
			- Target MCU, P2 -> P1.08

Want to configure P0.06 as input and P1.08 as output.
	
*/

#include "gpio.h"
#include "uart.h"

void uart_init(){
	GPIO0->DIRCLR = (1 << 6); // set as input
	GPIO0->PIN_CNF[6] = 0;
	GPIO1->DIRSET = (1 << 8); // set as output
	GPIO1->PIN_CNF[8] = 1;

	UART->BAUDRATE = 0x00275000; // set baudrate to 9600

	UART->PSELRTS = 2147483648; // Disconecting RTS; 2147483648 = 2**31
  	UART->PSELCTS = 2147483648; // Disconecting CTS

	UART->PSELRXD = 0x06; // Connect P0.06 as RXD; (0b00000 || 0x06) = 0 + 6 = 6 = 0x06
	UART->PSELTXD = 0x28; // Connect P1.08 as TXD; (0b10000 || 0x08) = 32 + 8 = 40 = 0x28

	UART->ENABLE = 4;
  	UART->TASKS_STARTTX = 1; // Trigger
}


void uart_send(char letter){
	// Denne funksjonen skal ta i mot en enkel bokstav, for å sende den over til data-maskinen. Husk å vente til sendingen er ferdig, før dere skrur av sendefunksjonaliteten.
	UART->TASKS_STARTTX = 1; // Trigger when set to 1, start UART receiver.
	UART->TXD=letter; // 7 bits. TX data to be transferred.
	while (UART->EVENTS_TXDRDY == 0){ // check if event (TX is ready) has been generated.
		
	}
	UART->EVENTS_TXDRDY = 0; // reset registry above.
	UART->TASKS_STOPTX = 1; // When set to 1 trigger to stop UART transmitter.
}


char uart_read(){
	if (UART->EVENTS_RXDRDY){ // 1 when event (Data received in RXD) has been triggered.
    	UART->EVENTS_RXDRDY = 0; // reset registry above.
    	return UART->RXD; // return letter recieved. (RX data received in previous transfers, double buffered)
  	}
	return '\0';
}


