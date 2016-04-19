/*******************************************************************************
              Copyright 2015 Arimex Importadora SA, All Rights Reserved
 *******************************************************************************
 ***************************************************************************/

#ifndef _OS_TASKS_H_
#define _OS_TASKS_H_
/** @brief Brief for this header file.
 **
 ** Full description for this header file.
 **
 **/

/** \addtogroup OS Task
 ** @{ */

/*
 * Initials    Name
 * ---------------------------
 * MD          MARCOS DARINO
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20151109 v0.0.1 FN Initial release.
 */

/*==================[inclusions]=============================================*/

#include "chip.h"

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

void Task1_Init(void);
void Task2_Init(void);
void Task3_Init(void);



void Task1(void);
void Task2(void);
void Task3(void);

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OS_TASKS_H_ */

