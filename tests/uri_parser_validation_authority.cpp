#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"

struct AuthorityTestPayload {
    std::string original_text;

    bool expected_status;
    std::optional<std::string> expected_userInfo;
    std::optional<std::string> expected_host;
    std::optional<std::string> expected_port;

    static AuthorityTestPayload error(const std::string& original_text) {
        return { original_text, false, std::nullopt, std::nullopt, std::nullopt };
    }

    static AuthorityTestPayload success(const std::string& original_text,
                                        std::optional<std::string> expected_userInfo = std::nullopt,
                                        std::optional<std::string> expected_host = std::nullopt,
                                        std::optional<std::string> expected_port = std::nullopt) {
        return { original_text, true, expected_userInfo, expected_host, expected_port };
    }
};

std::ostream& operator<<(std::ostream& stream, const AuthorityTestPayload& data) {
    stream << "{ "
           << "original text = " << data.original_text
           << ", expected status = " << data.expected_status;

    if (data.expected_userInfo) {
        stream << ", expected userInfo = " << data.expected_userInfo.value();
    } else {
        stream << ", expected userInfo = null";
    }

    if (data.expected_host) {
        stream << ", expected host = " << data.expected_host.value();
    } else {
        stream << ", expected host = null";
    }

    if (data.expected_port) {
        stream << ", expected port = " << data.expected_port.value();
    } else {
        stream << ", expected port = null";
    }

    stream << " }";

    return stream;
}

class UriParserAuthorityTestingFixture: public ::testing::TestWithParam<AuthorityTestPayload> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserAuthorityTests,
        UriParserAuthorityTestingFixture,
        ::testing::Values(
            AuthorityTestPayload::error("website.com?q=5"),
            AuthorityTestPayload::error("/website.com"),

            AuthorityTestPayload::success("", std::nullopt, ""),
            AuthorityTestPayload::success(":", std::nullopt, "", ""),
            AuthorityTestPayload::success("@", "", ""),
            AuthorityTestPayload::success("@:", "", "", ""),
            AuthorityTestPayload::success("website.com", std::nullopt, "website.com"),
            AuthorityTestPayload::success("website.net", std::nullopt, "website.net"),
            AuthorityTestPayload::success("somesite.co.uk:3036", std::nullopt, "somesite.co.uk", "3036"),
            AuthorityTestPayload::success("localhost:80", std::nullopt, "localhost", "80"),
            AuthorityTestPayload::success("port.net:", std::nullopt, "port.net", ""),
            AuthorityTestPayload::success("st235@website.com", "st235", "website.com"),
            AuthorityTestPayload::success("text:hello@website.net", "text:hello", "website.net"),
            AuthorityTestPayload::success("somesite.co.uk:3036", std::nullopt, "somesite.co.uk", "3036"),
            AuthorityTestPayload::success("st235@localhost:80", "st235", "localhost", "80"),
            AuthorityTestPayload::success("reallylong=userinfo+.:text@port.net:", "reallylong=userinfo+.:text", "port.net", ""),
            AuthorityTestPayload::success("@website.com:", "", "website.com", ""),
            AuthorityTestPayload::success("@website.com:19321", "", "website.com", "19321"),
            AuthorityTestPayload::success("st235:github.com@website.com:8080", "st235:github.com", "website.com", "8080"),
            AuthorityTestPayload::success("localhost", std::nullopt, "localhost")
        )
);

TEST_P(UriParserAuthorityTestingFixture, TestThatAuthorityParsingIsCorrect) {
    const auto& authority_payload = GetParam();

    const auto& original_text = authority_payload.original_text;

    const auto& expected_status = authority_payload.expected_status;
    const auto& expected_userInfo = authority_payload.expected_userInfo;
    const auto& expected_host = authority_payload.expected_host;
    const auto& expected_port = authority_payload.expected_port;

    std::optional<std::string> parsed_userInfo;
    std::optional<std::string> parsed_host;
    std::optional<std::string> parsed_port;
    uri::__internal::TokenReader reader(original_text);

    EXPECT_EQ(
        uri::__internal::authority(reader, parsed_userInfo, parsed_host, parsed_port) &&
        !reader.hasNext(), expected_status);

    // Check only fully matched inputs.
    if (!reader.hasNext()) {
        EXPECT_EQ(parsed_userInfo, expected_userInfo);
        EXPECT_EQ(parsed_host, expected_host);
        EXPECT_EQ(parsed_port, expected_port);
    }
}
