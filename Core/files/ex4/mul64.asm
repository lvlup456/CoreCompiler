lsh r3, r2, r6
and r3, r1, r3
cmp r3, 0
BEQ a
mov r9, r9, 0
mov r8, r8, 0
lsh r7, r0, r9
adc r8, r8, 0
add r9, r9, 1
cmp r6, r9
bge -4
add r4, r4, r7
adc r5, r5, 0
add r5, r5, r8
add r6, r6, 1
cmp r6, 40 
ble -10