#ifndef __COMMON_H__
#define __COMMON_H__

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define GRANDE 0xFF

#ifdef __cplusplus
extern "C" {
#endif

    void enviaStr(int server_fd, char *str);
    char* leeStr(int server_fd);

#ifdef __cplusplus
}
#endif

#endif
