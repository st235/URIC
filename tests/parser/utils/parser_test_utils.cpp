#include "parser_test_utils.h"

namespace tests {

std::ostream& operator<<(std::ostream& stream, const ParserTestPayload& data) {
    stream << "{ "
           << "original text = " << data.original_text
           << ", expected status = " << data.expected_status;

    if (data.expected_text) {
        stream << ", expected text = " << data.expected_text.value();
    }

    stream << " }";

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const UriTestPayload& data) {
    stream << "{ "
           << "original text = " << data.original_text
           << ", expected status = " << data.expected_status;

    if (data.expected_scheme) {
        stream << ", expected scheme = " << data.expected_scheme.value();
    }

    if (data.expected_userInfo) {
        stream << ", expected userInfo = " << data.expected_userInfo.value();
    }

    if (data.expected_host) {
        stream << ", expected host = " << data.expected_host.value() << " with type: " << static_cast<int>(data.expected_host_type.value());
    }

    if (data.expected_port) {
        stream << ", expected port = " << data.expected_port.value();
    }

    if (data.expected_path) {
        stream << ", expected path = " << data.expected_path.value();
    }

    if (data.expected_query) {
        stream << ", expected query = " << data.expected_query.value();
    }

    if (data.expected_fragment) {
        stream << ", expected fragment = " << data.expected_fragment.value();
    }

    stream << " }";

    return stream;
}

} // namespace tests
