from socket import *
from time import *

IP = '127.0.0.1'
SERVE_PORT = 50000
BUFLEN = 1024

dataSocket = socket(AF_INET, SOCK_STREAM) # 初始化一个socket
dataSocket.connect((IP, SERVE_PORT)) # 连接服务器端的socket

print("...客户端启动，正在准备与客户端连接...")

while 1:
    toSend = input(">>>")
    if toSend == 'exit':
        print('客户端关闭连接')
        break
    print('正在向服务器端发送消息')
    for i in range(3):
        print('.', end = "")
        sleep(1)
        if(i == 2): print()

    dataSocket.send(toSend.encode())
    recved = dataSocket.recv(BUFLEN)
    if not recved: 
        break
    print(f'服务器返回的确认信息为：{recved.decode()}')
dataSocket.close()
