#include<stdio.h>
#include<stdlib.h>


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
    int x,n;
    int l_shift,r_shift;

    printf("Enter integer: \n");
    scanf("%d",&x);
    printf("Enter n digit shift value: \n");
    scanf("%d",&n);


    
    printf("----- Bitwise N Bit Left Shift -----\n");
    l_shift = x << n;
    printf("%-4d -> %s\n%-4d -> %s",x,dec_2_bin(x),l_shift,dec_2_bin(l_shift));

    printf("\n----- Bitwise N Bit Right Shift -----\n");
    r_shift = x >> n;
    printf("%-4d -> %s\n%-4d -> %s",x,dec_2_bin(x),r_shift,dec_2_bin(r_shift));
    return 0;
}