
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/random/rand32.h>
#include <string.h>
#include "rando_sleep.h"
#include "duck2.h"




extern struct k_sem duck2_semaphore;
 
//callback activated at task completion, user uses RegisterDuck1CompleteCLBK to register
void (*Duck2Complete_CLBK_ptr)() = 0;



int32_t RegisterDuck2CompleteCLBK(Duck2_Callback_ptr_t callback)
{
    Duck2Complete_CLBK_ptr = callback;
}



void ActivateDuck2Callback()
{

    if(Duck2Complete_CLBK_ptr!=0)
    {
    (*Duck2Complete_CLBK_ptr)(); //activate userCLBK
    }
}

//brief: duck2 thread runs every 2-3 seconds and prints when signaled by main
void Duck2_THREAD(void)
{
   
    while(1)
    {
        //wait for clear to start from main:
        k_sem_take(&duck2_semaphore, K_FOREVER);
        
        //between 2 to 3 second delay

        RandomSleepBounded(2000, 1, 999);

        
        //wait for clear to print from main thread
        k_sem_take(&duck2_semaphore, K_FOREVER);
        printk("duck");
        ActivateDuck2Callback();
    }
    

}











       