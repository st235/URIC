#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"

using ValidationData = std::pair<std::string, bool>;

class UriParserQueryFragmentTestingFixture: public ::testing::TestWithParam<ValidationData> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserQueryFragmentTests,
        UriParserQueryFragmentTestingFixture,
        ::testing::Values(
            std::make_pair("[]", false),
            std::make_pair("a[]", false),
            std::make_pair("a#b", false),

            std::make_pair("", true),
            std::make_pair("a", true),
            std::make_pair("a01/", true),
            std::make_pair("a01/b:as", true),
            std::make_pair("0(hello)", true),
            std::make_pair("abc0$asdads91+sdasd?", true),
            std::make_pair("a=0@@@asw:", true)
        )
);

TEST_P(UriParserQueryFragmentTestingFixture, TestThatQueryFragmentParsingIsCorrect) {
    const auto& pair = GetParam();

    const auto& text = pair.first;
    const auto& expected_result = pair.second;

    uri::__internal::TokenReader reader(text);
    EXPECT_EQ(uri::__internal::queryFragment(reader) && !reader.hasNext(), expected_result);
}
