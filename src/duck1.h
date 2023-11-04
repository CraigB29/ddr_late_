 /******************************************************************************
  * File Name          : duck1.h
  * Description        : provides code for 'first' duck in 'duck, duck, goose' 
  *                      sequence.
  ******************************************************************************/


#ifndef DUCK1_H
#define DUCK1_H


#include <zephyr/kernel.h>

typedef  void (*Duck1_Callback_ptr_t)();

 /******************************************************************************
  * function          : RegisterDuck1CompleteCLBK
  * Description       : user calls theis function to register callback,
  *                     only one callback permitted
  * inputs              callback - pointer to callback function utilized
  * outputs            NONE
  ******************************************************************************/
int32_t RegisterDuck1CompleteCLBK(Duck1_Callback_ptr_t callback);


 /******************************************************************************
  * THREAD          : Duck1_THREAD
  * Description     : provides code for 'first' duck in 'duck, duck, goose' 
  *                   sequence.
  ******************************************************************************/
void Duck1_THREAD(void);










#endif DUCK1_H