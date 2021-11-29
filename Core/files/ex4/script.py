a = 0xfebc45fe4512695f
b = 0xf48ef54a
res = 0
mask = 0

for i in range(0, len(bin(b))-2):
    mask = 1 << i
    mask = b & mask

    if (mask):
        res += (a << i)

print(res)
print(a*b)