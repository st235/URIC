#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"

using ValidationData = std::pair<std::string, bool>;

class UriParserRelativePartTestingFixture: public ::testing::TestWithParam<ValidationData> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserRelativePartTests,
        UriParserRelativePartTestingFixture,
        ::testing::Values(
            // No column.
            std::make_pair("site.co.uk:3036", false),
            std::make_pair("site.co.uk:3036/", false),
            std::make_pair("github:st235@website.com/some_path", false),

            std::make_pair("", true),
            std::make_pair("//", true),
            std::make_pair("//localhost:8080", true),
            std::make_pair("//localhost:8080/", true),
            std::make_pair("//github:st235@website.com/some_path", true),
            std::make_pair("/", true),
            std::make_pair("/site.co.uk:3036", true),
            std::make_pair("/site.co.uk:3036/", true),
            std::make_pair("/github:st235@website.com/some_path", true),
            std::make_pair("st235.me/about/early-career", true)
        )
);

TEST_P(UriParserRelativePartTestingFixture, TestThatRelativePartParsingIsCorrect) {
    const auto& pair = GetParam();

    const auto& text = pair.first;
    const auto& expected_result = pair.second;

    uri::__internal::TokenReader reader(text);
    EXPECT_EQ(uri::__internal::relativePart(reader) && !reader.hasNext(), expected_result);
}
