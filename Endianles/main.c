#include <stdio.h>
#include <inttypes.h>
/*
little endian
    higher memory
       ----->
 +----+----+----+----+
 |0x01|0x00|0x00|0x00|
 +----+----+----+----+
 ^
 |
&data

big endian
+----+----+----+----+
 |0x00|0x00|0x00|0x01|
 +----+----+----+----+
 ^
 |
&data
*/

#define endian_conv_16(x)    (((x) >> 8) && 0xFF) | ((x) << 8)
#define endian_conv_32(x)    (((x) >> 24) & 0x000000FF) | (((x) >> 8) & 0x0000FF00) | (((x) << 8) & 0x00FF0000) | (((x) << 24) & 0xFF000000)

int main()
{
   unsigned int i = 1;          // 00000000 00000000 00000000 00000001 -> 0x 00 00 00 01      "4Byte Unsigned Int"
   char *c = (char*)&i;         // Int val to Char val    "1Byte"
   printf(*c ? "Little endian\n":"Big endian\n");
   return 0;
}
