#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"

using ValidationData = std::pair<std::string, bool>;

class UriParserH16TestingFixture: public ::testing::TestWithParam<ValidationData> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserH16Tests,
        UriParserH16TestingFixture,
        ::testing::Values(
            std::make_pair("", false),
            std::make_pair("01234", false),
            std::make_pair("AAAAA", false),
            std::make_pair("Z", false),

            std::make_pair("1", true),
            std::make_pair("1A", true),
            std::make_pair("1FB", true),
            std::make_pair("9CA2", true),
            std::make_pair("2AF", true)
        )
);

TEST_P(UriParserH16TestingFixture, TestThatH16ParsingIsCorrect) {
    const auto& pair = GetParam();

    const auto& text = pair.first;
    const auto& expected_result = pair.second;

    uri::__internal::TokenReader reader(text);
    EXPECT_EQ(uri::__internal::h16(reader) && !reader.hasNext(), expected_result);
}
