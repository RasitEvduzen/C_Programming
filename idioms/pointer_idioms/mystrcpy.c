#include <stdio.h>
#include <string.h>

void mystrcpy(char* pdest, const char* psource)
{
	while(*pdest++ = *psource++)
		; //null statement
}

int main(void)
{
    char* tmp_name = "temp";
    char name[strlen(tmp_name) + 1];

    mystrcpy(name, tmp_name);
    puts(name);

    return 0;
}