import socket


addrinfo = socket.getaddrinfo(
                    '127.0.0.1',
                    50000,
                    socket.AF_UNSPEC,
                    socket.SOCK_DGRAM,
                    socket.IPPROTO_UDP,
)[0]
sock_server = socket.socket(addrinfo[0], addrinfo[1], addrinfo[2])
sock_server.bind(addrinfo[4])
sock_client = socket.socket(addrinfo[0], addrinfo[1], addrinfo[2])

try:
    for i in range(1000000):
        sock_client.sendto(b"\x00", addrinfo[4])
        sock_server.recvfrom(16384)
        #raise ValueError()
except Exception:
    print(i)
    raise
