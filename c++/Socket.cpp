//
// Created by zll-yyds on 12/19/23.
//

#include "Socket.h"

namespace Socket {
    void Trans::init(bool ifServer) {
        /* 将套接字和IP、端口绑定 */
        sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock_fd < 0) {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }
        memset(&sockaddrIn, 0, sizeof(sockaddrIn));
        sockaddrIn.sin_family = AF_INET; //IPV4
        sockaddrIn.sin_port = htons(DEST_PORT); //端口
        if(ifServer){
            //服务端IP默认自己，客户端需指定服务端IP地址。二者端口应相同
            /* INADDR_ANY表示不管是哪个网卡接收到数据，只要目的端口是SERV_PORT，就会被该应用程序接收到 */
            sockaddrIn.sin_addr.s_addr = htonl(INADDR_ANY);  //自动获取IP地址

            /* 绑定socket */
            if(bind(sock_fd, (struct sockaddr *)&sockaddrIn, sizeof(sockaddrIn)) < 0)
            {
                perror("bind error:");
//                exit(1);
            }
        }
        else{
            sockaddrIn.sin_addr.s_addr = inet_addr(DSET_IP_ADDRESS); //服务端IP
        }

        len = sizeof(sockaddrIn);

    }

    bool Trans::sendData(const Data data_) {

        char  buf[1024]={0};
        memcpy(buf, &data_, sizeof(Data));

        int send_num = sendto(sock_fd, buf, sizeof(buf), 0, (struct sockaddr *)&sockaddrIn, len);
        if(send_num < 0){
            return false;
        }
        else {
            return true;
        }
    }

    bool Trans::recvData(Data & data_) {
//        printf("server is waitting data ...\n");
        char  buf[1024];

        int recv_num = recvfrom(sock_fd, buf, sizeof (buf), 0, (struct sockaddr *)&sockaddrIn, &len);

        data_ = * (Data*)buf;

        if(recv_num < 0)
        {
            printf("recv failed\n");
            return false;
        }

        printf("server receive %d bytes\n", recv_num);
        return true;
    }

} // Trans