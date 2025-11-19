#ifndef VX_CAPABILITY_H
#define VX_CAPABILITY_H

// Capability flags
#define CAP_READ     0x01
#define CAP_WRITE    0x02
#define CAP_FS       0x04
#define CAP_NET      0x08
#define CAP_DEVICE   0x10
#define CAP_ADMIN    0x20

// Проверка, есть ли у пространства нужный capability
int cap_check(unsigned int capabilities, unsigned int required);

// Добавление capability
void cap_add(unsigned int *capabilities, unsigned int cap);

// Удаление capability
void cap_remove(unsigned int *capabilities, unsigned int cap);

#endif