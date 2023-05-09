
# 42_ft_ssl_md5

args using bitwise impl: https://youtu.be/6hnLMnid1M0
specification: http://csrc.nist.gov/publications/fips/fips180-2/fips180-2withchangenotice.pdf

## Betwise examples

1. Bitwise AND (`&`):
```
    01101100
&   10101010
------------
    00101000
```

2. Bitwise OR (`|`):
```
    01101100
|   10101010
------------
    11101110
```

3. Bitwise XOR (`^`):
```
    01101100
^   10101010
------------
    11000110
```

4. Bitwise complement (`~`):
```
~   01101100
------------
    10010011
```

5. Bitwise left shift (`<<`):
```
    01101100
<<  3
------------
    01100000
```

6. Bitwise right shift (`>>`):
```
    01101100
>>  3
------------
    00001101
```

## sha256 & sha512 basic operations

1. right shift operation
``` C
#define SHA256_SHR(x, n) ((x) >> (n))
```

2. right rotation of 32bit unsigned int
``` C
#define SHA256_ROTR(x, n) (((x) >> (n)) | ((x) << (32 - (n))))
```
The `SHA256_ROTR` macro in C performs a right rotation of a 32-bit unsigned integer `x` by `n` bits, where the bits that are shifted out on the right side are placed on the left side.
Example of SHA256_ROTR(11, 3) :
```
00000000000000000000000000001011 // 11 binary representation
11000000000000000000000000000010 // after SHA256_ROTR(11, 3)
```
3. sigma 0
``` C
#define SHA256_DELTA0(x) (SHA256_ROTR(x,7) ^ SHA256_ROTR(x,18) ^ SHA256_SHR(x, 3))
```
example:
```
x:       00000000000000000011111111111111
SHA256_ROTR 7:  11111110000000000000000001111111
SHA256_ROTR 18: 00001111111111111100000000000000 XOR
SHA256_SHR 3:   00000000000000000000011111111111 XOR

SHA256_DELTA0:    11110001111111111100011110000000
```

4. sigma 1 (same as sigma 0 but different rotations and shifts number)
``` C
#define SHA256_DELTA1(x) (SHA256_ROTR(x,17) ^ SHA256_ROTR(x,19) ^ SHA256_SHR(x, 10))
```
example:
```
x:      00000000000000000011111111111111
ROTR17: 00011111111111111000000000000000
ROTR19: 00000111111111111110000000000000 XOR
SHA256_SHR 10: 00000000000000000000000000001111 XOR
SHA256_DELTA1:   00011000000000000110000000001111
```

5. SIGMA 0 (same as sigma 0 but different rotations and using another SHA256_ROTR instead of using SHA256_SHR)
``` C
#define SHA256_SIG0(x) (SHA256_ROTR(x,2) ^ SHA256_ROTR(x,13) ^ SHA256_ROTR(x,22))
```
example:
```
x:       00000000000000000011111111111111
SHA256_ROTR 2:  11000000000000000000111111111111
SHA256_ROTR 13: 11111111111110000000000000000001
SHA256_ROTR 22: 00000000111111111111110000000000
SHA256_SIG0 :   00111111000001111111001111111110

```
6. SIGMA 1 (same as sigma 0 but different rotations and using another SHA256_ROTR instead of using SHA256_SHR)
``` C
#define SHA256_SIG1(x) (SHA256_ROTR(x,6) ^ SHA256_ROTR(x,11) ^ SHA256_ROTR(x,25))
```
example:
```
x:       00000000000000000011111111111111
SHA256_ROTR 6:  11111100000000000000000011111111
SHA256_ROTR 11: 11111111111000000000000000000111
SHA256_ROTR 25: 00000000000111111111111110000000
SHA256_SIG1:    00000011111111111111111101111000
```

7. Choise ( choose between `y` and `z` based on the value of `x`. If `x` is 1, the result is `y`, otherwise it is `z`.)
``` C
#define SHA256_CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
```
example:
``` C
x:  00000000111111110000000011111111
y:  00000000000000001111111111111111
z:  11111111111111110000000000000000
SHA256_CH: 11111111000000000000000011111111
```

8. Majority (select the majority value between `x`, `y`, and `z` for each bit position. Specifically, the result for a given bit position is 1 if the majority of the input bits for that position are 1, otherwise it is 0)

``` C
#define SHA256_MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
```
example:
``` C
x:   00000000111111110000000011111111
y:   00000000000000001111111111111111
z:   11111111111111110000000000000000
SHA256_MAJ: 00000000111111110000000011111111
```