/***************************************************
 * Function : 
 * Author : leon
 * Creat Date : 2017/04/05  15:7:35
 * Description : 
 * In-Parameter : arm-hisiv300-linux-gcc -Wall -rdynamic -o backtrace_arm backtrace_arm.c -ldl
 * Return : 
 * Modify : 
 **************************************************/
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unwind.h>
#include <assert.h>
#include <string.h>

#include "ss_config.h"
#include "ss_backtrace.h"


SS_BEGIN_DECLS


extern void * __libc_stack_end;  // In the uCLibc library implementations.
extern int dladdr (__const void *__address, Dl_info *__info);

#ifdef  __cplusplus
#define SS_CPP_VOID	(unsigned long *)    //兼容C++,防止报错
#else
#define SS_CPP_VOID	
#endif




static void backtrace_dummy(void)
{
	//do nothing.
	return;
}


char ** ss_backtrace_symbols(void *const *array,  int size)
{
	Dl_info info[size];
	int status[size];
	int cnt;
	size_t total = 0;
	char **result;

	/* Fill in the information we can get from `dladdr'.  */
	for (cnt = 0; cnt < size; ++cnt) {
		status[cnt] = dladdr (array[cnt], &info[cnt]);
		if (status[cnt] && info[cnt].dli_fname &&
			info[cnt].dli_fname[0] != '\0')
			/*
			 * We have some info, compute the length of the string which will be
			 * "<file-name>(<sym-name>) [+offset].
			 */
			total += (strlen (info[cnt].dli_fname ?: "") +
					  (info[cnt].dli_sname ?
					   strlen (info[cnt].dli_sname) + 3 + WORD_WIDTH + 3 : 1)
					  + WORD_WIDTH + 5);
		else
			total += 5 + WORD_WIDTH;
	}

	/* Allocate memory for the result.	*/
	result = (char **) malloc (size * sizeof (char *) + total);
	if (result != NULL) {
		char *last = (char *) (result + size);
		for (cnt = 0; cnt < size; ++cnt) {
			result[cnt] = last;

			if (status[cnt] && info[cnt].dli_fname
				&& info[cnt].dli_fname[0] != '\0') {

				char buf[20];

				if (array[cnt] >= (void *) info[cnt].dli_saddr)
					sprintf (buf, "+%#lx",
							 (unsigned long)(SS_CPP_VOID array[cnt] - SS_CPP_VOID info[cnt].dli_saddr));
				else
					sprintf (buf, "-%#lx",
							 (unsigned long)(SS_CPP_VOID info[cnt].dli_saddr - SS_CPP_VOID array[cnt]));

				last += 1 + sprintf (last, "%s%s%s%s%s[%p]",
									 info[cnt].dli_fname ?: "",
									 info[cnt].dli_sname ? "(" : "",
									 info[cnt].dli_sname ?: "",
									 info[cnt].dli_sname ? buf : "",
									 info[cnt].dli_sname ? ") " : " ",
									 array[cnt]);
			} else
				last += 1 + sprintf (last, "[%p]", array[cnt]);
		}
		assert (last <= (char *) result + size * sizeof (char *) + total);
	}

	return result;
}


int ss_backtrace(void **array, int size)
{
	struct layout *current;
	void *top_frame;
	void *top_stack;
	int cnt = 0;
#ifdef USE_FRAME_POINTER
	unsigned int fp;
	RIGISTER_VALUE_GET(fp);
	top_frame = (void *)ADVANCE_STACK_FRAME(fp);
	top_stack = (void *)(fp - sizeof(struct layout));
#else
	top_frame = FIRST_FRAME_POINTER;
	top_stack = CURRENT_STACK_FRAME;
#endif
	/* We skip the call to this function, it makes no sense to record it.  */
	current = ((struct layout *) top_frame);
	while (cnt < size) {
		if ((void *) current INNER_THAN top_stack
			|| !((void *) current INNER_THAN __libc_stack_end) )
			/* This means the address is out of range.	Note that for the
			toplevel we see a frame pointer with value NULL which clearly is
			out of range.  */
			break;
			
		array[cnt++] = current->return_address;
		
		current = ADVANCE_STACK_FRAME (current->next);
	}
	
	//fix arm bug.
	backtrace_dummy();
	
	return cnt;
}


SS_END_DECLS

