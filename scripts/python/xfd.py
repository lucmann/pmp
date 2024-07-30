#!/usr/bin/env python3

# Copyright (C) 2024 Luc Ma
#
# SPDX-License-Identifier: GPL-2.0


import os
import socket, array
import threading
import time
from retry import retry

# Create a Unix Domain socket with address family AF_UNIX (note that AF_INET by default)

SOCKET_BINDING_ADDR = "/tmp/sock"

class Client(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        self.sock = socket.socket(socket.AF_UNIX)

    def send_fds(self, buffer, fds):
        return self.sock.sendmsg(buffer, [(socket.SOL_SOCKET, socket.SCM_RIGHTS, array.array("i", fds))])

    @retry(tries=100, delay=1)
    def connect(self, address):
        try:
            self.sock.connect(address)
        except Exception as e:
            print(e)

    def run(self):
        self.connect(SOCKET_BINDING_ADDR)
        print("Connected")

        # Obtain two file descriptors both in read only mode
        fd1 = os.open("/tmp/news1.txt", os.O_RDONLY)
        fd2 = os.open("/tmp/news2.txt", os.O_RDONLY)

        msg = "hi"
        msgb = bytes(msg, 'ascii')
        self.send_fds([msgb], [fd1, fd2])

        while True:
            data = self.sock.recv(1024)

            if data != b'':
                print("Server respone:")
                print(data)
            else:
                print("Connection closed by server")
                break

        self.sock.close()


class Server(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        self.sock = socket.socket(socket.AF_UNIX)
        # Used to ensure server thread doesn't terminate until client stops
        self.event = threading.Event()

    def recv_fds(self, sock, bufsize, maxfds):
        fds = array.array("i")  # Array of ints
        msg, ancillary, flags, addr = sock.recvmsg(bufsize, socket.CMSG_LEN(maxfds * fds.itemsize))
        for cmsg_level, cmsg_type, cmsg_data in ancillary:
            if cmsg_level == socket.SOL_SOCKET and cmsg_type == socket.SCM_RIGHTS:
                fds.frombytes(cmsg_data[:len(cmsg_data) - (len(cmsg_data) % fds.itemsize)])
        return msg, list(fds)

    def run(self):
        os.unlink(SOCKET_BINDING_ADDR) # avoid [Errno 98]: Address already in use
        self.sock.bind(SOCKET_BINDING_ADDR)
        self.sock.listen()
        print("Unix domain socket waiting for client connections ...")

        while not self.event.is_set():
            sock, addr = self.sock.accept()

            while True:
                msg, fds = self.recv_fds(sock, 1024, 2)

                for fd in fds:
                    print(os.read(fd, 8))

                sock.send("Great ... have read all news".encode())
                break

        self.sock.close()


if __name__ == '__main__':
    server = Server()
    client = Client()

    server.start()
    # Ensure server starts firstly
    time.sleep(1)
    client.start()

    server.event.set()
    server.join()
    client.join()

    print("Done")

