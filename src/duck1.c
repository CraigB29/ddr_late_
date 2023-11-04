 /******************************************************************************
  * File Name          : duck1.c
  * Description        : provides code for 'first' duck in 'duck, duck, goose' 
  *                      sequence.
  ******************************************************************************/

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/random/rand32.h>
#include <string.h>
#include "stdint.h"
#include "rando_sleep.h"
#include "duck1.h"



extern struct k_sem duck1_semaphore;

//callback function


//callback activated at task completion, user uses RegisterDuck1CompleteCLBK to register
void (*Duck1Complete_CLBK_ptr)() = 0;



int32_t RegisterDuck1CompleteCLBK(Duck1_Callback_ptr_t callback)
{
    Duck1Complete_CLBK_ptr = callback;
}



void ActivateDuck1Callback()
{

    if(Duck1Complete_CLBK_ptr!=0)
    {
    (*Duck1Complete_CLBK_ptr)(); //activate userCLBK
    }
}





//sleeps between 1 and 2 seconds then prints when signaled my main


void Duck1_THREAD(void)
{

   // RegisterDuck1CompleteCLBK(UpdateDuck1CompleteFlag);
   
    while(1)
    {   

        //wait for clear to start from main:
        k_sem_take(&duck1_semaphore, K_FOREVER);
      
        //between 1 to 2 second delay

        RandomSleepBounded(1000, 1, 999);
        
        //wait for clear to print from main thread
        k_sem_take(&duck1_semaphore, K_FOREVER);
        printk("duck");
        //SetDuck1Complete();
        ActivateDuck1Callback();
    }
    

}




       