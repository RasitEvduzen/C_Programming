#include<stdio.h>
#include<stdlib.h>


char *dec_2_bin(int num)
{
    char *bin_val = (char*)malloc(36); // 4 Byte + 3 space + Null 
    int idx = 34;
    int i = 0;
    for(;i < 32;++i)
    {
        if(i > 0 && i % 4 == 0)
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
    int x;
    int result;
    printf("Enter integer: \n");
    scanf("%d",&x);

    result = ~x;
    printf("----- Bitwise NOT -----\n");
    printf("%-4d -> %s\n%-4d -> %s\n",x,dec_2_bin(x),result,dec_2_bin(result));
}
