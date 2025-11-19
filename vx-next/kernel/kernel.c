#include "task.h"

// Прототипы инициализации
extern void task_init();
extern void scheduler_init();

// Главная точка входа ядра Teleport VX Next
void vx_kernel_main() {
    // Инициализация подсистем
    task_init();
    scheduler_init();

    // Здесь позже:
    // - создадим system-space
    // - запустим первые сервисы
    // - включим основной цикл планировщика

    while (1) {
        // Заглушка главного цикла
        // В будущем здесь будет вызов scheduler_run()
    }
}