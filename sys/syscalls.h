#ifndef __SYSCALLS_H
#define __SYSCALLS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>

extern long __syscall(long num, ...);

#include "sysnums.h"

int open(const char *pathname, int flags, mode_t mode);
int close(int fd);
ssize_t write(int fd, const void *buf, size_t count);
ssize_t read(int fd, void *buf, size_t count);
off_t lseek(int fd, off_t offset, int whence);
int ioctl(int fd, int request, void *arg);
void _exit(int status);
void *sbrk(intptr_t increment);

#ifdef __cplusplus
}
#endif

#endif // __SYSCALLS_H