#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"

using ValidationData = std::pair<std::string, bool>;

class UriParserPathTestingFixture: public ::testing::TestWithParam<ValidationData> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserPathTests,
        UriParserPathTestingFixture,
        ::testing::Values(
            std::make_pair("?", false),
            std::make_pair("#abc", false),

            std::make_pair("", true),
            std::make_pair("0", true),
            std::make_pair("ab", true),
            std::make_pair("abc", true),
            std::make_pair("/a\%20", true),
            std::make_pair("abc/hello", true),
            std::make_pair("0/hello", true),
            std::make_pair("/hello/world", true),
            std::make_pair("/hello/world/", true),
            std::make_pair("/hello1//world/2", true),
            std::make_pair("/1/2/3/4/5/6/7/8", true),
            std::make_pair("/", true),
            std::make_pair("//", true),
            std::make_pair("//a//ab/0/////2", true),
            std::make_pair("//hello/world", true),
            std::make_pair("/hello_world", true),
            std::make_pair("/hello-world", true),
            std::make_pair("/hello=world", true)
        )
);

TEST_P(UriParserPathTestingFixture, TestThatPathParsingIsCorrect) {
    const auto& pair = GetParam();

    const auto& text = pair.first;
    const auto& expected_result = pair.second;

    uri::__internal::TokenReader reader(text);
    EXPECT_EQ(uri::__internal::path(reader), expected_result);
}
