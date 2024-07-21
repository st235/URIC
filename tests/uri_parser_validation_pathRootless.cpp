#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"

using ValidationData = std::pair<std::string, bool>;

class UriParserPathRootlessTestingFixture: public ::testing::TestWithParam<ValidationData> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserPathRootlessTests,
        UriParserPathRootlessTestingFixture,
        ::testing::Values(
            std::make_pair("", false),
            std::make_pair("/", false),
            std::make_pair("/a", false),
            std::make_pair("/1b", false),
            std::make_pair("/c2\%20", false),
            std::make_pair("/ab0/aaa/swes", false),
            std::make_pair("/a_b0/a21\%20a/", false),
            std::make_pair("//", false),

            std::make_pair(":", true),
            std::make_pair("0", true),
            std::make_pair("ab", true),
            std::make_pair("a/sdas", true),
            std::make_pair("a01/sdas/bgdf%20", true)
        )
);

TEST_P(UriParserPathRootlessTestingFixture, TestThatPathRootlessParsingIsCorrect) {
    const auto& pair = GetParam();

    const auto& text = pair.first;
    const auto& expected_result = pair.second;

    uri::__internal::TokenReader reader(text);
    EXPECT_EQ(uri::__internal::pathRootless(reader) && !reader.hasNext(), expected_result);
}
