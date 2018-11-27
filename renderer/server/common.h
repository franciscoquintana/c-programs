#ifndef __COMMON_H__
#define __COMMON_H__

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <uuid/uuid.h>

typedef struct {
  uuid_t id;
  int x, y;
  float angle, speed;
} CarInfo;

typedef struct {
  int up, left, right, down;
} MoveCar;

typedef struct {
  MoveCar moveinfo;
  CarInfo info;
} Client;

#ifdef __cplusplus
extern "C" {
#endif

    void enviaStr(int server_fd, char *str);
    char* leeStr(int server_fd);
    int getTimeMs();

#ifdef __cplusplus
}
#endif

#endif
