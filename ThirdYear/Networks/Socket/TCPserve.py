from socket import *

IP = ""
PORT = 50000
BUFLEN = 512

listenSocket = socket(AF_INET, SOCK_STREAM)
# 初始化一个socket对象

listenSocket.bind((IP, PORT)) # 绑定

listenSocket.listen(8) # 使socket处于监听状态 这才是客户端

print(f'服务端启动成功，在{PORT}端口等待客户端连接...')

dataSocket, addr = listenSocket.accept()
print(f'接受来自IP地址为{addr[0]}，端口号为{addr[1]}客户端连接')

while 1:
    recved = dataSocket.recv(BUFLEN)
    if not recved:
        break # 空的话就break

    info = recved.decode() # 解码
    print(f'接受到客户端的信息：{info}')

    dataSocket.send(f'服务端接收到了信息: {info}'.encode()) 

dataSocket.close()
listenSocket.close()
