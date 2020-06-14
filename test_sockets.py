import socket
import sys


for port in range(49152, 65536):
    addrinfo = socket.getaddrinfo(
        "127.0.0.1", port, socket.AF_UNSPEC, socket.SOCK_DGRAM, socket.IPPROTO_UDP
    )[0]
    sock_server = socket.socket(addrinfo[0], addrinfo[1], addrinfo[2])
    try:
        sock_server.bind(addrinfo[4])
    except socket.error as e:
        print("Port {}: {}".format(port, e))

sys.exit(0)
sock_client = socket.socket(addrinfo[0], addrinfo[1], addrinfo[2])

try:
    for i in range(1000000):
        sock_client.sendto(b"\x00", addrinfo[4])
        sock_server.recvfrom(16384)
except Exception:
    print(i)
    raise
