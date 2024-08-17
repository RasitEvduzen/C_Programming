#include <stdio.h>

void buffer_flush(void)
{
    int tmp_char;
    while (tmp_char = getchar() != '\n' && tmp_char != EOF) ;
}


int main()
{   
    int ival1,ival2;
    printf("Give a integer number:");
    scanf("%d",&ival1);
    buffer_flush();
    printf("Give a integer number:");
    scanf("%d",&ival2);
    printf("Given Numbers: %d  %d\n",ival1,ival2);
    
    return 0;
}