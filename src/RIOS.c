#include "RIOS.h"

static uint8_t tasksNum = 0;
static RIOS_Task_t *tasks = NULL;
static uint32_t currentTime = 0;
static uint32_t timerTickPeriod; /* Timer tick rate */
volatile static uint8_t timerFlag = 0u;
void (*Sleep)(void) = NULL;

/// @brief
/// @param _tasks
/// @param _timerTickPeriod
void RIOS_Init(RIOS_Task_t *_tasks, uint32_t _timerTickPeriod)
{
    tasks = _tasks;
    timerTickPeriod = _timerTickPeriod;
}

/// @brief
/// @param pIdleTask
void RIOS_InitIdleTask(void (*pIdleTask)(void))
{
    Sleep = pIdleTask;
}

/// @brief
/// @param _pInput
/// @param _period
void RIOS_TaskCreate(void (*_pInput)(void), uint32_t _period)
{
    tasks[tasksNum].period = _period;
    tasks[tasksNum].elapsedTime = _period;
    tasks[tasksNum].TickFct = _pInput;
    tasksNum++;
}

/// @brief
/// @param
void RIOS_Scheduler(void)
{
    /* Heart of the scheduler code */
    for (uint8_t i = 0; i < tasksNum; ++i)
    {
        if (tasks[i].elapsedTime >= tasks[i].period)
        {                       /* Ready */
            tasks[i].TickFct(); /* execute task tick */
            tasks[i].elapsedTime = 0u;
        }
        tasks[i].elapsedTime += timerTickPeriod;
    }
    timerFlag = 0u;
    while (!timerFlag)
    {
        if (NULL != Sleep)
        {
            Sleep();
        }
    }
}

/// @brief
/// @param
void RIOS_TickISR(void)
{
    timerFlag = 1u;
}
