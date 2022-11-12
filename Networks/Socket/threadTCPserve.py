from socket import *
from threading import Thread

IP = ''
PORT = 50000
BUFLEN = 512

# �������߳�ִ�еĺ�����ÿ���̸߳����һ���ͻ��˽���ͨ��
def clientHandler(dataSocket,addr):
    while True:
        recved = dataSocket.recv(BUFLEN)
        # ���Է��ر����ӵ�ʱ�򣬷��ؿ��ַ���
        if not recved:
            print(f'�ͻ���{addr} �ر�������' )
            break

        # ��ȡ���ֽ�������bytes���ͣ���Ҫ����Ϊ�ַ���
        info = recved.decode()
        print(f'�յ�{addr}��Ϣ�� {info}')

        dataSocket.send(f'����˽��յ�����Ϣ {info}'.encode())

    dataSocket.close()

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
