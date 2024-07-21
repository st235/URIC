#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"

using ValidationData = std::pair<std::string, bool>;

class UriParserAuthorityTestingFixture: public ::testing::TestWithParam<ValidationData> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserAuthorityTests,
        UriParserAuthorityTestingFixture,
        ::testing::Values(
            std::make_pair("website.com?q=5", false),
            std::make_pair("/website.com", false),

            std::make_pair("", true),
            std::make_pair(":", true),
            std::make_pair("@", true),
            std::make_pair("@:", true),
            std::make_pair("website.com", true),
            std::make_pair("website.net", true),
            std::make_pair("somesite.co.uk:3036", true),
            std::make_pair("localhost:80", true),
            std::make_pair("port.net:", true),
            std::make_pair("website.com", true),
            std::make_pair("website.net", true),
            std::make_pair("somesite.co.uk:3036", true),
            std::make_pair("localhost:80", true),
            std::make_pair("port.net:", true),
            std::make_pair("@website.com:", true),
            std::make_pair("@website.com:19321", true),
            std::make_pair("st235:github.com@website.com:8080", true),
            std::make_pair("localhost", true)
        )
);

TEST_P(UriParserAuthorityTestingFixture, TestThatAuthorityParsingIsCorrect) {
    const auto& pair = GetParam();

    const auto& text = pair.first;
    const auto& expected_result = pair.second;

    uri::__internal::TokenReader reader(text);
    EXPECT_EQ(uri::__internal::authority(reader) && !reader.hasNext(), expected_result);
}
