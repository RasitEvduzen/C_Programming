#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


int main(void)
{
    // ------------------ TEST-1 ------------------//
    HQUEUE hQueue;
    DATATYPE val;
    if((hQueue = create_queue()) == NULL){
        fprintf(stderr,"Cannot Create Queue!\n");
        exit(EXIT_FAILURE);
    }
	  for (int i = 0; i < 10; ++i)
		if (!put_queue(hQueue, i)) {
			fprintf(stderr, "cannot put queue!..\n");
			exit(EXIT_FAILURE);
		}
    disp_queue(hQueue);
    //-----------------------------------------------
    //-----------------------------------------------

    // ------------------ TEST-2 ------------------//
  //   HQUEUE hQueue;
  //   size_t queue_size = 10;
  //   size_t new_queue_size = 20;
  //   DATATYPE get_val;

  //   if((hQueue = create_queue()) == NULL){
  //       fprintf(stderr,"Cannot Create Queue!\n");
  //       exit(EXIT_FAILURE);
  //   }
	// for (int i = 0; i < 10; ++i)
	// 	if (!put_queue(hQueue, i)) {
	// 		fprintf(stderr, "cannot put queue!..\n");
	// 		exit(EXIT_FAILURE);
	// 	}
  //   disp_queue(hQueue);

  //   for (int i = 0; i < 5; ++i)
	// 	get_queue(hQueue, &get_val);
  //   disp_queue(hQueue);

  //   if(!resize_queue(hQueue,new_queue_size)){
  //       fprintf(stderr,"Cannot Resize Queue!\n");
  //       exit(EXIT_FAILURE);
  //   }
  //   for (int i = 0; i < 15; ++i)
	// 	if (!put_queue(hQueue, i)) {
	// 		fprintf(stderr, "cannot put queue!..\n");
	// 		exit(EXIT_FAILURE);
	// 	}
  //   disp_queue(hQueue);
  //   destroy_queue(hQueue);
    //-----------------------------------------------
    //-----------------------------------------------



    return 0;
}