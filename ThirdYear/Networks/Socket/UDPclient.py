from socket import *
from json import *
from time import *

BUFF_LEN = 400
SERVER_ADDR  = ("127.0.0.1", 18000)

client_socket = socket(AF_INET, SOCK_DGRAM)
client_socket.settimeout(2)

message = {
    'action': '��ȡ��Ϣ',
    'name' : ''
}

while 1:
    name = input("��������Ҫ��ѯ��������")
    message['name'] = name
    sendgram = dumps(message).encode()
    client_socket.sendto(sendgram, SERVER_ADDR)
    print('�ͻ��˷�����Ϣ')
    for i in range(3):
        print('*', end = '')
        sleep(1)
        if i == 2:print()
    try:
        recvgram, server = client_socket.recvfrom(BUFF_LEN)
        message = loads(recvgram.decode())
        print(f'����˷��ص���ϢΪ��{message}')
        print('-'*100)
    except timeout:
        print('������Ϣ��ʱ')
