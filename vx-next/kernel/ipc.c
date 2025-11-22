#include "ipc.h"

// Глобальная очередь сообщений
static message_t *msg_queue_head = 0;

// Инициализация IPC
void ipc_init() {
    msg_queue_head = 0;
}

// Отправка сообщения (пока заглушка)
int ipc_send(int src_task, int dst_task, msg_type_t type, void *payload) {
    return 0;
}

// Получение сообщения (заглушка)
message_t* ipc_receive(int dst_task) {
    return 0;
}