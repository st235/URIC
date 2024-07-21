#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"

using ValidationData = std::pair<std::string, bool>;

class UriParserSchemeTestingFixture: public ::testing::TestWithParam<ValidationData> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserSchemeTests,
        UriParserSchemeTestingFixture,
        ::testing::Values(
            std::make_pair("", false),

            std::make_pair("http", true),
            std::make_pair("https", true),
            std::make_pair("ws", true),
            std::make_pair("ssh", true),
            std::make_pair("mailto", true),
            std::make_pair("ftp", true),
            std::make_pair("a+b", true),
            std::make_pair("a.b", true)
        )
);

TEST_P(UriParserSchemeTestingFixture, TestThatSchemeParsingIsCorrect) {
    const auto& pair = GetParam();

    const auto& text = pair.first;
    const auto& expected_result = pair.second;

    uri::__internal::TokenReader reader(text);
    EXPECT_EQ(uri::__internal::scheme(reader) && !reader.hasNext(), expected_result);
}
