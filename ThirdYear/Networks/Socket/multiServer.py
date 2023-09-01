from socket import *
from threading import Thread
import os

IP = ''
PORT = 50000
BUFLEN = 512

# �������߳�ִ�еĺ�����ÿ���̸߳����һ���ͻ��˽���ͨ��
def clientHandler(dataSocket,addr):
    while True:
        FLAG = dataSocket.recv(BUFLEN).decode()
        if FLAG == '0':
            dataSocket.send('�����׼����ʼ�����ļ�...'.encode())
            path = dataSocket.recv(BUFLEN).decode() 
            # �ӿͻ��˶�ȡ�ļ���
            file_name = os.path.join(r'C:\Users\XFL\Desktop\�����', path)
            file_size = os.stat(file_name).st_size
            info = file_name + '|' + str(file_size)
            dataSocket.send(info.encode())
            message = dataSocket.recv(BUFLEN) # ���յ�ȷ����Ϣ
            # ��ʼ�����ļ�
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
        if FLAG == '1': # �����ļ�
            print('�������ȴ�')
            pre_data = dataSocket.recv(BUFLEN).decode()
            file_name, file_size = pre_data.split('|')
            dataSocket.send(f'������յ��ͻ��˷��͵��й� {pre_data} ���ļ���Ϣ'.encode())
            recv_size = 0
            file_dir = os.path.join(r'C:\Users\XFL\Desktop\�����', file_name)
            print(f'����˴���ļ�·��Ϊ�� {file_dir}') # test
            f = open(file_dir, 'wb')
            while 1:
                if int(file_size) > recv_size:
                    data = dataSocket.recv(BUFLEN)
                    recv_size += len(data)
                    f.write(data)
                else:
                    recv_size = 0
                    break
            dataSocket.send('������������'.encode())
            f.close()
        if FLAG == '2':
            print('��ʼ����')
            while 1:
                data = dataSocket.recv(BUFLEN)
                print(f'�ͻ��˷�����Ϣ��\n{data.decode()}')
                if not data:
                    continue
                elif data.decode() == 'exit':
                    print('���շ����쵽�˽���')
                    break
                message = input('>>>')
                print(message)
                dataSocket.send(message.encode())

# ʵ����һ��socket���� ���������ͻ�����������
listenSocket = socket(AF_INET, SOCK_STREAM)

# socket�󶨵�ַ�Ͷ˿�
listenSocket.bind((IP, PORT))

listenSocket.listen(8)
print(f'����������ɹ�����{PORT}�˿ڵȴ��ͻ�������...')

while True:
    # ��ѭ���У�һֱ�����µ���������
    dataSocket, addr = listenSocket.accept()     # Establish connection with client.
    addr = str(addr)
    print(f'һ���ͻ��� {addr} ���ӳɹ�' )

    # �������̴߳��������ͻ��˵���Ϣ�շ�
    th = Thread(target=clientHandler,args=(dataSocket,addr))
    th.start()

listenSocket.close()
