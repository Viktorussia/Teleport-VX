#ifndef VX_LOG_H
#define VX_LOG_H

// Уровни логирования
typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
} log_level_t;

// Инициализация логгера ядра
void log_init();

// Базовая функция записи
void log_write(log_level_t level, const char *message);

// Удобные обёртки
void log_debug(const char *message);
void log_info(const char *message);
void log_warn(const char *message);
void log_error(const char *message);

#endif
