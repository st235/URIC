#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"

using ValidationData = std::pair<std::string, bool>;

class UriParserPctEncodedTestingFixture: public ::testing::TestWithParam<ValidationData> {};

// pct-encoded = "%" HEXDIG HEXDIG
INSTANTIATE_TEST_SUITE_P(
        UriParserPctEncodedTests,
        UriParserPctEncodedTestingFixture,
        ::testing::Values(
            std::make_pair("", false),
            std::make_pair("11", false),
            std::make_pair("AB", false),
            std::make_pair("%", false),
            std::make_pair("%A", false),
            std::make_pair("%AV", false),
            std::make_pair("%ZA", false),
            std::make_pair("%ABC", false),

            std::make_pair("%ab", true),
            std::make_pair("%0F", true),
            std::make_pair("%20", true),
            std::make_pair("%01", true),
            std::make_pair("%99", true),
            std::make_pair("%1B", true),
            std::make_pair("%C2", true),
            std::make_pair("%F5", true),
            std::make_pair("%AA", true),
            std::make_pair("%FF", true)
        )
);

TEST_P(UriParserPctEncodedTestingFixture, TestThatPctEncodedParsingIsCorrect) {
    const auto& pair = GetParam();

    const auto& text = pair.first;
    const auto& expected_result = pair.second;

    uri::__internal::TokenReader reader(text);
    EXPECT_EQ(uri::__internal::pctEncoded(reader) && !reader.hasNext(), expected_result);
}
