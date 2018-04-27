#ifndef PROGMEM_H
  #define PROGMEM_H

extern uint32_t lpm_u32(uint32_t *);
/*
  Loads a 32 bit value from program memory space
 */
extern uint16_t lpm_u16(uint16_t *);
/*
  Loads a 16 bit value from program memory space
  */
extern uint8_t  lpm_u8(uint8_t *);
/*
  Loads an 8 bit value from program memory space
  */
extern void * program_address(void *);
/*
  Returns a pointer to a label located in program memory space
  */
#endif
