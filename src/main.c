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

#include "duck1.h"
#include "duck2.h"
#include "goose.h"

#define MAIN_STACKSIZE        512
#define DUCK1_STACKSIZE       512
#define DUCK2_STACKSIZE       512
#define GOOSE_STACKSIZE       512




#define MAIN_PRIORITY        4
#define DUCK1_PRIORITY       4
#define DUCK2_PRIORITY       4
#define GOOSE_PRIORITY       4




K_SEM_DEFINE(duck1_semaphore, 0, 1);
K_SEM_DEFINE(duck2_semaphore, 0, 1);
K_SEM_DEFINE(goose_semaphore, 0, 1);

     
//brief main thread: controls gating of tasks.

uint32_t duck1_complete = 0;
uint32_t duck2_complete = 0;
uint32_t goose_complete;

void UpdateDuck1CompleteFlag_CLBK(void)
{
    duck1_complete = 1;
}

void UpdateDuck2CompleteFlag_CLBK(void)
{
    duck2_complete = 1;
}

void UpdateGooseCompleteFlag_CLBK(void)
{
    goose_complete = 1;
}


void Main_THREAD(void)
{
	//register task completion (print completed) callbacks
	RegisterDuck1CompleteCLBK(UpdateDuck1CompleteFlag_CLBK);
	RegisterDuck2CompleteCLBK(UpdateDuck2CompleteFlag_CLBK);
	RegisterGooseCompleteCLBK(UpdateGooseCompleteFlag_CLBK);



    while(1)
    {


		//block at task start (remove if this is not desired)
	k_sem_give(&duck1_semaphore);
	k_sem_give(&duck2_semaphore);
	k_sem_give(&goose_semaphore);
	

    //signal duck1 thread is clear to print when ready
    k_sem_give(&duck1_semaphore);
   


	
	
    //wait until duck1 callback was received (duck1 ran to completion (ie printed first 'duck'))
    while(duck1_complete==0) 
    {
        k_yield();
    }
    duck1_complete = 0;

    printk(", ");
    

    
   

    //signal duck2 thread is clear to print when ready
    k_sem_give(&duck2_semaphore);

    //wait until duck2 callback was received (duck1 ran to completion (ie printed second 'duck'))
    while(duck2_complete==0)
    {
        k_yield();
    }
    duck2_complete = 0;
    printk(", ");

     


    //signal goose thread cleared to print when ready
    k_sem_give(&goose_semaphore);

    //wait until goose callback was received (goose ran to completion (ie printed goose))
    while(goose_complete==0)
    {
        k_yield();
    }
    goose_complete = 0;
    printk("\r\n");

    
    }
    
   

}






// Define and initialize threads


K_THREAD_DEFINE(Duck1_THREAD_id, DUCK1_STACKSIZE, Duck1_THREAD, NULL, NULL, NULL,
        DUCK1_PRIORITY, 0, 0);


K_THREAD_DEFINE(Duck2_THREAD_id, DUCK2_STACKSIZE, Duck2_THREAD, NULL, NULL, NULL,
        DUCK2_PRIORITY, 0, 0);

K_THREAD_DEFINE(Goose_THREAD_id, GOOSE_STACKSIZE, Goose_THREAD, NULL, NULL, NULL,
        GOOSE_PRIORITY, 0, 0);

K_THREAD_DEFINE(Main_THREAD_id, MAIN_STACKSIZE, Main_THREAD, NULL, NULL, NULL,
        MAIN_PRIORITY, 0, 0); 