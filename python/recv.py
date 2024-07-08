import socket            
import numpy as np
import time
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)        
 
port = 1234               
 
s.connect(('127.0.0.1', port))

#recv message 
received_data = s.recv(1024)  # 假设接收缓冲区大小为 1024，根据实际情况调整
received_arr = np.frombuffer(received_data, dtype=np.float64)  # 假设数组元素为 int32 类型
print(received_arr)

while(1):

    #send message
    arr = np.array([1.4, 5, 6,3,4,5,6], dtype=np.float64) #pose 
    arr_bytes = arr.tobytes()
    s.send(arr_bytes)
    time.sleep(1)
    # break
# close the connection
s.close()  