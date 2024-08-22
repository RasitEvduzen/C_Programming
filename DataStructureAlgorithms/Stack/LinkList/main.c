#include <stdio.h>
#include <stdlib.h>
#include "stack.h"




int main()
{
	HSTACK t_stack;

	if ((t_stack = stack_create()) == NULL)
	{
		printf("FAILURE");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < 10; ++i)
	{
		if (stack_push(t_stack, i * 7))
		{
			printf("\n\n****************************** PUSH ***********************\n\n\n");
			printf("PUSH DATA\n");
			stack_display(t_stack);
			printf("Last Element: %d\n", stack_peep(t_stack));
			printf("Stack Size: %zu\n", stack_size(t_stack));
			printf("Stack Length: %zu\n", stack_length(t_stack));
		}

		else
		{
			printf("NOT PUSHED");break;
		}
	}

	

	while (stack_pop(t_stack))
	{
		printf("\n\n********************** POP *************************************\n\n\n");
		printf("POP DATA\n");
		stack_display(t_stack);
		printf("Last Element: %d\n", stack_peep(t_stack));
		printf("Stack Size: %zu\n", stack_size(t_stack));
		printf("Stack Length: %zu\n", stack_length(t_stack));

	}

	stack_clear(t_stack);
	//stack_peep(t_stack);
	stack_destroy(t_stack);

	if (t_stack == NULL)
		printf("Destroyed Succesfully!");




}