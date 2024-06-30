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
    int x;
    int mul,div;
    printf("Enter an integers: \n");
    scanf("%d",&x);


    mul = x << 1;
    printf("----- Bitwise Multiply 2 -----\n");
    printf("%-4d -> %s Multiplying 2 :  %-4d -> (%s)\n",x,dec_2_bin(x),mul,dec_2_bin(mul));

    div = x >> 1;
    printf("----- Bitwise Divide 2 -----\n");
    printf("%-4d -> %s Dividing 2 :  %-4d -> (%s)\n",x,dec_2_bin(x),div,dec_2_bin(div));

    return 0;
}
