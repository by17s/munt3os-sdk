#include <sys/types.h>
#include <stdint.h>

#include "sysnums.h"
#include "sysdef.h"

extern long __syscall(long num, ...);

int open(const char *pathname, int flags, mode_t mode) {
    return (int)__syscall(SYS_OPEN, pathname, flags, mode);
}

int close(int fd) {
    return (int)__syscall(SYS_CLOSE, fd, 0, 0);
}

ssize_t write(int fd, const void *buf, size_t count) {
    return (ssize_t)__syscall(SYS_WRITE, fd, buf, count);
}

ssize_t read(int fd, void *buf, size_t count) {
    return (ssize_t)__syscall(SYS_READ, fd, buf, count);
}

off_t lseek(int fd, off_t offset, int whence) {
    return (off_t)__syscall(SYS_LSEEK, fd, offset, whence);
}

int ioctl(int fd, int request, void *arg) {
    return (int)__syscall(SYS_IOCTL, fd, request, arg);
}

int stat(const char *restrict pathname, struct stat *restrict statbuf) {
    return (int)__syscall(SYS_STAT, pathname, statbuf, 0);
}

int fstat(int fd, struct stat *statbuf) {
    return (int)__syscall(SYS_FSTAT, fd, statbuf, 0);
}

void _exit(int status) {
    __syscall(SYS_EXIT, status);
    while (1);
}

int readdir(int fd, struct dirent *dirp, uint32_t index) {
    return (int)__syscall(SYS_READDIR, fd, dirp, index);
}

void *sbrk(intptr_t increment) {
    static void *current_brk = 0;
    if (current_brk == 0) {
        current_brk = (void *)__syscall(SYS_BRK, 0);
    }
    void *prev_brk = current_brk;
    if (increment != 0) {
        current_brk = (void *)__syscall(SYS_BRK, (uintptr_t)current_brk + increment);
    }
    return prev_brk;
}

// === Access & Tasks === //

int vexecve(const char* path, char **argv) {
    return (int)__syscall(SYS_EXECVE, path, argv);
}

int chdir(const char* dir) {
    return (int)__syscall(SYS_CHDIR, dir);
}

int setuid(uid_t uid) {
    return (int)__syscall(SYS_SETUID, uid, 0, 0);
}

int setgid(gid_t gid) {
    return (int)__syscall(SYS_SETGID, gid, 0, 0);
}

int chown(const char* path, uid_t uid, gid_t gid) {
    return (int)__syscall(SYS_CHOWN, path, uid, gid);
}

int execve_module(const char* path, void* arg) {
    return (int)__syscall(SYS_EXECVE_MODULE, path, arg);
}