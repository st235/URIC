#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"

using ValidationData = std::pair<std::string, bool>;

class UriParserIPvFutureTestingFixture: public ::testing::TestWithParam<ValidationData> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserIPvFutureTests,
        UriParserIPvFutureTestingFixture,
        ::testing::Values(
            std::make_pair("", false),
            std::make_pair("a", false),
            std::make_pair("v.", false),
            std::make_pair("v1.", false),
            std::make_pair("v.12345", false),

            std::make_pair("v4.11", true),
            std::make_pair("v4.11:25", true),
            std::make_pair("v4.11:25:", true),
            std::make_pair("v77.abz:25:", true)
        )
);

TEST_P(UriParserIPvFutureTestingFixture, TestThatIPvFutureParsingIsCorrect) {
    const auto& pair = GetParam();

    const auto& text = pair.first;
    const auto& expected_result = pair.second;

    uri::__internal::TokenReader reader(text);
    EXPECT_EQ(uri::__internal::IPvFuture(reader) && !reader.hasNext(), expected_result);
}
