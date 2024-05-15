import socket
import argparse
import time

def send_ping(port):
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('127.0.0.1', port))

    for i in range(1, 11):
        client_socket.sendall(b'PING')
        print(f"{i} : sent PING...")
        response = client_socket.recv(1024)
        if response:
            print(f"{i} : received {response.decode()}")

    client_socket.close()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Simple Client")
    parser.add_argument("--port", type=int, help="Port for the client to connect to")
    args = parser.parse_args()
    send_ping(args.port)
