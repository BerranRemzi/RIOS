/*
   Copyright (c) 2013 Frank Vahid, Tony Givargis, and
   Bailey Miller. Univ. of California, Riverside and Irvine.
   RIOS version 1.2
*/
#ifndef RIOS_H
#define RIOS_H

#include "stdint.h"

typedef struct
{
    uint32_t period;       /* Rate at which the task should tick */
    uint32_t elapsedTime;  /* Time since task's last tick */
    void (*TickFct)(void); /* Function to call for task's tick */
} RIOS_Task_t;

void RIOS_Init(RIOS_Task_t *_tasks, uint32_t _timerTickPeriod);

void RIOS_InitIdleTask(void (*pIdleTask)(void));

void RIOS_TaskCreate(void (*_pInput)(void), uint32_t _period);

void RIOS_Scheduler(void);

void RIOS_TickISR(void);

#endif /* RIOS_H */