from socket import *

IP = ""
PORT = 50000
BUFLEN = 512

listenSocket = socket(AF_INET, SOCK_STREAM)
# ��ʼ��һ��socket����

listenSocket.bind((IP, PORT)) # ��

listenSocket.listen(8) # ʹsocket���ڼ���״̬ ����ǿͻ���

print(f'����������ɹ�����{PORT}�˿ڵȴ��ͻ�������...')

dataSocket, addr = listenSocket.accept()
print(f'��������IP��ַΪ{addr[0]}���˿ں�Ϊ{addr[1]}�ͻ�������')

while 1:
    recved = dataSocket.recv(BUFLEN)
    if not recved:
        break # �յĻ���break

    info = recved.decode() # ����
    print(f'���ܵ��ͻ��˵���Ϣ��{info}')

    dataSocket.send(f'����˽��յ�����Ϣ: {info}'.encode()) 

dataSocket.close()
listenSocket.close()
