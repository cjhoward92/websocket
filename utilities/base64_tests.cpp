//
// Created by Carson Howard on 9/11/23.
//
#include <catch2/catch_test_macros.hpp>

#include "base64.h"

TEST_CASE("Test base64", "[base64]") {
    std::string in("testing mytesty");
    std::string expected("dGVzdGluZyBteXRlc3R5");

    auto output = base64_encode(in);

    REQUIRE(output == expected);

    auto decoded_output = base64_decode(output);

    REQUIRE(in == decoded_output);
}