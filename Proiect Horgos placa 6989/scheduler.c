/*
 * scheduler.c
 *
 *  Created on: Nov 12, 2025
 *      Author: cosmi
 */


#include "scheduler.h"

tCB initTask(void (*funct)(), uint8_t taskPeriod,  uint8_t taskDelay, bool periodicTask)
{

    tCB task;

    task.funct = funct;
    task.taskPeriod = taskPeriod;
    task.taskDelay = taskDelay;
    task.elapsedTime = 0; // initializare timp scurs de la ultima rulare
    task.periodicTask = periodicTask;

#ifdef DEBUG_SCHEDULER
    task.taskExecutionMin = 0xFF;
    task.taskExecutionMax = 0;
#endif

    task.state = Waiting;

    if (taskDelay == 0)
    {
        task.state = Ready;
    }

    return (task);
} // initTask()

void scheduler()
{
   uint8_t indexTask;

#ifdef DEBUG_SCHEDULER

   uint16_t taskTiming = 0;

#endif

   for(indexTask = 0; indexTask < TASK_COUNT; ++indexTask)
   {
       ++taskList[indexTask].elapsedTime;  /* incrementam cu un MinorCycle */

       if( (taskList[indexTask].state == Ready) && (taskList[indexTask].elapsedTime >= taskList[indexTask].taskPeriod) )
       {
           taskList[indexTask].state = Running;

           /* lansare task */

#ifdef DEBUG_SCHEDULER

    timer_start_task_statistics();

#endif

           taskList[indexTask].funct();

#ifdef DEBUG_SCHEDULER

    taskTiming = timer_stop_task_statistics();

    if(taskList[indexTask].taskExecutionMin >= taskTiming){
        taskList[indexTask].taskExecutionMin = taskTiming;
    }

    taskList[indexTask].taskExecutionMax = taskList[indexTask].taskExecutionMax <= taskTiming ? taskTiming : taskList[indexTask].taskExecutionMax;

#endif

           /* am revenit din rularea task-ului */
           if (taskList[indexTask].periodicTask == false)
           {
               taskList[indexTask].state = Stop;
               /* Stergem task-ul */
           }
           else
           {
               taskList[indexTask].state = Ready;

               taskList[indexTask].elapsedTime = 0;
           }
       }
       else // Implementare delay Task
       {
           if( (taskList[indexTask].state == Waiting) && (taskList[indexTask].elapsedTime >= taskList[indexTask].taskDelay) )
           {
               taskList[indexTask].state = Ready;
               taskList[indexTask].taskDelay = 0;
               taskList[indexTask].elapsedTime = 0;
           }
       }
   }
} // scheduler()
