/*
 * ATMEGA328 MEMORY MAP
 * Include in assembly files which require labels for accessing
 * named registers and named fields in those registers.
 *
 * eg.
 *      .include './path/to/atmega328mm.s'
 */

RAMEND = 0x7FF

_temp_reg_ = 0x00     /* [memory-mapped] */
_zero_reg_ = 0x01     /* [memory-mapped] */

/* NON MEMORY MAPPED REGISTERS ACCESSED WITH IN/OUT OPS */
PINB    =   0x03
DDRB    =   0x04
PORTB   =   0x05
PINC    =   0x06
DDRC    =   0x07
PORTC   =   0x08
PIND    =   0x09
DDRD    =   0x0A
PORTD   =   0x0B
TIFR0   =   0x15
TIFR1   =   0x16
TIFR2   =   0x17
PCIFR   =   0x1B
EIFR    =   0x1C
EIMSK   =   0x1D
GPIOR0  =   0x1E
EECR    =   0x1F
EEDR    =   0x20
EEARL   =   0x21
EEARH   =   0x22
GTCCR   =   0x23
TCCR0A  =   0x24
TCCR0B  =   0x25
TCNT0   =   0x26
OCR0A   =   0x27
OCR0B   =   0x28
GPIOR1  =   0x29
GPIOR2  =   0x2A
SPCR0   =   0x2B
SPSR0   =   0x2C
SPDR0   =   0x2D
ACSR    =   0x30
DWDR    =   0x31
SMCR    =   0x33
MCUSR   =   0x34
MCUCR   =   0x35
SPMCSR  =   0x37
SPL     =   0x3D
SPH     =   0x3E
SREG    =   0x3F

WDTCSR  =   0x60    /* [memory-mapped] */
CLKPR   =   0x61    /* [memory-mapped] */
PRR     =   0x64    /* [memory-mapped] */
OSCCAL  =   0x66    /* [memory-mapped] */
PCICR   =   0x68    /* [memory-mapped] */
EICRA   =   0x69    /* [memory-mapped] */
PCMSK0  =   0x6B    /* [memory-mapped] */
PCMSK1  =   0x6C    /* [memory-mapped] */
PCMSK2  =   0x6D    /* [memory-mapped] */
TIMSK0  =   0x6E    /* [memory-mapped] */
TIMSK1  =   0x6F    /* [memory-mapped] */
TIMSK2  =   0x70    /* [memory-mapped] */
ADCL    =   0x78    /* [memory-mapped] */
ADCH    =   0x79    /* [memory-mapped] */
ADCSRA  =   0x7A    /* [memory-mapped] */
ADCSRB  =   0x7B    /* [memory-mapped] */
ADMUX   =   0x7C    /* [memory-mapped] */
DIDR0   =   0x7E    /* [memory-mapped] */
DIDR1   =   0x7F    /* [memory-mapped] */
TCCR1A  =   0x80    /* [memory-mapped] */
TCCR1B  =   0x81    /* [memory-mapped] */
TCCR1C  =   0x82    /* [memory-mapped] */
TCNT1L  =   0x84    /* [memory-mapped] */
TCNT1H  =   0x85    /* [memory-mapped] */
ICR1L   =   0x86    /* [memory-mapped] */
ICR1H   =   0x87    /* [memory-mapped] */
OCR1AL  =   0x88    /* [memory-mapped] */
OCR1AH  =   0x89    /* [memory-mapped] */
OCR1BL  =   0x8A    /* [memory-mapped] */
OCR1BH  =   0x8B    /* [memory-mapped] */
TCCR2A  =   0xB0    /* [memory-mapped] */
TCCR2B  =   0xB1    /* [memory-mapped] */
TCNT2   =   0xB2    /* [memory-mapped] */
OCR2A   =   0xB3    /* [memory-mapped] */
OCR2B   =   0xB4    /* [memory-mapped] */
ASSR    =   0xB6    /* [memory-mapped] */
TWBR    =   0xB8    /* [memory-mapped] */
TWSR    =   0xB9    /* [memory-mapped] */
TWAR    =   0xBA    /* [memory-mapped] */
TWDR    =   0xBB    /* [memory-mapped] */
TWCR    =   0xBC    /* [memory-mapped] */
TWAMR   =   0xBD    /* [memory-mapped] */
UCSR0A  =   0xC0    /* [memory-mapped] */
UCSR0B  =   0xC1    /* [memory-mapped] */
UCSR0C  =   0xC2    /* [memory-mapped] */
UBRR0L  =   0xC4    /* [memory-mapped] */
UBRR0H  =   0xC5    /* [memory-mapped] */
UDR0    =   0xC6    /* [memory-mapped] */

/* ADMUX Bit Defs */
MUX0  = 0
MUX1  = 1
MUX2  = 2
MUX3  = 3
ADLAR = 5
REFS0 = 6
REFS1 = 7

/* ADCSRA Bit Defs */
ADPS0 = 0
ADPS1 = 1
ADPS2 = 2
ADIE  = 3
ADIF  = 4
ADATE = 5
ADSC  = 6
ADEN  = 7

/* ADCSRB Bit Defs */
ADTS0 = 0
ADTS1 = 1
ADTS2 = 2
ACME  = 6

/* DIDR0 Bit Defs */
ADC0D   = 0
ADC1D   = 1
ADC2D   = 2
ADC3D   = 3
ADC4D   = 4
ADC5D   = 5
ADC6D   = 6
ADC7D   = 7

/* TCCR0A Bit Defs */
WGM00   = 0
WGM01   = 1
COM0B0  = 4
COM0B1  = 5
COM0A0  = 6
COM0A1  = 7

/* TCCR0B Bit Defs */
CS00    = 0
CS01    = 1
CS02    = 2
WGM02   = 3
FOC0B   = 6
FOC0A   = 7

/* TCCR1A Bit Defs */
WGM10   = 0
WGM11   = 1
COM1A0  = 4
COM1A1  = 5
COM1B0  = 6
COM1B1  = 7

/* TCCR1B Bit Defs */
CS10    = 0
CS11    = 1
CS12    = 2
WGM12   = 3
WGM13   = 4
ICES1   = 6
ICNC1   = 7

/* TIMSK0 Bit Defs */
TOIE    = 0
OCIEA   = 1
OCIEB   = 2
ICIE    = 5

/* TIFR0 Bit Defs */
TOV     = 0
OCFA    = 1
OCFB    = 2
