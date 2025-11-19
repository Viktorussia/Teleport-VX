#include "task.h"

// Глобальный список задач (пока простой)
task_t *task_list_head = 0;

// Текущая задача
task_t *current_task = 0;

// Создание новой задачи
task_t* task_create(void (*entry)(), int task_id, int space_id) {
    // Пока заглушка
    return 0;
}

// Переключение задач
void task_switch() {
    // Заглушка — реализуем позже
}

// Инициализация блока задач
void task_init() {
    task_list_head = 0;
    current_task = 0;
}