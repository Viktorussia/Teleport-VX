#ifndef VX_SCHEDULER_H
#define VX_SCHEDULER_H

#include "task.h"

// Инициализация планировщика
void scheduler_init();

// Запуск планировщика (выбор следующей задачи)
void scheduler_run();

#endif