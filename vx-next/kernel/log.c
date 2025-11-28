#include "log.h"

// Размер кольцевого буфера сообщений
#define LOG_BUFFER_SIZE 128

// Максимальная длина одного сообщения
#define LOG_MESSAGE_MAX 80

// Кольцевой буфер
static char log_buffer[LOG_BUFFER_SIZE][LOG_MESSAGE_MAX];

// Позиция, куда писать следующее сообщение
static int log_write_pos = 0;

// Инициализация логгера
void log_init() {
    for (int i = 0; i < LOG_BUFFER_SIZE; i++) {
        log_buffer[i][0] = '\0';
    }
    log_write_pos = 0;
}

// Запись сообщения в буфер
void log_write(log_level_t level, const char *message) {
    // Не позволяем падать, если null
    if (!message) return;

    // Определяем текст уровня
    const char *lvl = "UNK";
    switch (level) {
        case LOG_DEBUG: lvl = "DBG"; break;
        case LOG_INFO:  lvl = "INF"; break;
        case LOG_WARN:  lvl = "WRN"; break;
        case LOG_ERROR: lvl = "ERR"; break;
    }

    // Формируем запись: "<LEVEL>: message"
    int i = 0;
    log_buffer[log_write_pos][i++] = '<';
    log_buffer[log_write_pos][i++] = lvl[0];
    log_buffer[log_write_pos][i++] = lvl[1];
    log_buffer[log_write_pos][i++] = lvl[2];
    log_buffer[log_write_pos][i++] = '>';
    log_buffer[log_write_pos][i++] = ' ';

    // Копируем само сообщение
    for (int j = 0; j < LOG_MESSAGE_MAX - 6 && message[j] != '\0'; j++) {
        log_buffer[log_write_pos][i++] = message[j];
    }

    // Завершаем строку
    log_buffer[log_write_pos][i] = '\0';

    // Сдвигаем указатель (кольцевой)
    log_write_pos++;
    if (log_write_pos >= LOG_BUFFER_SIZE)
        log_write_pos = 0;
}

// Удобные обёртки
void log_debug(const char *message) { log_write(LOG_DEBUG, message); }
void log_info(const char *message)  { log_write(LOG_INFO,  message); }
void log_warn(const char *message)  { log_write(LOG_WARN,  message); }
void log_error(const char *message) { log_write(LOG_ERROR, message); }
