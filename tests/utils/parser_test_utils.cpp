#include "parser_test_utils.h"

namespace tests {

std::ostream& operator<<(std::ostream& stream, const ParserTestPayload& data) {
    stream << "{ "
           << "original text = " << data.original_text
           << ", expected status = " << data.expected_status;

    if (data.expected_text) {
        stream << ", expected text = " << data.expected_text.value();
    } else {
        stream << ", expected text = null";
    }

    stream << " }";

    return stream;
}

} // namespace tests
