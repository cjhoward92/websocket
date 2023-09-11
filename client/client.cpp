//
// Created by Carson Howard on 9/10/23.
//

#include "client.h"

#define MAX_PROTOCOL_LEN 6

std::shared_ptr<w_client> w_client::parse_uri(const std::string &uri) {
    if (uri.length() < MAX_PROTOCOL_LEN) {
        std::ostringstream stream;
        stream << "Unable to parse protocol from ";
        stream << uri;
        throw std::runtime_error(stream.str());
    }

    // Start idx after protocol
    int idx = 5;
    bool is_secure = false;
    if (uri.starts_with("wss://")) {
        is_secure = true;
        idx = 6;
    } else if (!uri.starts_with("ws://")) {
        std::ostringstream stream;
        stream << "Unable to parse protocol from ";
        stream << uri;
        throw std::runtime_error(stream.str());
    }

    int port = is_secure ? 443 : 80;
    int start_port = -1;
    bool parsed_host = false;
    std::string host;
    for (int i = idx; i < uri.size(); i++) {
        auto c = uri[i];
        if (c == ':' || (c == '/' && start_port == -1)) {
            host = uri.substr(idx, i - idx);
            start_port = c == ':' ? i + 1 : -1;
            parsed_host = true;
            continue;
        } else if (c == '/' && start_port > 0) {
            port = std::stoi(uri.substr(start_port, i - idx));
            start_port = -1;
        }
    }

    if (!parsed_host) {
        host = uri.substr(idx, uri.length() - idx);
    }

    if (start_port > 0) {
        port = std::stoi(uri.substr(start_port, uri.length() - start_port));
    }

    std::shared_ptr<w_client> shared(new w_client(host, port, is_secure));
    return shared;
}

bool w_client::get_secure() const {
    return this->_secure;
}

const std::string& w_client::get_host() const {
    return this->_host;
}

uint16_t w_client::get_port() const {
    return this->_port;
}
