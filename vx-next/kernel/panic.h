#ifndef VX_PANIC_H
#define VX_PANIC_H

// Коды уровней паники (на будущее, если захотим различать)
typedef enum {
    PANIC_GENERAL,
    PANIC_MEMORY,
    PANIC_TASK,
    PANIC_SPACE,
    PANIC_CAPABILITY,
    PANIC_IPC
} panic_type_t;

// Базовая функция паники ядра
void vx_panic(const char *message);

// Паника с типом (для более точной диагностики)
void vx_panic_type(panic_type_t type, const char *message);

#endif
