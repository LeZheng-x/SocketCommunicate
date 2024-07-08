#include <iostream>
#include "Socket.h"
#include<thread>
#include <chrono>
#include <time.h>

std::time_t GetTimeStamp()
{
    std::chrono::time_point<std::chrono::system_clock,std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());//获取当前时间点
    std::time_t timestamp =  tp.time_since_epoch().count(); //计算距离1970-1-1,00:00的时间长度
    return timestamp;
}

void Send(std::time_t codeInitTime){
    Socket::Trans client(false,codeInitTime);

    while (true){
        Socket::Data data;

        data.timeStamp = GetTimeStamp()-codeInitTime; //时间戳 （程序运行时间）
        data.kp= 0.5; //一些需要记录的参数 ， 在Socket.h中直接添加


        bool ifSuccess=client.sendData(data);

        if(ifSuccess){
            std::cout<<"Send Succeed"<<std::endl<<std::endl;
        }
        else{
            std::cout<<"Send Failed"<<std::endl<<std::endl;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1)); //1hz频率发送
    }
}

void Recv(std::time_t codeInitTime){
    Socket::Trans server(true,codeInitTime);
    while(true){
        Socket::Data data;
        bool ifSuccess= server.recvData(data);
        if(ifSuccess){
            std::cout<<"Recv Success: "<<data.timeStamp<<" "<<data.kp<<std::endl<<std::endl;
        }
        else{
            std::cout<<"Recv Failed"<<std::endl<<std::endl;
        }
    }
}


int main() {

    time_t timestampInit =GetTimeStamp(); //初始时间

    std::thread t1(Recv, timestampInit);
    std::cout << "接收线程中显示子线程id为" << t1.get_id() << std::endl;

    std::thread t2(Send,timestampInit);
    std::cout << "发送线程中显示子线程id为" << t2.get_id() << std::endl;


    t2.join();
    t1.join();
    return 0;
}
