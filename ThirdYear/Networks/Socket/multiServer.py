from socket import *
from threading import Thread
import os

IP = ''
PORT = 50000
BUFLEN = 512

# 这是新线程执行的函数，每个线程负责和一个客户端进行通信
def clientHandler(dataSocket,addr):
    while True:
        FLAG = dataSocket.recv(BUFLEN).decode()
        if FLAG == '0':
            dataSocket.send('服务端准备开始发送文件...'.encode())
            path = dataSocket.recv(BUFLEN).decode() 
            # 从客户端读取文件名
            file_name = os.path.join(r'C:\Users\XFL\Desktop\服务端', path)
            file_size = os.stat(file_name).st_size
            info = file_name + '|' + str(file_size)
            dataSocket.send(info.encode())
            message = dataSocket.recv(BUFLEN) # 接收到确认信息
            # 开始发送文件
            send_size = 0
            f = open(file_name, 'rb')
            flag = True
            while flag:
                if send_size + BUFLEN > file_size:
                    data = f.read(file_size-send_size)
                    flag = False
                else:
                    data = f.read(BUFLEN)
                    send_size += BUFLEN
                dataSocket.send(data)
            
            dataSocket.recv(BUFLEN)
            f.close()
        if FLAG == '1': # 接收文件
            print('服务器等待')
            pre_data = dataSocket.recv(BUFLEN).decode()
            file_name, file_size = pre_data.split('|')
            dataSocket.send(f'服务端收到客户端发送的有关 {pre_data} 的文件信息'.encode())
            recv_size = 0
            file_dir = os.path.join(r'C:\Users\XFL\Desktop\服务端', file_name)
            print(f'服务端存放文件路径为： {file_dir}') # test
            f = open(file_dir, 'wb')
            while 1:
                if int(file_size) > recv_size:
                    data = dataSocket.recv(BUFLEN)
                    recv_size += len(data)
                    f.write(data)
                else:
                    recv_size = 0
                    break
            dataSocket.send('服务端下载完成'.encode())
            f.close()
        if FLAG == '2':
            print('开始聊天')
            while 1:
                data = dataSocket.recv(BUFLEN)
                print(f'客户端发来消息：\n{data.decode()}')
                if not data:
                    continue
                elif data.decode() == 'exit':
                    print('今日份聊天到此结束')
                    break
                message = input('>>>')
                print(message)
                dataSocket.send(message.encode())

# 实例化一个socket对象 用来监听客户端连接请求
listenSocket = socket(AF_INET, SOCK_STREAM)

# socket绑定地址和端口
listenSocket.bind((IP, PORT))

listenSocket.listen(8)
print(f'服务端启动成功，在{PORT}端口等待客户端连接...')

while True:
    # 在循环中，一直接受新的连接请求
    dataSocket, addr = listenSocket.accept()     # Establish connection with client.
    addr = str(addr)
    print(f'一个客户端 {addr} 连接成功' )

    # 创建新线程处理和这个客户端的消息收发
    th = Thread(target=clientHandler,args=(dataSocket,addr))
    th.start()

listenSocket.close()
