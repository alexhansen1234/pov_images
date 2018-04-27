.global lpm_u16
.text
lpm_u16:
movw  r30,  r24
lpm   r24,  Z+
lpm   r25,  Z+
ret
