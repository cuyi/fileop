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
    printf("tcp client begin\r\n");
    for (int i = 0; i < argc; i++) {
        printf("argc%d:%s\r\n", i, argv[i]);
    }

    if (argc != 5) {
        printf("tcp client usage: a.out <server_ip_address> <server_listen_port> <client_ip_address> <client_port>");
        return 0;
    }

    uint16_t server_port = atoi(argv[2]);
    uint16_t client_port = atoi(argv[4]);
    printf("server port is:%u client port is:%u\r\n", server_port, client_port);
    /***************************/



    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        printf("tcp client socket err\r\n");
        return -1;
    }

    struct sockaddr_in client_addr;
    bzero(&client_addr, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(client_port);
    if (inet_pton(AF_INET, argv[1], &client_addr.sin_addr) <= 0) {
        printf("tcp client get client addr failed.\r\n");
        close(client_fd);
        return -1;
    }

    int ret = bind(client_fd, (struct sockaddr *)&client_addr, sizeof(client_addr));
    if (ret != 0) {
        printf("tcp client bind failed. ret:%d errno:%d:%s\r\n", ret, errno, strerror(errno));
        close(client_fd);
        return -1;
    }

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
        printf("tcp client get server addr failed.\r\n");
        close(client_fd);
        return -1;
    }

    ret = connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret != 0) {
        printf("tcp client connect failed. ret:%d errno:%d:%s\r\n", ret, errno, strerror(errno));
        close(client_fd);
        return -1;
    }

    char buff[64] = {0};
    int n = read(client_fd, buff, sizeof(buff) - 1);
    if (n <= 0) {
        printf("tcp client read failed after connected. ret:%d errno:%d:%s\r\n", ret, errno, strerror(errno));
        close(client_fd);
        return -1;
    }
    printf("tcp client read from server:%s\r\n", buff);
    
    close(client_fd);
    return 0;
}