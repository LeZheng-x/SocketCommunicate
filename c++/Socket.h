//
// Created by zll-yyds on 12/19/23.
//

#ifndef SOCKET_CLIENT_H
#define SOCKET_CLIENT_H
#include <stdio.h>
#include <cstring>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <chrono>
#include <thread>
#include <string>
#include <iostream>
#define DEST_PORT 8000  //端口
#define DSET_IP_ADDRESS  "127.0.0.1"  //服务端IP地址
namespace Socket {

    struct  Data{
//        char  msg[1024];
        time_t timeStamp; //ms级
        double kp ;
    };


    class Trans {
    public:

        Trans(bool ifServer,std::time_t codeInitTime_){
            init(ifServer);
            codeInitTime=codeInitTime_;
        }

        ~ Trans(){
            close(sock_fd);
        }

        /**
         * @return: [true] Send Success
         *          [false] Send Failed
         * @param: data_  发送数据
         * */
        bool sendData(const Data  data_);

        /**
         * @return: [true] Recv Success
         *          [false] Recv Failed
         * @param: data_  接收数据
         * */
        bool recvData(Data & data_);

    private:
        int sock_fd;  /* socket文件描述符 */
        struct sockaddr_in sockaddrIn;
        socklen_t len;
        std::time_t codeInitTime;
        void init(bool ifServer); //0:Trans 1:Server
    };


} // Trans

#endif //SOCKET_CLIENT_H
