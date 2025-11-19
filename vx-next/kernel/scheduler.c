#include "task.h"

// Указатель на текущую выполняемую задачу
extern task_t *current_task;

// Глобальная очередь задач
extern task_t *task_list_head;

// Round-robin scheduler — простейший планировщик
void scheduler_run() {
    if (!current_task) {
        current_task = task_list_head;
        return;
    }

    if (current_task->next) {
        current_task = current_task->next;
    } else {
        // Если это последняя задача — начинаем сначала
        current_task = task_list_head;
    }
}

// Инициализация планировщика
void scheduler_init() {
    // Пока пусто — добавим позже
}