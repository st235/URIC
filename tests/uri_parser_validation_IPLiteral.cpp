#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"

using ValidationData = std::pair<std::string, bool>;

class UriParserIPLiteralTestingFixture: public ::testing::TestWithParam<ValidationData> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserIPLiteralTests,
        UriParserIPLiteralTestingFixture,
        ::testing::Values(
            std::make_pair("", false),
            std::make_pair("a", false),
            std::make_pair("v.", false),
            std::make_pair("v1.", false),
            std::make_pair("v.12345", false),
            std::make_pair("v4.11:25:]", false),
            std::make_pair("1fd2:23b4:4c96:1bed:4c89:3f5c:98ed:0494]", false),
            std::make_pair("efab:ffac:bd1a:1a71:8fcd::1a8f]", false),
            std::make_pair("[v4.11:25:", false),
            std::make_pair("[1fd2:23b4:4c96:1bed:4c89:3f5c:98ed:0494", false),
            std::make_pair("[efab:ffac:bd1a:1a71:8fcd::1a8f", false),

            std::make_pair("[v4.11]", true),
            std::make_pair("[v4.11:25]", true),
            std::make_pair("[v4.11:25:]", true),
            std::make_pair("[1fd2:23b4:4c96:1bed:4c89:3f5c:98ed:0494]", true),
            std::make_pair("[efab:ffac:bd1a:1a71:8fcd::1a8f]", true),
            std::make_pair("[v77.abz:25:]", true)
        )
);

TEST_P(UriParserIPLiteralTestingFixture, TestThatIPLiteralParsingIsCorrect) {
    const auto& pair = GetParam();

    const auto& text = pair.first;
    const auto& expected_result = pair.second;

    uri::__internal::TokenReader reader(text);
    EXPECT_EQ(uri::__internal::IPLiteral(reader) && !reader.hasNext(), expected_result);
}
