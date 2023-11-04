/******************************************************************************
  * File Name          : goose.h
  * Description        : provides code for 'goose' in printed 'duck, duck, goose' 
  *                      sequence.
  ******************************************************************************/

#ifndef GOOSE_H
#define GOOSE_H


typedef  void (*Goose_Callback_ptr_t)();

 /******************************************************************************
  * function          : RegisterDuck1CompleteCLBK
  * Description       : user calls theis function to register callback,
  *                     only one callback permitted
  * inputs              callback - pointer to callback function utilized
  * outputs            NONE
  ******************************************************************************/
int32_t RegisterGooseCompleteCLBK(Goose_Callback_ptr_t callback);

 /******************************************************************************
  * THREAD          : Goose Thread
  * Description     : when signaled by main, sleeps 3-4 seconds then prints 'goose'
  *                    (the second duck)
  ******************************************************************************/
void Goose_THREAD(void);


#endif GOOSE_H