#ifndef VX_TASK_H
#define VX_TASK_H

// Состояние задачи
typedef enum {
    TASK_RUNNING,
    TASK_READY,
    TASK_WAITING,
    TASK_PAUSED
} task_state_t;

// Контекст процессора (минимальный)
typedef struct {
    unsigned int eax, ebx, ecx, edx;
    unsigned int esi, edi, ebp;
    unsigned int eip;
    unsigned int esp;
} cpu_context_t;

// Структура задачи
typedef struct task {
    int task_id;
    task_state_t state;
    cpu_context_t context;
    int space_id;            // принадлежность Space
    unsigned int *stack;     // стек задачи
    struct task *next;       // для планировщика
} task_t;

#endif