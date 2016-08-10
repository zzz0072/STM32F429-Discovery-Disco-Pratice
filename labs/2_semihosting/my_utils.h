#ifndef MY_UTIL_H
#define MY_UTIL_H
#include <stddef.h>
#include <stm32f4xx.h>
#include "stm32f4xx_conf.h"
#define STDIN  (0)
#define STDOUT (1)

int strlen(char *);
void memset(void *s, int c, int n);
size_t host_read(int fd, void *buf, size_t count);
size_t host_write(int fd, const void *buf, size_t count);
#endif
