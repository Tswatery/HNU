from socket import *
from json import *

BUFF_LEN = 400 # ����ĳ���
ADDR = ('', 18000)

server_socket = socket(AF_INET, SOCK_DGRAM)
server_socket.bind(ADDR)

print("...�����������ɹ�...")

while 1:
    try:
        recvgram, client_addr = server_socket.recvfrom(BUFF_LEN)
    except timeout:
        continue
    print(f'�յ�����IP��ַΪ{client_addr[0]}���˿ں�Ϊ{client_addr[1]}������')
    message = loads(recvgram.decode())
    print(f'�ͻ��˵�������ϢΪ��{message}')
    if(message['action'] == '��ȡ��Ϣ'):
        # ��ѯ���ݿ��е���Ϣ �õ���ȡ��Ϣ
        username = message['name']
        message = {
            'action' : '������Ϣ',
            'info' : f'{username}���Ա�Ϊ��'
        }
        sendgram = dumps(message).encode()
        server_socket.sendto(sendgram, client_addr)
