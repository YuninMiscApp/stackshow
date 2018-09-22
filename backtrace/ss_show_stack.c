/***************************************************
 * Function : 
 * Author : leon
 * Creat Date : 2017/04/18  9:41:43
 * Description : 
 * In-Parameter : 
 * Return : 
 * Modify : 
 **************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "ss_backtrace.h"

SS_BEGIN_DECLS

void ss_show_call_stack(int level,int (*output)(const char *))
{
	void *array[10];
	size_t size;
	char **strings;
	size_t i;

	size = ss_backtrace (array, level);
	strings = ss_backtrace_symbols (array, size);

	for (i = 0; i < size; i++)
	{
		if(output)
			output(strings[i]);
		else	
			printf("%s\n", strings[i]);
	}

	free (strings);

	return ;
}

SS_END_DECLS


