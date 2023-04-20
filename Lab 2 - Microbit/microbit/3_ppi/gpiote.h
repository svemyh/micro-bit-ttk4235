#ifndef GPIOTE_H
#define GPIOTE_H
#include <stdint.h>

#define GPIOTE ((NRF_GPIOTE_REG*)0x40006000) // 6.9 GPIOTE — GPIO tasks and events.

typedef struct {
	// Tasks
	volatile uint32_t TASKS_OUT[8]; // 0x000; Last cell: 0x01c
		// ^Last cell (TASKS_OUT[7]): 0x01c
		// From last cell: 0x030-0x01c = 48 - 28  = 20 -> 5.
	volatile uint32_t RESERVED0[4]; // 0x030-0x000 = 48-0 = 48 -> 12.
	volatile uint32_t TASKS_SET[8]; // 0x030
		// ^Last cell (TASKS_SET[7]): 0x04C
		// From last cell: 0x060-0x04C = 96 - 76  = 20 -> 5.
	volatile uint32_t RESERVED1[4]; // 0x060-0x030 = 96-48 = 48 -> 12.
	volatile uint32_t TASKS_CLR[8]; // 0x060
	// Events
		// ^Last cell (TASKS_CLR[7]): 0x07C
		// From last cell: 0x100-0x07C = 256 - 124  = 132 -> 33.
	volatile uint32_t RESERVED2[32]; // 0x100-0x060 = 256-96 = 160 -> 40.
	volatile uint32_t EVENTS_IN[8]; // 0x100
		// ^Last cell: 0x11C
		// From last cell: 0x17C-0x11C = 380 - 284  = 96 -> 24.
	volatile uint32_t RESERVED3[23]; // 0x17C-0x100 = 380-256 = 124 -> 31.
	volatile uint32_t EVENTS_PORT; // 0x17C
	// Registers
	volatile uint32_t RESERVED4[97]; // 0x304-0x17C = 772-380 = 392 -> 98.
	volatile uint32_t INTENSET; // 0x304
	volatile uint32_t INTENCLR; // 0x308
	volatile uint32_t RESERVED5[129]; // 0x510-0x308 = 1296-776 = 520 -> 130.


	// hex((8+4+8+4+8+32+8+23+1+97+1+1+129)*4) = hex(1296) = 0x510 -> checks out!
	volatile uint32_t CONFIG[8]; // 0x510
} NRF_GPIOTE_REG;

#endif

void init_GPIOTE();


void gpio_init();
void gpio_lights_on();
void gpio_lights_off();
void init_buttons();
int button_press_a();
int button_press_b();
void burst_flash();
int toggle_LEDs(int led_state);