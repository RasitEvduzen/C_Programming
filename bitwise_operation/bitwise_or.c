#include<stdio.h>
#include<stdlib.h>


char *decimal_2_bin(int num)
{
    char *bin_val = (char*)malloc(33); // 4 Byte + Null 
    int idx = 31;
    int i = 0;
    for(;i < 32;++i)
    {
        if((num & 1) == 1)
            bin_val[idx--] = '1';
        else
            bin_val[idx--] = '0';
        num >>= 1;  // Right Shift Bit
    }
    bin_val[i] = '\0'; // Null Terminate
    return bin_val;
}



int main(int argc, char **argv)
{
    int x,y;
    int result;
    printf("Enter two integers: \n");
    scanf("%d %d",&x,&y);

    result = x | y;
    printf("----- Bitwise OR -----\n");
    printf("%-4d -> %s\n%-4d -> %s\n%-4d -> %s",x,decimal_2_bin(x),y,decimal_2_bin(y),result,decimal_2_bin(result));
}
