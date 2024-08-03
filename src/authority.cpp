#include "authority.h"

#include "uri_parser.h"
#include "token_reader.h"

namespace uri {

std::optional<Authority> Authority::parse(const std::string& input) {
    __internal::TokenReader reader(input);

    optional_string_t outUserInfo;
    optional_string_t outHost;
    std::optional<__internal::HostType> outHostType;
    optional_string_t outPort;
    authority(reader, outUserInfo, outHost, outHostType, outPort);

    if (reader.hasNext() || !outHost || !outHostType) {
        return std::nullopt;
    }

    bool isHostIPLiteral = outHostType.value() == uri::__internal::HostType::kIPLiteral;
    return Authority(outHost.value(), outPort, outUserInfo, /* isHostIPLiteral= */ isHostIPLiteral);
}

} // namepsace uri
