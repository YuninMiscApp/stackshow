/***************************************************
 * Function : 
 * Author : leon
 * Creat Date : 2017/04/18  9:47:33
 * Description : 
 * In-Parameter : 
 * Return : 
 * Modify : 
 **************************************************/
 

#ifndef __SS_SHOW_STACK_H
#define __SS_SHOW_STACK_H
#include "ss_config.h"

SS_BEGIN_DECLS

void ss_show_call_stack(int level,int (*output)(const char *));

SS_END_DECLS


#endif //__SS_SHOW_STACK_H
