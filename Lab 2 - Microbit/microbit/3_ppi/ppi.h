#ifndef PPI_H
#define PPI_H
#include <stdint.h>

#define PPI ((NRF_PPI_REG*)0x4001F000)

typedef struct {
	uint32_t EN;
	uint32_t DIS;
} PPI_TASKS_TYPE;

typedef struct {
	uint32_t EEP;
	uint32_t TEP;
} PPI_CHANNEL_TYPE;

typedef struct {
	// Tasks
	volatile PPI_TASKS_TYPE PPI_TASKS[6]; // (takes twice as much space)
		// ^Last cell (TASKS_CHG[5].DIS): 0x02C
		// From last cell: 0x500-0x02C = 1280 - 44  = 1236 -> 309.
	// Registers
	volatile uint32_t RESERVED0[308];
	volatile uint32_t CHEN; // 0x500
	volatile uint32_t CHENSET; // 0x504
	volatile uint32_t CHENCLR; // 0x508
	volatile uint32_t RESERVED1[1]; // 0x50C
	volatile PPI_CHANNEL_TYPE PPI_CH[20]; // CH[0].EEP -> 0x510 // (takes twice as much space)
		// ^Last cell (CH[19].TEP): 0x5AC
		// From last cell: 0x800-0x5AC = 2048 - 1452 = 596 -> 149.
	volatile uint32_t RESERVED2[148]; // CH[0].EEP -> 0x510
	volatile uint32_t CHG[6]; // CHG[0] -> 0x800
		// ^Last cell (CHG[5]): 0x814
		// From last cell: 0x910-0x814 = 2320 - 2068  = 252 -> 63.
	volatile uint32_t RESERVED3[62];

	// hex(4*(2*6+308+1+1+1+1+20*2+148+6+62)) = hex(2320) = 0x910. Checks out.

	volatile uint32_t FORK_TEP[32]; // FORK[0].TEP -> 0x910
} NRF_PPI_REG; // Programmable peripheral interconnect - 6.15

#endif

void init_PPI();
