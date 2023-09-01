from socket import *
from json import *

BUFF_LEN = 400 # 最大报文长度
ADDR = ('', 18000)

server_socket = socket(AF_INET, SOCK_DGRAM)
server_socket.bind(ADDR)

print("...服务器启动成功...")

while 1:
    try:
        recvgram, client_addr = server_socket.recvfrom(BUFF_LEN)
    except timeout:
        continue
    print(f'收到来自IP地址为{client_addr[0]}，端口号为{client_addr[1]}的请求')
    message = loads(recvgram.decode())
    print(f'客户端的请求信息为：{message}')
    if(message['action'] == '获取信息'):
        # 查询数据库中的消息 拿到获取信息
        username = message['name']
        message = {
            'action' : '返回信息',
            'info' : f'{username}的性别为男'
        }
        sendgram = dumps(message).encode()
        server_socket.sendto(sendgram, client_addr)
