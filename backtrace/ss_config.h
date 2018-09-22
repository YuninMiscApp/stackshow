/**
  ******************************************************************************
  * @file ss_config.h 
  * @author leon.xie
  * @version v1.0.0
  * @date 2018-4-12 21:39:57
  * @brief This file contains all the functions prototypes for the BOARD 
  *  ss_config 
  ******************************************************************************
  * @attention
  *
  * File For Yunin Software Team Only
  *
  * Copyright (C), 2017-2027, Yunin Software Team
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __SS_CONFIG_H
#define __SS_CONFIG_H

/* Includes ------------------------------------------------------------------*/


/* Exported typedef ----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

/* Guard C code in headers, while including them from C++ */
#ifdef  __cplusplus
#define SS_BEGIN_DECLS  extern "C" {
#define SS_END_DECLS    }
#else
#define SS_BEGIN_DECLS
#define SS_END_DECLS
#endif

#ifndef NULL
#  ifdef __cplusplus
#  define NULL        (0L)
#  else /* !__cplusplus */
#  define NULL        ((void*) 0)
#  endif /* !__cplusplus */
#endif

/* Exported functions ------------------------------------------------------- */

#endif  /* __SS_CONFIG_H */


