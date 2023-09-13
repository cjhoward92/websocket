#include <cerrno>
#include <iostream>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include <fcntl.h>

#include "client/client.h"
#include "utilities/base64.h"

int main() {
    std::ostringstream str;
    str << "ws://localhost:18080";
    auto client = w_client::parse_uri(str.str());

    int status;
    struct addrinfo hints;
    struct addrinfo *servinfo;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((status = getaddrinfo("localhost", "18080", &hints, &servinfo)) != 0) {
        std::cerr << "getaddrinfo error: " << gai_strerror(status) << std::endl;
        exit(1);
    }

    int sockfd;
    if ((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) < 0) {
        freeaddrinfo(servinfo);
        std::cerr << "socket error: " << strerror(errno) << std::endl;
        exit(1);
    }

    if (connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) != 0) {
        close(sockfd);
        freeaddrinfo(servinfo);
        std::cerr << "connect error: " << strerror(errno) << std::endl;
        exit(1);
    }

    std::ostringstream msg_stream;
    msg_stream << "GET / HTTP/1.1\r\n";
    msg_stream << "Host: localhost:18080\r\n";
    msg_stream << "Upgrade: websocket\r\n";
    msg_stream << "Connection: Upgrade\r\n";
    msg_stream << "Sec-WebSocket-Key: x3JJHMbDL1EzLkh9GBhXDw==\r\n";
    msg_stream << "Sec-WebSocket-Version: 13\r\n\r\n";
    auto msg = msg_stream.str();

    if (send(sockfd, msg.c_str(), msg.length(), 0) < 0) {
        close(sockfd);
        freeaddrinfo(servinfo);
        std::cerr << "send error: " << strerror(errno) << std::endl;
        exit(1);
    }

    char buf[1024];
    size_t len;
    len = recv(sockfd, buf, 1024, 0);
    if (len < 0) {
        close(sockfd);
        freeaddrinfo(servinfo);
        std::cerr << "recv error: " << strerror(errno) << std::endl;
        exit(1);
    }

    std::string res(buf, len);
    // TODO: validate websocket return headers
    // then start doing the work of building a real client.
    std::cout << res << std::endl;

    // Optimize by removing Nagle's Algo and setting IO to non-blocking.
    // Do this _after_ connecting
//    int flag = 1;
//    setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, (char*)&flag, sizeof(flag));
//    fcntl(sockfd, F_SETFL, O_NONBLOCK);

    close(sockfd);
    freeaddrinfo(servinfo);

    std::cout << "Cleaned up and completed..." << std::endl;

    return 0;
}
