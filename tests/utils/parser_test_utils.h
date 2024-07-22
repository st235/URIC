#ifndef __URIC_TEST_UTILS_H__
#define __URIC_TEST_UTILS_H__

#include <optional>
#include <string>
#include <ostream>

namespace tests {

struct ParserTestPayload {
    std::string original_text;

    bool expected_status;
    std::optional<std::string> expected_text;

    static ParserTestPayload error(const std::string& original_text) {
        return { original_text, false, std::nullopt };
    }

    static ParserTestPayload success(const std::string& original_text) {
        return { original_text, true, original_text };
    }
};

std::ostream& operator<<(std::ostream& stream, const ParserTestPayload& data);

} // namespace tests

#endif // __URIC_TEST_UTILS_H__
