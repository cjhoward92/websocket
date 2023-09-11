//
// Created by Carson Howard on 9/10/23.
//
#include <catch2/catch_test_macros.hpp>

#include "client.h"

TEST_CASE("Test parsing ws://test.websockets.com:8080", "[client]") {
    std::string uri("ws://test.websockets.com:8080");
    auto c = w_client::parse_uri(uri);
    REQUIRE(c->get_port() == 8080);
    REQUIRE_FALSE(c->get_secure());
    REQUIRE(c->get_host() == "test.websockets.com");
}

TEST_CASE("Test parsing wss://test.websockets.com", "[client]") {
    std::string uri("wss://test.websockets.com");
    auto c = w_client::parse_uri(uri);
    REQUIRE(c->get_port() == 443);
    REQUIRE(c->get_secure());
    REQUIRE(c->get_host() == "test.websockets.com");
}

TEST_CASE("Test parsing wss://test.websockets.com/", "[client]") {
    std::string uri("wss://test.websockets.com/");
    auto c = w_client::parse_uri(uri);
    REQUIRE(c->get_port() == 443);
    REQUIRE(c->get_secure());
    REQUIRE(c->get_host() == "test.websockets.com");
}

TEST_CASE("Test failure", "[client]") {
    std::string uri("invalid_uri");
    REQUIRE_THROWS([&]{
        w_client::parse_uri(uri);
    }());
}