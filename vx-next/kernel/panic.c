#include "panic.h"

// Базовая паника ядра
void vx_panic(const char *message) {
    // Сейчас у нас нет вывода на экран и логов,
    // поэтому просто игнорируем строку, чтобы не было предупреждений.
    (void)message;

    // Останавливаем систему: выключаем прерывания и уходим в вечный hlt
    for (;;) {
        __asm__ __volatile__("cli; hlt");
    }
}

// Паника с типом (пока просто вызываем обычную панику)
void vx_panic_type(panic_type_t type, const char *message) {
    (void)type;
    vx_panic(message);
}
