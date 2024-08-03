#ifndef __URIC_TEST_UTILS_H__
#define __URIC_TEST_UTILS_H__

#include <optional>
#include <string>
#include <ostream>

#include "uri_parser.h"

namespace tests {

struct ParserTestPayload {
    std::string original_text;

    bool expected_status;
    std::optional<std::string> expected_text;

    static ParserTestPayload error(const std::string& original_text) {
        return { original_text, false, std::nullopt };
    }

    static ParserTestPayload success(const std::string& original_text) {
        return { original_text, true, /* expected_text= */ original_text };
    }

    static ParserTestPayload success(const std::string& original_text,
                                     const std::string& expected_text) {
        return { original_text, true, expected_text };
    }
};

std::ostream& operator<<(std::ostream& stream, const ParserTestPayload& data);

struct UriTestPayload {
    std::string original_text;

    bool expected_status;
    std::optional<std::string> expected_scheme;
    std::optional<std::string> expected_userInfo;
    std::optional<std::string> expected_host;
    std::optional<uri::__internal::HostType> expected_host_type;
    std::optional<std::string> expected_port;
    std::optional<std::string> expected_path;
    std::optional<std::string> expected_query;
    std::optional<std::string> expected_fragment;

    UriTestPayload(const std::string& original_text,
                   bool expected_status):
        original_text(original_text),
        expected_status(expected_status),
        expected_scheme(std::nullopt),
        expected_userInfo(std::nullopt),
        expected_host(std::nullopt),
        expected_host_type(std::nullopt),
        expected_port(std::nullopt),
        expected_path(std::nullopt),
        expected_query(std::nullopt),
        expected_fragment(std::nullopt) {
        // Empty on purpose.
    }

    UriTestPayload(const UriTestPayload& that) = default;
    UriTestPayload& operator=(const UriTestPayload& that) = default;
    UriTestPayload(UriTestPayload&& that) = default;
    UriTestPayload& operator=(UriTestPayload&& that) = default;

    static UriTestPayload error(const std::string& original_text) {
        return UriTestPayload(original_text, /* expected_status= */ false);
    }

    static UriTestPayload success(const std::string& original_text) {
        return UriTestPayload(original_text, /* expected_status= */ true);
    }

    UriTestPayload& expectScheme(const std::string& scheme) {
        expected_scheme = scheme;
        return *this;
    }

    UriTestPayload& expectUserInfo(const std::string& userInfo) {
        expected_userInfo = userInfo;
        return *this;
    }

    UriTestPayload& expectHost(const std::string& host,
                               const uri::__internal::HostType& host_type = uri::__internal::HostType::kRegName) {
        expected_host = host;
        expected_host_type = std::make_optional(host_type);
        return *this;
    }

    UriTestPayload& expectPort(const std::string& port) {
        expected_port = port;
        return *this;
    }

    UriTestPayload& expectPath(const std::string& path) {
        expected_path = path;
        return *this;
    }

    UriTestPayload& expectQuery(const std::string& query) {
        expected_query = query;
        return *this;
    }

    UriTestPayload& expectFragment(const std::string& fragment) {
        expected_fragment = fragment;
        return *this;
    }
};

std::ostream& operator<<(std::ostream& stream, const UriTestPayload& data);

} // namespace tests

#endif // __URIC_TEST_UTILS_H__
