from socket import *
import sys, os
from time import *

IP = '127.0.0.1'
SERVER_PORT = 50000
BUFLEN = 1024
client_socket = socket(AF_INET, SOCK_STREAM)
client_socket.connect((IP, SERVER_PORT))

def sendfile():
    global client_socket
    path = input('�������ļ��ľ���·����\n')
    file_name = os.path.basename(path) # ��ȡ�ļ�����
    file_size = os.stat(path).st_size
    info = file_name + '|' + str(file_size)
    client_socket.send(f'{info}'.encode())
    message = client_socket.recv(BUFLEN) # ���յ�ȷ����Ϣ
    print(message.decode())
    # ��ʼ�����ļ�
    send_size = 0
    f = open(path, 'rb')
    flag = True
    while flag:
        if send_size + BUFLEN > file_size:
            data = f.read(file_size-send_size)
            flag = False
        else:
            data = f.read(BUFLEN)
            send_size += 1024
        client_socket.send(data)
    
    message = client_socket.recv(BUFLEN)
    print(message.decode())
    f.close()

def recvfile(): # �����ļ�
    global client_socket
    message = client_socket.recv(BUFLEN)
    print(message.decode())
    message = input('������Ҫ�ӷ�������ص��ļ���: ')
    client_socket.send(message.encode())
    print('...�ͻ��˵ȴ�...')
    recvdata = client_socket.recv(BUFLEN).decode()
    # ��ȡ�ļ���
    print(recvdata)
    file_name, file_size = recvdata.split('|')
    client_socket.send('�յ�'.encode())
    recv_size = 0
    file_dir = os.path.join(r'C:\Users\XFL\Desktop\�ͻ���\���յ��ļ�', message)
    f = open(file_dir, 'wb')
    flag = True
    while flag:
        if int(file_size) > recv_size:
            data = client_socket.recv(BUFLEN)
            recv_size += len(data)
            f.write(data)
        else:
            recv_size = 0
            flag = False
    client_socket.send('�������'.encode())
    print('���ճɹ�')
    f.close()

def chat():
    global client_socket
    while 1:
        sendmessage = input(">>>")
        if sendmessage == 'exit':
            client_socket.send(sendmessage.encode())
            # sleep(0.1) # ��ֹ̫����Щ�ַ�û�����
            print('���շ����쵽�˽���')
            break
        elif not sendmessage:
            continue
        client_socket.send(sendmessage.encode())
        recvmessage = client_socket.recv(BUFLEN)
        if not recvmessage:
            continue
        print(f'��������������Ϣ��\n{recvmessage.decode()}')

while 1:
    FLAG = input('''
        ���������ִ������\n
        0.�����ļ� 1.�����ļ� 2.������Ϣ��\n
    ''')
    client_socket.send(FLAG.encode())
    if FLAG == '1':
        sendfile()
    elif FLAG  == '0':
        recvfile()
    else:
        chat()
sk.close()
