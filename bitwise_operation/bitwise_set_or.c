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
    int result;
    printf("Enter an integer: \n");
    scanf("%d",&x);

    printf("Enter bit position: \n");
    scanf("%d",&n);

    // Setting a Bit (OR)
    result = x | (1 << n);
    printf("----- Bitwise Setting -----\n");
    printf("Setting Bit %-4d of %-4d  (%s) -> New Value %-4d  (%s)\n",n,x,dec_2_bin(x),result,dec_2_bin(result));
}
