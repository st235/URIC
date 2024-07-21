#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"

using ValidationData = std::pair<std::string, bool>;

class UriParserUserInfoTestingFixture: public ::testing::TestWithParam<ValidationData> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserUserInfoTests,
        UriParserUserInfoTestingFixture,
        ::testing::Values(
            std::make_pair("#asdasd", false),
            std::make_pair("/text", false),
            std::make_pair("?notauserinfo", false),

            std::make_pair("", true),
            std::make_pair("github:st235", true),
            std::make_pair("hell018", true),
            std::make_pair("some_text", true),
            std::make_pair("key=value&user=password", true)
        )
);

TEST_P(UriParserUserInfoTestingFixture, TestThatUserInfoParsingIsCorrect) {
    const auto& pair = GetParam();

    const auto& text = pair.first;
    const auto& expected_result = pair.second;

    uri::__internal::TokenReader reader(text);
    EXPECT_EQ(uri::__internal::userInfo(reader) && !reader.hasNext(), expected_result);
}
