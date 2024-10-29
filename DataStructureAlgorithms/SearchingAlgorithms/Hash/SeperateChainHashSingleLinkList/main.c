#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hashtable.h"

void get_random_record(char *key, PERSON *per);


int main(void)
{
    HHASTABLE hhtable;
    PERSON per;
    char name[32];
    
    PERSON spec_per = {"Rasit Evduzen",34,123456789};
    char spec_name[32] = "Rasit Evduzen";

    PERSON *ret_per;

    srand(time(NULL));  // Set Random Seed Value 

    if((hhtable = create_htable(HASH_TABLE_SIZE,LOAD_FACTOR)) == NULL)
    {
        fprintf(stderr,"Cannot Create Hash Table!..\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < 100; ++i)
    {
        if(i == 50){       
            if(!insert_htable(hhtable,spec_name,&spec_per)){
                fprintf(stderr,"Cannot Add Item!..\n");
                exit(EXIT_FAILURE);
            }
        }
        else{
            get_random_record(name,&per);
            if(!insert_htable(hhtable,name,&per)){
                fprintf(stderr,"Cannot Add Item!..\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    if(!(ret_per = find_htable(hhtable,"Rasit Evduzen"))){
        fprintf(stderr,"Cannot Find Item!..\n");
        exit(EXIT_FAILURE);
    }
    else{
        printf("Person Name: %s\nPerson City No: %d\nPerson No: %d\n",ret_per->name,ret_per->city,ret_per->no);
    }

    if((remove_htable(hhtable,"Rasit Evduzen"))){
        printf("Item Removed!..\n");
    }
    else{
        printf("Item Cannot Removed!..\n");
    }

    return 0;
}


void get_random_record(char *key, PERSON *per)
{
    int i;
    for(i = 0; i < 31; ++i)
        key[i] = per->name[i] = rand() % 26 + 'A';
    key[i] = per->name[i] = '\0';  // Null Terminated Byte Stream
    per->city = rand() % 81;
    per->no = rand() % 1000000;

}