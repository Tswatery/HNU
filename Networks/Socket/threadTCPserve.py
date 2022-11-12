from socket import *
from threading import Thread

IP = ''
PORT = 50000
BUFLEN = 512

# 这是新线程执行的函数，每个线程负责和一个客户端进行通信
def clientHandler(dataSocket,addr):
    while True:
        recved = dataSocket.recv(BUFLEN)
        # 当对方关闭连接的时候，返回空字符串
        if not recved:
            print(f'客户端{addr} 关闭了连接' )
            break

        # 读取的字节数据是bytes类型，需要解码为字符串
        info = recved.decode()
        print(f'收到{addr}信息： {info}')

        dataSocket.send(f'服务端接收到了信息 {info}'.encode())

    dataSocket.close()

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
