import socket


for attempt in range(5):
    print("Attempt {}".format(attempt + 1))
    for port in range(1024, 65536):
        addrinfo = socket.getaddrinfo(
            "127.0.0.1", port, socket.AF_UNSPEC, socket.SOCK_DGRAM, socket.IPPROTO_UDP
        )[0]
        sock_server = socket.socket(addrinfo[0], addrinfo[1], addrinfo[2])
        try:
            sock_server.bind(addrinfo[4])
        except socket.error as e:
            print("  Port {}: {}".format(port, e))
