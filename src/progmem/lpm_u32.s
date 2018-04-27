.global lpm_u32
.text
lpm_u32:
movw  r30,  r24
lpm   r22,  Z+
lpm   r23,  Z+
lpm   r24,  Z+
lpm   r25,  Z
ret
