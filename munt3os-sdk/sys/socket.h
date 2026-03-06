#pragma once

#include <stdint.h>
#include <stddef.h>

#define AF_UNIX 1
#define SOCK_STREAM 1

struct sockaddr_un {
    uint16_t sun_family;
    char sun_path[108];
};

struct sockaddr {
    uint16_t sa_family;
    char sa_data[14];
};

#ifdef __cplusplus
extern "C" {
#endif

extern long __syscall(long num, ...);

#include "sysnums.h"

static inline int socket(int domain, int type, int protocol) {
    return (int)__syscall(SYS_SOCKET, domain, type, protocol);
}

static inline int bind(int fd, const struct sockaddr_un* addr, size_t addrlen) {
    return (int)__syscall(SYS_BIND, fd, addr, addrlen);
}

static inline int listen(int fd, int backlog) {
    return (int)__syscall(SYS_LISTEN, fd, backlog);
}

static inline int accept(int fd, struct sockaddr_un* addr, size_t* addrlen) {
    return (int)__syscall(SYS_ACCEPT, fd, addr, addrlen);
}

static inline int connect(int fd, const struct sockaddr_un* addr, size_t addrlen) {
    return (int)__syscall(SYS_CONNECT, fd, addr, addrlen);
}

#ifdef __cplusplus
}
#endif
