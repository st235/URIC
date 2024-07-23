#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"
#include "utils/parser_test_utils.h"

using UriTestPayload = tests::UriTestPayload;

class UriParserRelativeRefTestingFixture: public ::testing::TestWithParam<UriTestPayload> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserRelativeRefTests,
        UriParserRelativeRefTestingFixture,
        ::testing::Values(
            // Should be parsed as path-rootless.
            UriTestPayload::error("://localhost:8080"),
            // No column symbols in relative-ref.
            UriTestPayload::error("site.co.uk:3036"),
            UriTestPayload::error("site.co.uk:3036/"),
            UriTestPayload::error("github:st235@website.com/some_path"),

            UriTestPayload::success("")
                .expectPath(""),
            UriTestPayload::success("//")
                .expectHost("")
                .expectPath(""),
            UriTestPayload::success("//localhost:8080")
                .expectHost("localhost")
                .expectPort("8080")
                .expectPath(""),
            UriTestPayload::success("//localhost:8080/")
                .expectHost("localhost")
                .expectPort("8080")
                .expectPath("/"),
            UriTestPayload::success("//localhost:8080?q=5")
                .expectHost("localhost")
                .expectPort("8080")
                .expectPath("")
                .expectQuery("q=5"),
            UriTestPayload::success("//localhost:8080/?q=text")
                .expectHost("localhost")
                .expectPort("8080")
                .expectPath("/")
                .expectQuery("q=text"),
            UriTestPayload::success("//localhost:8080/?q=text#anchor1")
                .expectHost("localhost")
                .expectPort("8080")
                .expectPath("/")
                .expectQuery("q=text")
                .expectFragment("anchor1"),
            UriTestPayload::success("//github:st235@website.com/some_path")
                .expectUserInfo("github:st235")
                .expectHost("website.com")
                .expectPath("/some_path"),
            UriTestPayload::success("//github:st235@website.com/some_path#anchor1")
                .expectUserInfo("github:st235")
                .expectHost("website.com")
                .expectPath("/some_path")
                .expectFragment("anchor1"),
            // '?' goes into fragment as fragment accepts it.
            UriTestPayload::success("//localhost:8080/#thisisabigfragment?q=text")
                .expectHost("localhost")
                .expectPort("8080")
                .expectPath("/")
                .expectFragment("thisisabigfragment?q=text"),
            UriTestPayload::success("/")
                .expectPath("/"),
            UriTestPayload::success("/site.co.uk:3036")
                .expectPath("/site.co.uk:3036"),
            UriTestPayload::success("/site.co.uk:3036/")
                .expectPath("/site.co.uk:3036/"),
            UriTestPayload::success("/github:st235@website.com/some_path")
                .expectPath("/github:st235@website.com/some_path"),
            UriTestPayload::success("st235.me/about/early-career")
                .expectPath("st235.me/about/early-career")
        )
);

TEST_P(UriParserRelativeRefTestingFixture, TestThatRelativeRefParsingIsCorrect) {
    const auto& authority_payload = GetParam();

    const auto& original_text = authority_payload.original_text;

    const auto& expected_status = authority_payload.expected_status;
    const auto& expected_userInfo = authority_payload.expected_userInfo;
    const auto& expected_host = authority_payload.expected_host;
    const auto& expected_port = authority_payload.expected_port;
    const auto& expected_path = authority_payload.expected_path;
    const auto& expected_query = authority_payload.expected_query;
    const auto& expected_fragment = authority_payload.expected_fragment;

    std::optional<std::string> parsed_userInfo;
    std::optional<std::string> parsed_host;
    std::optional<std::string> parsed_port;
    std::optional<std::string> parsed_path;
    std::optional<std::string> parsed_query;
    std::optional<std::string> parsed_fragment;
    uri::__internal::TokenReader reader(original_text);

    EXPECT_EQ(
        uri::__internal::relativeRef(reader,
            parsed_userInfo, parsed_host, parsed_port, parsed_path,
            parsed_query, parsed_fragment) &&
        !reader.hasNext(), expected_status);

    // Check only fully matched inputs.
    if (!reader.hasNext()) {
        EXPECT_EQ(parsed_userInfo, expected_userInfo);
        EXPECT_EQ(parsed_host, expected_host);
        EXPECT_EQ(parsed_port, expected_port);
        EXPECT_EQ(parsed_path, expected_path);
        EXPECT_EQ(parsed_query, expected_query);
        EXPECT_EQ(parsed_fragment, expected_fragment);
    }
}
