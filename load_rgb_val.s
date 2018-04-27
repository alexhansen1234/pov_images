/* WS2812 Data Pushing Routine */

SPL = 0x3d
SPH = 0x3e
SREG = 0x3f
_temp_reg_ = 0x00
_zero_reg_ = 0x01
OUTPUT_PORT = 0x0B
OUTPUT_BIT = 7

/* extern void load_rgb_val (uint32_t color) */
.global load_rgb_val
.text
load_rgb_val:

  ldi   r20, 0x08
byte1:
  lsl   r23
  brbs  0,  byte1_bit_high
  call  T0
  rjmp  byte1_bit_low
  byte1_bit_high:
  call  T1
  byte1_bit_low:
  dec   r20
  brne  byte1

  ldi r20,  0x08
byte2:
  lsl   r24
  brbs  0,  byte2_bit_high
  call  T0
  rjmp  byte2_bit_low
  byte2_bit_high:
  call  T1
  byte2_bit_low:
  dec   r20
  brne  byte2

  ldi r20,  0x08
byte3:
  lsl   r22
  brbs  0,  byte3_bit_high
  call  T0
  rjmp  byte3_bit_low
  byte3_bit_high:
  call  T1
  byte3_bit_low:
  dec   r20
  brne  byte3

  ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Logic zero written to WS2812                 ;
; high for 500ns [8 clock cycles at 16MHz]     ;
; low for 625ns [10 clock cycles at 16MHz]    ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
T0:
    ldi r21, 1<<OUTPUT_BIT
    out OUTPUT_PORT, r21
    nop
    nop
    nop
    nop
    nop
    ldi r21, 0<<OUTPUT_BIT
    out OUTPUT_PORT, r21
    nop
    nop
    nop
    ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Logic one written to WS2812                 ;
; high for 750ns [12 clock cycles at 16MHz]   ;
; low for 625ns [10 clock cycles at 16MHz]    ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
T1:
  ldi r21, 1<<OUTPUT_BIT
  out OUTPUT_PORT,  r21
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  nop
  ldi r21, 0<<OUTPUT_BIT
  out OUTPUT_PORT,  r21
  nop
  nop
  nop
  ret
