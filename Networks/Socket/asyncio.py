async def handle_echo(reader, writer):
    addr = writer.get_extra_info() # ��ȡ
    while True:
        data = await reader.read(100)
        if not data:
            print(f'�ͻ���{addr}�ر�������')
            writer.close()
            break

        message = data.decode()
        print(f'�յ�{addr}��Ϣ�� {message}')

        writer.write(data)
