/***************************************************
 * Function : 
 * Author : leon
 * Creat Date : 2017/04/18  9:47:43
 * Description : 
 * In-Parameter : 
 * Return : 
 * Modify : 
 **************************************************/
 
#ifndef __SS_BACKTRACE_H
#define __SS_BACKTRACE_H
#include "ss_config.h"

SS_BEGIN_DECLS



#define FRAME_DEPTH_MAX		0	 //stack frame depth

#ifndef INNER_THAN
#define INNER_THAN <
#endif

#ifndef WORD_WIDTH
#define WORD_WIDTH 8
#endif

typedef struct {
    __const char *dli_fname;  /* File name of defining object.  */
    void *dli_fbase;          /* Load address of that object.  */
    __const char *dli_sname;  /* Name of nearest symbol.  */
    void *dli_saddr;          /* Exact value of nearest symbol.  */
} Dl_info;


struct layout {
    struct layout *next;		//stack frame 
    void *return_address;		//value for LR
};

#define ADVANCE_STACK_FRAME(frm)    \
            ((struct layout *)((unsigned long *)frm - 1))


#ifdef USE_FRAME_POINTER

#define RIGISTER_VALUE_GET(val)	asm(\
        "mov %0,fp\n\t"\
        :"=r"(val)\
        :\
    )

#else
#define FIRST_FRAME_POINTER ADVANCE_STACK_FRAME (__builtin_frame_address (FRAME_DEPTH_MAX))
#define CURRENT_STACK_FRAME (__builtin_frame_address (FRAME_DEPTH_MAX) - sizeof(struct layout))
#endif




int ss_backtrace(void **array, int size);
char ** ss_backtrace_symbols (void *const *array,  int size);

SS_END_DECLS


#endif //__SS_BACKTRACE_H

