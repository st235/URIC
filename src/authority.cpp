#include "authority.h"

#include "uri_parser.h"
#include "token_reader.h"

namespace uri {

std::optional<Authority> Authority::parse(const std::string& input) {
    __internal::TokenReader reader(input);

    optional_string_t outUserInfo;
    optional_string_t outHost;
    optional_string_t outPort;
    authority(reader, outUserInfo, outHost, outPort);

    if (reader.hasNext() || !outHost) {
        return std::nullopt;
    }

    return Authority(outUserInfo, outHost.value(), outPort);
}

} // namepsace uri
