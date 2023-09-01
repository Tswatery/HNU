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
    path = input('请输入文件的绝对路径：\n')
    file_name = os.path.basename(path) # 获取文件名称
    file_size = os.stat(path).st_size
    info = file_name + '|' + str(file_size)
    client_socket.send(f'{info}'.encode())
    message = client_socket.recv(BUFLEN) # 接收到确认信息
    print(message.decode())
    # 开始发送文件
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

def recvfile(): # 接收文件
    global client_socket
    message = client_socket.recv(BUFLEN)
    print(message.decode())
    message = input('请输入要从服务端下载的文件名: ')
    client_socket.send(message.encode())
    print('...客户端等待...')
    recvdata = client_socket.recv(BUFLEN).decode()
    # 获取文件名
    print(recvdata)
    file_name, file_size = recvdata.split('|')
    client_socket.send('收到'.encode())
    recv_size = 0
    file_dir = os.path.join(r'C:\Users\XFL\Desktop\客户端\接收的文件', message)
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
    client_socket.send('下载完成'.encode())
    print('接收成功')
    f.close()

def chat():
    global client_socket
    while 1:
        sendmessage = input(">>>")
        if sendmessage == 'exit':
            client_socket.send(sendmessage.encode())
            # sleep(0.1) # 防止太快有些字符没有输出
            print('今日份聊天到此结束')
            break
        elif not sendmessage:
            continue
        client_socket.send(sendmessage.encode())
        recvmessage = client_socket.recv(BUFLEN)
        if not recvmessage:
            continue
        print(f'服务器发来的消息：\n{recvmessage.decode()}')

while 1:
    FLAG = input('''
        请输入数字代表服务：\n
        0.接收文件 1.发送文件 2.发送消息：\n
    ''')
    client_socket.send(FLAG.encode())
    if FLAG == '1':
        sendfile()
    elif FLAG  == '0':
        recvfile()
    else:
        chat()
sk.close()
