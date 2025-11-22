#include "space.h"
#include "capability.h"

// Указатель на системное пространство
static space_t *system_space = 0;

// Создание системного пространства
void system_space_init() {
    // 1. Создаём пространство типа SYSTEM
    system_space = space_create(SPACE_SYSTEM);

    if (!system_space) {
        // В будущем тут будет panic()
        return;
    }

    // 2. Даём ему максимальные права
    system_space->capabilities = 
          CAP_READ 
        | CAP_WRITE 
        | CAP_FS 
        | CAP_NET 
        | CAP_DEVICE 
        | CAP_ADMIN;

    // 3. Регистрируем в глобальном списке (через space_create)
}

// Получение системного пространства
space_t* get_system_space() {
    return system_space;
}