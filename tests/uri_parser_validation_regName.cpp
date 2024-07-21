#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"

using ValidationData = std::pair<std::string, bool>;

class UriParserRegNameTestingFixture: public ::testing::TestWithParam<ValidationData> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserRegNameTests,
        UriParserRegNameTestingFixture,
        ::testing::Values(
            std::make_pair(":", false),
            std::make_pair("@", false),
            std::make_pair("abc:sdas", false),
            std::make_pair("/sdasds", false),
            std::make_pair("/1b", false),
            std::make_pair("?q=5", false),
            std::make_pair("#fragment", false),
            std::make_pair("[ololo]", false),
            std::make_pair("@gmail.com", false),

            std::make_pair("", true),
            std::make_pair("0", true),
            std::make_pair("ab", true),
            std::make_pair("a.sdas", true),
            std::make_pair("~echo", true),
            std::make_pair("1_000_000", true),
            std::make_pair("(Hello%20world)", true),
            std::make_pair("q=5&f=7", true),
            std::make_pair("a01-sdas-bgdf%20", true)
        )
);

TEST_P(UriParserRegNameTestingFixture, TestThatRegNameParsingIsCorrect) {
    const auto& pair = GetParam();

    const auto& text = pair.first;
    const auto& expected_result = pair.second;

    uri::__internal::TokenReader reader(text);
    EXPECT_EQ(uri::__internal::regName(reader) && !reader.hasNext(), expected_result);
}
