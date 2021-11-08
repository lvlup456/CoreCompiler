test= [0x01, 0x32, 0x01, 0X04]
val = 0

j = len(test)-1
for i in test:
    print( str(val) + " + " + str(i) + " * " + str(pow(16,j*2)))
    val = val + i * pow(16,j*2)
    j = j -1

print(val)
print(0x01320104)