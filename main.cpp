#include <iostream>
#include <string>
#include <sstream>

#include "client/client.h"

int main() {
    std::ostringstream str;
    str << "ws://somethihg.com:8080";

    // w_client c(str.str());
    std::cout << "Hello" << std::endl;

    return 0;
}
