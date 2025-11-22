#include "task.h"

// Максимальное количество задач и размер стека
#define VX_MAX_TASKS   16
#define VX_STACK_SIZE  4096

// Статический пул задач
static task_t tasks[VX_MAX_TASKS];

// Статические стеки для задач
static unsigned char task_stacks[VX_MAX_TASKS][VX_STACK_SIZE];

// Глобальный список задач (круговой) и текущая задача
task_t *task_list_head = 0;
task_t *current_task   = 0;

// Поиск свободного слота для новой задачи
static task_t* find_free_task_slot(int *index_out) {
    for (int i = 0; i < VX_MAX_TASKS; i++) {
        // Считаем свободным слот, если task_id == 0 и стек ещё не назначен
        if (tasks[i].task_id == 0 && tasks[i].stack == 0) {
            if (index_out) {
                *index_out = i;
            }
            return &tasks[i];
        }
    }
    return 0; // свободных слотов нет
}

// Включаем задачу в круговой список для планировщика
static void add_task_to_list(task_t *t) {
    if (!task_list_head) {
        // Первая задача в системе
        task_list_head = t;
        t->next = t;      // указывает на саму себя
        current_task = t; // текущая задача — первая
        return;
    }

    // Ищем "последнюю" задачу в кольце
    task_t *iter = task_list_head;
    while (iter->next != task_list_head) {
        iter = iter->next;
    }

    // Вставляем новую задачу в конец кольца
    iter->next = t;
    t->next = task_list_head;
}

// Создание новой задачи
task_t* task_create(void (*entry)(), int task_id, int space_id) {
    int idx = -1;
    task_t *t = find_free_task_slot(&idx);
    if (!t) {
        // TODO: здесь можно вызвать panic() или лог
        return 0;
    }

    // Обнуляем структуру задачи
    // (простое обнуление полей)
    t->task_id = task_id;
    t->state   = TASK_READY;
    t->space_id = space_id;
    t->next    = 0;

    // Настраиваем стек: вершина = конец массива
    unsigned int *stack_top = (unsigned int*)(
        task_stacks[idx] + VX_STACK_SIZE
    );

    t->stack = stack_top;

    // Инициализируем контекст CPU
    t->context.eax = 0;
    t->context.ebx = 0;
    t->context.ecx = 0;
    t->context.edx = 0;
    t->context.esi = 0;
    t->context.edi = 0;
    t->context.ebp = 0;

    // Точка входа задачи
    t->context.eip = (unsigned int)entry;
    // Стек
    t->context.esp = (unsigned int)stack_top;

    // Добавляем задачу в список планировщика
    add_task_to_list(t);

    return t;
}

// Переключение задач (заглушка — реальный контекст будет на ASM)
void task_switch() {
    // Реальная реализация переключения контекста
    // появится позже (ASM / низкоуровневый код)
}

// Инициализация подсистемы задач
void task_init() {
    // Обнуляем пул задач
    for (int i = 0; i < VX_MAX_TASKS; i++) {
        tasks[i].task_id = 0;
        tasks[i].state   = TASK_PAUSED;
        tasks[i].stack   = 0;
        tasks[i].next    = 0;
        tasks[i].space_id = 0;
    }

    task_list_head = 0;
    current_task   = 0;
}
