#include <iostream>
#include <string>

#include "uri.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Uri Validator expects a uri as the first argument,"  << std::endl
                  << "See the command below:" << std::endl
                  << "\turi-validator [https://github.com/st235]" << std::endl;
        return 0;
    }

    const auto& uri_to_verify = std::string(argv[1]);

    const auto& uri_opt = uri::Uri::parse(uri_to_verify);
    if (!uri_opt) {
        std::cout << "Not a valid URI. Please, do read RFC3986 for more information."  << std::endl;
        return 0;
    }

    const auto& uri = uri_opt.value();

    std::cout << std::endl;

    if (uri.getScheme()) {
        std::cout << "Scheme: " << uri.getScheme().value() << std::endl;
    }

    if (uri.getAuthority()) {
        const auto& authority = uri.getAuthority().value();

        std::cout << "Authority:" << std::endl;
        if (authority.getUserInfo()) {
            std::cout << "\tUser Info: " << authority.getUserInfo().value() << std::endl;
        }

        std::cout << "\tHost: " << authority.getHost() << std::endl;

        if (authority.getPort()) {
            std::cout << "\tPort: " << authority.getPort().value() << std::endl;
        }
    }

    std::cout << "Path: " << uri.getPath() << std::endl;

    if (uri.getQuery()) {
        std::cout << "Query: " << uri.getQuery().value() << std::endl;
    }

    if (uri.getFragment()) {
        std::cout << "Fragment: " << uri.getFragment().value() << std::endl;
    }

    return 0;
}
