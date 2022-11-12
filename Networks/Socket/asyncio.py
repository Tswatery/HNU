async def handle_echo(reader, writer):
    addr = writer.get_extra_info() # 获取
    while True:
        data = await reader.read(100)
        if not data:
            print(f'客户端{addr}关闭了连接')
            writer.close()
            break

        message = data.decode()
        print(f'收到{addr}信息： {message}')

        writer.write(data)
