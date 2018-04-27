/*
 *  Interrupt Table must be assembled to object file, and included
 *  first in the linking stage of build.
 */

.include "./src/_avr/atmega328mm.s"

.TEXT
.ORG 0x0000           ;; Interrupts, highest priority first
jmp RESET             ;; 3  Reset Handler
jmp INT0              ;; 3  External Interrupt Request 0
jmp INT1              ;; 3  External Interrupt Request 1
jmp PCINT0            ;; 3  Pin Change Interrupt Request 0
jmp PCINT1            ;; 3  Pin Change Interrupt Request 1
jmp PCINT2            ;; 3  Pin Change Interrupt Request 2
jmp WDT               ;; 3  Watchdog Time-out Interrupt
jmp TIMER2_COMPA      ;; 3  Timer2 Compare A Handler
jmp TIMER2_COMPB      ;; 3  Timer2 Compare B Handler
jmp TIMER2_OVF        ;; 3  Timer2 Overflow Handler
jmp TIMER1_CAPT       ;; 3  Timer1 Capture Handler
jmp TIMER1_COMPA      ;; 3  Timer1 Compare A Handler
jmp TIMER1_COMPB      ;; 3  Timer1 Compare B Handler
jmp TIMER1_OVF        ;; 3  Timer1 Overflow Handler
jmp TIMER0_COMPA      ;; 3  Timer0 Compare A Handler
jmp TIMER0_COMPB      ;; 3  Timer0 Compare B Handler
jmp TIMER0_OVF        ;; 3  Timer0 Overflow Handler
jmp SPI_STC           ;; 3  SPI Transfer Complete Handler
jmp USART_RXC         ;; 3  USART, RX Complete Handler
jmp USART_UDRE        ;; 3  USART, UDR Empty Handler
jmp USART_TXC         ;; 3  USART, TX Complete Handler
jmp ADC               ;; 3  ADC Conversion Complete Handler
jmp EE_READY          ;; 3  EEPROM Ready Handler
jmp ANALOG_COMP       ;; 3  Analog Comparator Handler
jmp TWI               ;; 3  2-wire Serial Interface Handler
jmp SPM_READY         ;; 3  Store Program Memory Ready Handler

RESET:
ldi r16,  lo8(RAMEND)
out SPL,  r16
ldi r16,  hi8(RAMEND)
out SPH,  r16
ldi r16,  0xFF
out DDRD, r16
jmp main

USART_RXC:
        reti
INT0:
        reti
INT1:
        reti
PCINT0:
        reti
PCINT1:
        reti
PCINT2:
        reti
WDT:
        reti
TIMER2_COMPA:
        reti
TIMER2_COMPB:
        reti
TIMER2_OVF:
        reti
TIMER1_CAPT:
        reti
TIMER1_COMPA:
        reti
TIMER1_COMPB:
        reti
TIMER1_OVF:
        reti
TIMER0_COMPA:
        reti
TIMER0_COMPB:
        reti
TIMER0_OVF:
        reti
SPI_STC:
        reti
USART_UDRE:
        reti
USART_TXC:
        reti
ADC:
        reti
EE_READY:
        reti
ANALOG_COMP:
        reti
TWI:
        reti
SPM_READY:
        reti
