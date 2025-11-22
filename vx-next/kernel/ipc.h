#ifndef VX_IPC_H
#define VX_IPC_H

// Тип сообщения
typedef enum {
    MSG_GENERIC,
    MSG_SYSTEM,
    MSG_SERVICE,
    MSG_USER
} msg_type_t;

// Структура сообщения
typedef struct message {
    int src_task;        // отправитель
    int dst_task;        // получатель
    msg_type_t type;     // тип сообщения
    void *payload;       // указатель на данные
    struct message *next;
} message_t;

// Инициализация IPC-подсистемы
void ipc_init();

// Отправка сообщения
int ipc_send(int src_task, int dst_task, msg_type_t type, void *payload);

// Получение сообщения
message_t* ipc_receive(int dst_task);

#endif