#include <iostream>
#include <string>

#include "url.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Url Validator expects a url as the first argument,"  << std::endl
                  << "See the command below:" << std::endl
                  << "\turl-validator [https://github.com/st235]" << std::endl;
        return 0;
    }

    const auto& url_to_verify = std::string(argv[1]);

    const auto& url_opt = uri::Url::parse(url_to_verify);
    if (!url_opt) {
        std::cout << "Not a valid URL. Please, do read RFC3986 for more information."  << std::endl;
        return 0;
    }

    const auto& url = url_opt.value();

    std::cout << std::endl;

    if (url.getScheme()) {
        std::cout << "Scheme: " << url.getScheme().value() << std::endl;
    }

    if (url.getAuthority()) {
        const auto& authority = url.getAuthority().value();

        std::cout << "Authority:" << std::endl;
        if (authority.getUserInfo()) {
            std::cout << "\tUser Info: " << authority.getUserInfo().value() << std::endl;
        }

        std::cout << "\tHost: " << authority.getHost() << std::endl;

        if (authority.getPort()) {
            std::cout << "\tPort: " << authority.getPort().value() << std::endl;
        }
    }

    std::cout << "Path: " << url.getPath() << std::endl;

    std::cout << "Parsed Queries: " << std::endl;
    for (const auto& [key, value]: url.getQuery()) {
        std::cout << '\t' << key << ": " << value << std::endl;
    }

    if (url.getFragment()) {
        std::cout << "Fragment: " << url.getFragment().value() << std::endl;
    }

    return 0;
}
