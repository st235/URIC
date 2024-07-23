#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"

using ValidationData = std::pair<std::string, bool>;

class UriParserPcharTestingFixture: public ::testing::TestWithParam<ValidationData> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserPcharTests,
        UriParserPcharTestingFixture,
        ::testing::Values(
            std::make_pair("", false),
            std::make_pair("aa", false),
            std::make_pair("11", false),
            std::make_pair("()", false),

            std::make_pair("a", true),
            std::make_pair("b", true),
            std::make_pair("c", true),
            std::make_pair("f", true),
            std::make_pair("A", true),
            std::make_pair("B", true),
            std::make_pair("C", true),
            std::make_pair("F", true),
            std::make_pair("0", true),
            std::make_pair("1", true),
            std::make_pair("2", true),
            std::make_pair("3", true),
            std::make_pair("4", true),
            std::make_pair("5", true),
            std::make_pair("6", true),
            std::make_pair("7", true),
            std::make_pair("8", true),
            std::make_pair("9", true),
            std::make_pair("!", true),
            std::make_pair("(", true),
            std::make_pair("&", true),
            std::make_pair(",", true),
            std::make_pair("=", true),
            std::make_pair("\%ab", true),
            std::make_pair("\%0F", true),
            std::make_pair("\%20", true),
            std::make_pair("-", true),
            std::make_pair(".", true),
            std::make_pair("_", true),
            std::make_pair("~", true),
            std::make_pair(":", true),
            std::make_pair("@", true)
        )
);

TEST_P(UriParserPcharTestingFixture, TestThatPcharParsingIsCorrect) {
    const auto& pair = GetParam();

    const auto& text = pair.first;
    const auto& expected_result = pair.second;

    uri::__internal::TokenReader reader(text);
    EXPECT_EQ(uri::__internal::pchar(reader) && !reader.hasNext(), expected_result);
}
