from socket import *
from time import *

IP = '127.0.0.1'
SERVE_PORT = 50000
BUFLEN = 1024

dataSocket = socket(AF_INET, SOCK_STREAM) # ��ʼ��һ��socket
dataSocket.connect((IP, SERVE_PORT)) # ���ӷ������˵�socket

print("...�ͻ�������������׼����ͻ�������...")

while 1:
    toSend = input(">>>")
    if toSend == 'exit':
        print('�ͻ��˹ر�����')
        break
    print('������������˷�����Ϣ')
    for i in range(3):
        print('.', end = "")
        sleep(1)
        if(i == 2): print()

    dataSocket.send(toSend.encode())
    recved = dataSocket.recv(BUFLEN)
    if not recved: 
        break
    print(f'���������ص�ȷ����ϢΪ��{recved.decode()}')
dataSocket.close()
