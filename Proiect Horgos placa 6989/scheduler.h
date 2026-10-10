/*
 * scheduler.h
 *
 *  Created on: Nov 12, 2025
 *      Author: cosmi
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_
#define DEBUG_SCHEDULER

#include <stdbool.h>
#include <stdint.h>
#ifdef DEBUG_SCHEDULER
#include "timer.h"
#endif

#define TASK_COUNT 5 /* Numarul de task-uri din sistem */

typedef enum {Ready , Running, Waiting, Stop} taskState;

typedef struct taskControlBlock{
    void (*funct)();        /* pointer la task */
    uint8_t taskPeriod;     /* perioada de executie a unui Task*/
    uint8_t taskDelay;      /* delay de executie a unui task */
    bool periodicTask;      /* false - one time run, true - periodic Task */
    uint8_t elapsedTime;    /* timpul scurs de la ultima rulare a Task-ului*/
    taskState state;        /* starea curenta a Task-ului */

#ifdef DEBUG_SCHEDULER
    uint16_t taskExecutionMin;
    uint16_t taskExecutionMax;
#endif
} tCB;

/* Lista de task-uri*/
extern tCB taskList[TASK_COUNT];

void scheduler(void); /* Planificator sistem de operare */

tCB initTask(void (*funct)(), uint8_t taskPeriod, uint8_t taskDelay, bool periodicTask); /* Initializare proprietati task */

#endif /* SCHEDULER_H_ */
