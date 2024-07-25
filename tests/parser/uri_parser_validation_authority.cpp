#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"
#include "utils/parser_test_utils.h"

using UriTestPayload = tests::UriTestPayload;

class UriParserAuthorityTestingFixture: public ::testing::TestWithParam<UriTestPayload> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserAuthorityTests,
        UriParserAuthorityTestingFixture,
        ::testing::Values(
            UriTestPayload::error("website.com?q=5"),
            UriTestPayload::error("/website.com"),

            UriTestPayload::success("").expectHost(""),
            UriTestPayload::success(":").expectHost("").expectPort(""),
            UriTestPayload::success("@").expectUserInfo("").expectHost(""),
            UriTestPayload::success("@:").expectUserInfo("").expectHost("").expectPort(""),
            UriTestPayload::success("website.com").expectHost("website.com"),
            UriTestPayload::success("website.net").expectHost("website.net"),
            UriTestPayload::success("somesite.co.uk:3036").expectHost("somesite.co.uk").expectPort("3036"),
            UriTestPayload::success("localhost:80").expectHost("localhost").expectPort("80"),
            UriTestPayload::success("port.net:").expectHost("port.net").expectPort(""),
            UriTestPayload::success("st235@website.com").expectUserInfo("st235").expectHost("website.com"),
            UriTestPayload::success("text:hello@website.net").expectUserInfo("text:hello").expectHost("website.net"),
            UriTestPayload::success("192.168.1.1:3036").expectHost("192.168.1.1").expectPort("3036"),
            UriTestPayload::success("st235@localhost:80").expectUserInfo("st235").expectHost("localhost").expectPort("80"),
            UriTestPayload::success("reallylong=userinfo+.:text@port.net:")
                .expectUserInfo("reallylong=userinfo+.:text")
                .expectHost("port.net")
                .expectPort(""),
            UriTestPayload::success("@website.com:")
                .expectUserInfo("")
                .expectHost("website.com")
                .expectPort(""),
            UriTestPayload::success("@website.com:19321")
                .expectUserInfo("")
                .expectHost("website.com")
                .expectPort("19321"),
            UriTestPayload::success("st235:github.com@website.com:8080")
                .expectUserInfo("st235:github.com")
                .expectHost("website.com")
                .expectPort("8080"),
            UriTestPayload::success("localhost").expectHost("localhost")
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
