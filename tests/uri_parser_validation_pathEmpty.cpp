#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"

using ValidationData = std::pair<std::string, bool>;

class UriParserPathEmptyTestingFixture: public ::testing::TestWithParam<ValidationData> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserPathEmptyTests,
        UriParserPathEmptyTestingFixture,
        ::testing::Values(
            std::make_pair("/", false),
            std::make_pair("/a", false),
            std::make_pair("/1b", false),
            std::make_pair("/c2\%20", false),
            std::make_pair("/ab0/aaa/swes", false),
            std::make_pair("/a_b0/a21\%20a/", false),
            std::make_pair(":", false),
            std::make_pair("0", false),
            std::make_pair("ab", false),
            std::make_pair("a/sdas", false),
            std::make_pair("a01/sdas/bgdf%20", false),

            std::make_pair("", true)
        )
);

TEST_P(UriParserPathEmptyTestingFixture, TestThatPathEmptyParsingIsCorrect) {
    const auto& pair = GetParam();

    const auto& text = pair.first;
    const auto& expected_result = pair.second;

    uri::__internal::TokenReader reader(text);
    EXPECT_EQ(uri::__internal::pathEmpty(reader) && !reader.hasNext(), expected_result);
}
