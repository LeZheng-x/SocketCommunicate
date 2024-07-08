import socket            
import numpy as np 

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)      
 

port = 1234              
 
s.bind(('', port))        

s.listen(5)    
 
#send message
arr = np.array([1], dtype=np.float64) #pose 
arr_bytes = arr.tobytes()    
c, addr = s.accept()    
c.send(arr_bytes)

while True:

    #recv message 
    received_data = c.recv(1024)  # 假设接收缓冲区大小为 1024，根据实际情况调整
    received_arr = np.frombuffer(received_data, dtype=np.float64)  # 假设数组元素为 int32 类型
    if received_arr.size==0:
        continue
    print(received_arr)
    pass  

c.close()