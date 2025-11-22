#include "task.h"
#include "scheduler.h"
#include "ipc.h"
#include "system_space.h"

// Главная точка входа ядра Teleport VX Next
void vx_kernel_main() {
    // 1. Инициализация подсистем ядра
    task_init();
    scheduler_init();
    ipc_init();
    system_space_init();

    // Здесь позже появится создание базовых задач и сервисов

    while (1) {
        // Основной цикл ядра
        scheduler_run();
    }
}