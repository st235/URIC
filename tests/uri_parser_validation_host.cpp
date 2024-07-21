#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"

using ValidationData = std::pair<std::string, bool>;

class UriParserHostTestingFixture: public ::testing::TestWithParam<ValidationData> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserHostTests,
        UriParserHostTestingFixture,
        ::testing::Values(
            std::make_pair("v4.11:25:]", false),
            std::make_pair("1fd2:23b4:4c96:1bed:4c89:3f5c:98ed:0494]", false),
            std::make_pair("efab:ffac:bd1a:1a71:8fcd::1a8f]", false),
            std::make_pair("[v4.11:25:", false),
            std::make_pair("[1fd2:23b4:4c96:1bed:4c89:3f5c:98ed:0494", false),
            std::make_pair("[efab:ffac:bd1a:1a71:8fcd::1a8f", false),

            // IP-literal
            std::make_pair("[v4.11]", true),
            std::make_pair("[v4.11:25]", true),
            std::make_pair("[v4.11:25:]", true),
            std::make_pair("[1fd2:23b4:4c96:1bed:4c89:3f5c:98ed:0494]", true),
            std::make_pair("[efab:ffac:bd1a:1a71:8fcd::1a8f]", true),
            std::make_pair("[v77.abz:25:]", true),

            // IPv4address
            std::make_pair("82.239.179.164", true),
            std::make_pair("23.6.209.89", true),
            std::make_pair("86.143.252.23", true),
            std::make_pair("124.1.165.76", true),
            std::make_pair("91.24.186.22", true),
            std::make_pair("88.36.159.30", true),
            std::make_pair("24.25.81.113", true),
            std::make_pair("7.75.209.57", true),
            std::make_pair("11.6.36.223", true),
            std::make_pair("233.155.227.64", true),

            // reg-name
            std::make_pair("", true),
            std::make_pair("a", true),
            std::make_pair("v.", true),
            std::make_pair("v1.", true),
            std::make_pair("v.12345", true),
            std::make_pair("localhost", true)
        )
);

TEST_P(UriParserHostTestingFixture, TestThatHostParsingIsCorrect) {
    const auto& pair = GetParam();

    const auto& text = pair.first;
    const auto& expected_result = pair.second;

    uri::__internal::TokenReader reader(text);
    EXPECT_EQ(uri::__internal::host(reader) && !reader.hasNext(), expected_result);
}
