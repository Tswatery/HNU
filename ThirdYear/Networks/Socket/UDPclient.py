from socket import *
from json import *
from time import *

BUFF_LEN = 400
SERVER_ADDR  = ("127.0.0.1", 18000)

client_socket = socket(AF_INET, SOCK_DGRAM)
client_socket.settimeout(2)

message = {
    'action': '获取信息',
    'name' : ''
}

while 1:
    name = input("请输入您要查询的姓名：")
    message['name'] = name
    sendgram = dumps(message).encode()
    client_socket.sendto(sendgram, SERVER_ADDR)
    print('客户端发送信息')
    for i in range(3):
        print('*', end = '')
        sleep(1)
        if i == 2:print()
    try:
        recvgram, server = client_socket.recvfrom(BUFF_LEN)
        message = loads(recvgram.decode())
        print(f'服务端返回的信息为：{message}')
        print('-'*100)
    except timeout:
        print('接收消息超时')
