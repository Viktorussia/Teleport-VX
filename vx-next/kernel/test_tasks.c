#include "test_tasks.h"
#include "task.h"
#include "system_space.h"
#include "space.h"

extern task_t* task_create(void (*entry)(), int task_id, int space_id);

// ==== ТЕСТОВЫЕ ЗАДАЧИ ====

void task_blink() {
    // Позже здесь будет вывод текста / мигание
    while (1) {
        // пустой цикл-заглушка
    }
}

void task_counter() {
    int i = 0;
    while (1) {
        i++;
        // потом добавим логирование i
    }
}

// ==== ИНИЦИАЛИЗАЦИЯ ====

void test_tasks_init() {
    space_t *sys = get_system_space();

    if (!sys) {
        // позже здесь будет panic() или лог
        return;
    }

    // Создаём две тестовые задачи в системном пространстве
    task_create(task_blink,   1, sys->space_id);
    task_create(task_counter, 2, sys->space_id);
}
