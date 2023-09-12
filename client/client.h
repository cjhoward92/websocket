//
// Created by Carson Howard on 9/10/23.
//

#ifndef WEBSOCKET_CLIENT_H
#define WEBSOCKET_CLIENT_H

#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <utility>

class w_client {
public:
    static std::shared_ptr<w_client> parse_uri(const std::string& uri);
    w_client(w_client&& copy)  noexcept {
        _host = copy._host;
        _port = copy._port;
        _secure = copy._secure;
    }
    ~w_client() = default;

    [[nodiscard]] const std::string& get_uri() const;
    [[nodiscard]] const std::string& get_host() const;
    [[nodiscard]] uint16_t get_port() const;
    [[nodiscard]] bool get_secure() const;

private:
    explicit w_client(std::string uri, std::string host, uint16_t port, bool secure):
        _uri(std::move(uri)),
        _host(std::move(host)),
        _port(port),
        _secure(secure) {};
    std::string _uri;
    std::string _host;
    uint16_t _port {};
    bool _secure {};
};


#endif //WEBSOCKET_CLIENT_H
