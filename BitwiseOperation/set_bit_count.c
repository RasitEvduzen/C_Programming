#include <stdio.h>

int set_bit_count(int x)
{
    int cnt = 0;
    while (x){
        x &= (x - 1);
        ++cnt;
    }
    return cnt;
}

int main(void)
{
    printf("%d",set_bit_count(0xFF));
}