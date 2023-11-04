/******************************************************************************
  * File Name          : duck2.h
  * Description        : provides code for 'second' duck in 'duck, duck, goose' 
  *                      sequence.
  ******************************************************************************/

#ifndef DUCK2_H
#define DUCK2_H



typedef  void (*Duck2_Callback_ptr_t)();


 /******************************************************************************
  * function          : RegisterDuck1CompleteCLBK
  * Description       : user calls theis function to register callback,
  *                     only one callback permitted
  * inputs              callback - pointer to callback function utilized
  * outputs            NONE
  ******************************************************************************/
int32_t RegisterDuck1CompleteCLBK(Duck2_Callback_ptr_t callback);




 /******************************************************************************
  * THREAD          : Duck2 Thread
  * Description     : when signaled by main, sleeps 2-3 seconds then prints 'duck'
  *                    (the second duck)
  ******************************************************************************/
void Duck2_THREAD(void);


#endif DUCK2_H