#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>


int main(int argc, char *argv[])
{
    printf("tcp server begin\r\n");
    for (int i = 0; i < argc; i++) {
        printf("argc%d:%s\r\n", i, argv[i]);
    }

    if (argc != 3) {
        printf("tcp server usage: a.out <ip_address> <listen_port>");
        return 0;
    }

    uint16_t server_port = atoi(argv[2]);
    printf("port is:%u address is:%s\r\n", server_port, argv[1]);

    /***************************/

    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0) {
        printf("tcp server socket err\r\n");
        return -1;
    }

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
        printf("tcp server get addr failed.\r\n");
        close(listen_fd);
        return -1;
    }

    int ret = bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret != 0) {
        printf("tcp server bind failed. ret:%d errno:%d:%s\r\n", ret, errno, strerror(errno));
        close(listen_fd);
        return -1;
    }

    ret = listen(listen_fd, 1);
    if (ret != 0) {
        printf("tcp server listen failed. ret:%d errno:%d:%s\r\n", ret, errno, strerror(errno));
        close(listen_fd);
        return -1;
    }

    struct sockaddr_in client_addr;
    socklen_t len;
    int conn_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &len);
    char buff[64] = {0};
    printf("tcp server connection from:%s, port:%d\r\n",
        inet_ntop(AF_INET, &client_addr.sin_addr, buff, sizeof(buff)),
        ntohs(client_addr.sin_port));

    snprintf(buff, sizeof(buff), "server writes something:%d\r\n", 123);
    write(conn_fd, buff, strlen(buff));

    close(conn_fd);
    close(listen_fd);

    return 0;
}