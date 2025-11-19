#ifndef VX_SPACE_H
#define VX_SPACE_H

// Типы пространств
typedef enum {
    SPACE_SYSTEM,   // системное пространство
    SPACE_USER,     // пользовательское пространство
    SPACE_SERVICE   // служебное пространство
} space_type_t;

// Структура Space
typedef struct space {
    int space_id;            // уникальный ID пространства
    space_type_t type;       // тип (system/user/service)

    // Список задач в этом Space
    struct task *task_list;

    // Будущая карта памяти
    void *memory_map;

    // Capability-ключи
    unsigned int capabilities;

    // Ссылка на следующее пространство (односвязный список)
    struct space *next;
} space_t;

// Функции управления Space
space_t* space_create(space_type_t type);
void space_destroy(int space_id);
space_t* space_get(int space_id);

#endif