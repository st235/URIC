#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"

using ValidationData = std::pair<std::string, bool>;

class UriParserSegmentNzNcTestingFixture: public ::testing::TestWithParam<ValidationData> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserSegmentNzNcTests,
        UriParserSegmentNzNcTestingFixture,
        ::testing::Values(
            std::make_pair("", false),
            std::make_pair("abc?", false),
            std::make_pair("[]", false),
            std::make_pair("a[]", false),
            std::make_pair("a#b", false),
            std::make_pair("0/hello", false),
            std::make_pair("a:b", false),
            std::make_pair("a:b@", false),

            std::make_pair("a", true),
            std::make_pair("abc", true),
            std::make_pair("abc0$asdads91+sdasd", true),
            std::make_pair("a=0", true)
        )
);

TEST_P(UriParserSegmentNzNcTestingFixture, TestThatSegmentNzNcParsingIsCorrect) {
    const auto& pair = GetParam();

    const auto& text = pair.first;
    const auto& expected_result = pair.second;

    uri::__internal::TokenReader reader(text);
    EXPECT_EQ(uri::__internal::segmentNzNc(reader) && !reader.hasNext(), expected_result);
}
