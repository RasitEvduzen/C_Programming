#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


void bit_print1(int ival)
{
    for(int i = (int)(sizeof(ival) * CHAR_BIT - 1); i >= 0; --i)
	    if(!(i % CHAR_BIT) && i) putchar(' ');
	    else putchar(ival >> i & 0x0001 ? '1' : '0');
    putchar('\n');
}

void bit_print2(int ival)
{
    unsigned int mask = ~(~0u >> 1);
    while (mask)
        putchar(ival & mask ? '1' : '0'),mask >>= 1;
    putchar('\n');
}

int main(void)
{
    bit_print1(4095);
    bit_print2(10);

    return 0;
}


