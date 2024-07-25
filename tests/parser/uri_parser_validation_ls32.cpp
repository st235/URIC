#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"

using ValidationData = std::pair<std::string, bool>;

class UriParserLS32TestingFixture: public ::testing::TestWithParam<ValidationData> {};

// ls32 = ( h16 ":" h16 ) / IPv4address
INSTANTIATE_TEST_SUITE_P(
        UriParserLS32Tests,
        UriParserLS32TestingFixture,
        ::testing::Values(
            std::make_pair("", false),
            std::make_pair("abcsd", false),
            std::make_pair("1FAB:", false),

            std::make_pair("1FAB:AB", true),
            std::make_pair("1:2CB", true),

            std::make_pair("202.72.23.99", true),
            std::make_pair("243.148.80.244", true),
            std::make_pair("108.227.156.228", true),
            std::make_pair("120.122.235.124", true),
            std::make_pair("235.97.113.89", true),
            std::make_pair("212.15.116.17", true),
            std::make_pair("135.141.48.203", true),
            std::make_pair("140.119.208.94", true),
            std::make_pair("162.174.113.136", true),
            std::make_pair("77.189.162.135", true),
            std::make_pair("213.18.130.146", true),
            std::make_pair("111.63.98.70", true),
            std::make_pair("204.21.183.48", true),
            std::make_pair("70.164.197.157", true),
            std::make_pair("133.234.180.108", true),
            std::make_pair("219.141.245.164", true),
            std::make_pair("145.196.248.224", true),
            std::make_pair("71.206.135.201", true),
            std::make_pair("165.114.76.104", true),
            std::make_pair("243.225.52.242", true)
        )
);

TEST_P(UriParserLS32TestingFixture, TestThatLS32ParsingIsCorrect) {
    const auto& pair = GetParam();

    const auto& text = pair.first;
    const auto& expected_result = pair.second;

    uri::__internal::TokenReader reader(text);
    EXPECT_EQ(uri::__internal::ls32(reader) && !reader.hasNext(), expected_result);
}
