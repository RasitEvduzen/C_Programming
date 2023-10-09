#include<stdio.h>
#include<stdlib.h>
#define MASK_SET 0x0F // 0000 1111

char *dec_2_bin(int num)
{
    char *bin_val = (char*)malloc(36); // 32 Byte for value + 3 Byte for space character + 1 Byte for Null Character 
    int idx = 34;
    int i = 0;
    for(;i < 32;++i)
    {
        if(i > 0 && i % 8 == 0)
            bin_val[idx--] = ' '; // Add Space
        if((num & 1) == 1)
            bin_val[idx--] = '1';
        else
            bin_val[idx--] = '0';
        num >>= 1;  // Right Shift Bit
    }
    bin_val[35] = '\0'; // Null Terminate
    return bin_val;
}

int main(int argc, char **argv)
{
    int x,result;
    printf("Enter an integer: \n");
    scanf("%d",&x);


    // Masking Bit Multiple Setting 
    result = x | MASK_SET;
    printf("----- Bitwise Masking Setting Multiple Bit -----\n");
    printf("%-4d -> (%s) Mask Value (%x)  %-4d -> (%s) \n",x,dec_2_bin(x),MASK_SET,result,dec_2_bin(result));
    return 0;
}
