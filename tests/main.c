/***************************************************
 * Function : 
 * Author : leon
 * Creat Date : 2017/08/30  16:3:29
 * Description : 
 * In-Parameter : 
 * Return : 
 * Modify : 
 **************************************************/
#include <stdio.h>
#include "../backtrace/ss_show_stack.h"

int
main(int argc, char *argv[])
{
	ss_show_call_stack(3,NULL);
	return 0;
}


