.include "./src/_avr/atmega328mm.s"

data_bit = 6
clk_bit = 7
port = PORTD

.global display_pixel_apa102
.text
display_pixel_apa102:

  push  r16

byte1:
  ldi r16,  0x08
byte1_loop:
  lsl r25
  in  _temp_reg_, SREG
  sbrs _temp_reg_, 0
  cbi port,   data_bit
  sbrc _temp_reg_, 0
  sbi port,   data_bit
  cbi port,   clk_bit
  sbi port,   clk_bit
  dec r16
  brne  byte1_loop

byte2:
  ldi r16,  0x08
byte2_loop:
  lsl r22
  in  _temp_reg_, SREG
  sbrs _temp_reg_, 0
  cbi port,   data_bit
  sbrc _temp_reg_, 0
  sbi port,   data_bit
  cbi port,   clk_bit
  sbi port,   clk_bit
  dec r16
  brne  byte2_loop

byte3:
  ldi r16,  0x08
byte3_loop:
  lsl r23
  in  _temp_reg_, SREG
  sbrs _temp_reg_, 0
  cbi port,   data_bit
  sbrc _temp_reg_, 0
  sbi port,   data_bit
  cbi port,   clk_bit
  sbi port,   clk_bit
  dec r16
  brne  byte3_loop


byte4:
  ldi r16,  0x08
byte4_loop:
  lsl r24
  in  _temp_reg_, SREG
  sbrs _temp_reg_, 0
  cbi port,  data_bit
  sbrc _temp_reg_, 0
  sbi port,  data_bit
  cbi port,  clk_bit
  sbi port,  clk_bit
  dec r16
  brne  byte4_loop

  pop r16
  ret
