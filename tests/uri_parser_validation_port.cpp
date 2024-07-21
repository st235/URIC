#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"

using ValidationData = std::pair<std::string, bool>;

class UriParserPortTestingFixture: public ::testing::TestWithParam<ValidationData> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserPortTests,
        UriParserPortTestingFixture,
        ::testing::Values(
            std::make_pair("AAAAA", false),
            std::make_pair("G", false),

            std::make_pair("", true),
            std::make_pair("1", true),
            std::make_pair("18", true),
            std::make_pair("80", true),
            std::make_pair("3036", true),
            std::make_pair("8080", true),
            std::make_pair("21", true),
            std::make_pair("22", true),
            std::make_pair("23", true),
            std::make_pair("143", true),
            std::make_pair("443", true),
            std::make_pair("20", true)
        )
);

TEST_P(UriParserPortTestingFixture, TestThatPortParsingIsCorrect) {
    const auto& pair = GetParam();

    const auto& text = pair.first;
    const auto& expected_result = pair.second;

    uri::__internal::TokenReader reader(text);
    EXPECT_EQ(uri::__internal::port(reader) && !reader.hasNext(), expected_result);
}
