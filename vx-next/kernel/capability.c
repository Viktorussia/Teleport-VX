#include "capability.h"

// Проверка capability
int cap_check(unsigned int capabilities, unsigned int required) {
    return (capabilities & required) == required;
}

// Добавление capability
void cap_add(unsigned int *capabilities, unsigned int cap) {
    *capabilities |= cap;
}

// Удаление capability
void cap_remove(unsigned int *capabilities, unsigned int cap) {
    *capabilities &= ~cap;
}