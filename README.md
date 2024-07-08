# SocketCommunicate
 Communication within LAN based on socket with c++ 17 and cmake project.Also with python project.  
This simulates communication within the LAN through multi-threading and encapsulates Socket usage into classes. After configuration, users can only focus on the use of receiving and sending functions.
# How to run 
[c++]:   
mkdir build  
cd build  
cmake ..  
./socket

[python]:  
python **.py

# How to configure 
1.Configure your port and IP address in the Socket.h file  
2.Customize the content of the Data struct in the Socket.h file  

# Notes
Demos for receiving and sending are given in the main.cpp file. Please customize and modify them to achieve the desired effect.