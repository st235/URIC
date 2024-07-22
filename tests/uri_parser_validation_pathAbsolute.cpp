#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"

using ValidationData = std::pair<std::string, bool>;

class UriParserPathAbsoluteTestingFixture: public ::testing::TestWithParam<ValidationData> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserPathAbsoluteTests,
        UriParserPathAbsoluteTestingFixture,
        ::testing::Values(
            std::make_pair("", false),
            std::make_pair("0", false),
            std::make_pair("a/sdas", false),
            std::make_pair("//", false),

            std::make_pair("/", true),
            std::make_pair("/a", true),
            std::make_pair("/1b", true),
            std::make_pair("/c2\%20", true),
            std::make_pair("/ab0/aaa/swes", true),
            std::make_pair("/a_b0/a21\%20a/", true)
        )
);

TEST_P(UriParserPathAbsoluteTestingFixture, TestThatPathAbsoluteParsingIsCorrect) {
    const auto& pair = GetParam();

    const auto& text = pair.first;
    const auto& expected_result = pair.second;

    uri::__internal::TokenReader reader(text);
    EXPECT_EQ(uri::__internal::pathAbsolute(reader) && !reader.hasNext(), expected_result);
}
