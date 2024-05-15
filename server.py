import socket
import argparse

def create_server(port):
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('127.0.0.1', port))
    server_socket.listen()

    print(f"[server] : ready to accept data on port {port}...")

    while True:
        client_socket, _ = server_socket.accept()
        data = client_socket.recv(1024)
        if data == b'PING':
            print("[proxy] : PING received from client")
            client_socket.sendall(b'PONG')
        client_socket.close()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Simple Server")
    parser.add_argument("--port", type=int, help="Port for the server to listen on")
    args = parser.parse_args()
    create_server(args.port)
