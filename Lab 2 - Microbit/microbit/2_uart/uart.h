void uart_init();
void uart_send(char letter);
char uart_read();


#define UART ((NRF_UART_REG*) 0x40002000)

typedef struct {
  volatile uint32_t TASKS_STARTRX;
  volatile uint32_t TASKS_STOPRX;
  volatile uint32_t TASKS_STARTTX;
  volatile uint32_t TASKS_STOPTX; // 4 = 1 + 3  words long // 0x0c (TASKS_STOPTX) = 12; 0x1c (TASKS_SUSPEND) = 28; 28-12 = 16; 16 / 4 = 4 = 1 + 3.
  volatile uint32_t RESERVED0[3];
  volatile uint32_t TASKS_SUSPEND; // 0x1c (TASKS_SUSPEND) = 28; 0x100 (EVENTS_CTS) = 256; 256-28 = 228; 228 / 4 = 57 = 1 + 56.
  volatile uint32_t RESERVED1[56];
  volatile uint32_t EVENTS_CTS;
  volatile uint32_t EVENTS_NCTS;
  volatile uint32_t EVENTS_RXDRDY; // 0x108 (EVENTS_RXDRDY) = 264; 0x11c (EVENTS_TXDRDY) = 284; 284-264 = 20; 20 / 4 = 5 = 1 + 4.
  volatile uint32_t RESERVED2[4];
  volatile uint32_t EVENTS_TXDRDY; // 0x11c (EVENTS_TXDRDY) = 284; 0x124 (EVENTS_ERROR) = 292; 292-284 = 8; 8 / 4 = 2 = 1 + 1.
  volatile uint32_t RESERVED3;
  volatile uint32_t EVENTS_ERROR; // 0x124 (EVENTS_ERROR) = 292; 0x144 (EVENTS_RXTO) = 324; 324-292 = 32; 32 / 4 = 8 = 1 + 7.
  volatile uint32_t RESERVED4[7];
  volatile uint32_t EVENTS_RXTO; // 0x144 (EVENTS_RXTO) = 324; 0x200 (SHORT) = 512; 512-324 = 118; 118 / 4 = 47 = 1 + 46.
  volatile uint32_t RESERVED5[46];
  volatile uint32_t SHORT; // 0x200 (SHORT) = 512; 0x304 (INTENSET) = 772; 772-512 = 260; 260 / 4 = 65 = 1 + 64
  volatile uint32_t RESERVED6[64];
  volatile uint32_t INTENSET;
  volatile uint32_t INTENCLR; // 0x308 (INTENCLR) = 776; 0x480 (ERRORSRC) = 1152; 1152-776 = 376; 376 / 4 = 94 = 1 + 93.
  volatile uint32_t RESERVED7[93];
  volatile uint32_t ERRORSRC; // 0x480 (ERRORSRC) = 1152; 0x500 (ENABLE) = 1280; 1280-1152 = 128; 128 / 4 = 32 = 1 + 31.
  volatile uint32_t RESERVED8[31];
  volatile uint32_t ENABLE; // 2 words.
  volatile uint32_t RESERVED9;
  volatile uint32_t PSELRTS;
  volatile uint32_t PSELTXD;
  volatile uint32_t PSELCTS;
  volatile uint32_t PSELRXD;
  volatile uint32_t RXD;
  volatile uint32_t TXD; // 0x51c (TXD) = 1308; 0x524 (BAUDRATE) = 1316; 1316-1308 = 8; 8 / 4 = 2 = 1 + 1.
  volatile uint32_t RESERVED10;
  volatile uint32_t BAUDRATE; // 0x524 (BAUDRATE) = 1316; 0x56C (CONFIG) = 1388; 1388-1316 = 72; 72 / 4 = 18 = 1 + 17.
  volatile uint32_t RESERVED11[17];
  volatile uint32_t CONFIG;
} NRF_UART_REG;