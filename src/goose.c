/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */




/*
 * Copyright (c) 2017 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/random/rand32.h>
#include <string.h>
#include "rando_sleep.h"
#include "goose.h"


extern struct k_sem goose_semaphore;
 
//callback activated at task completion, user uses RegisterDuck1CompleteCLBK to register
void (*GooseComplete_CLBK_ptr)() = 0;



int32_t RegisterGooseCompleteCLBK(Goose_Callback_ptr_t callback)
{
    GooseComplete_CLBK_ptr = callback;
}



void ActivateGooseCallback()
{

    if(GooseComplete_CLBK_ptr!=0)
    {
    (*GooseComplete_CLBK_ptr)(); //activate userCLBK
    }
}

//sleeps between 3 and 4 seconds then prints 'goose' when signaled by main

void Goose_THREAD(void)
{
   
    while(1)
    {
        //wait for clear to start from main:
        k_sem_take(&goose_semaphore, K_FOREVER);
        
        //delay betwee 3 and 4 seconds
         
        RandomSleepBounded(3000, 1, 999);

        
        //wait for clear to print from main thread
        k_sem_take(&goose_semaphore, K_FOREVER);
        printk("goose");
        ActivateGooseCallback();
    }
    

}






       