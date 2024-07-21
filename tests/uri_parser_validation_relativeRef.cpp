#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"

using ValidationData = std::pair<std::string, bool>;

class UriParserRelativeRefTestingFixture: public ::testing::TestWithParam<ValidationData> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserRelativeRefTests,
        UriParserRelativeRefTestingFixture,
        ::testing::Values(
            std::make_pair("", true),
            std::make_pair("//", true),
            std::make_pair("//localhost:8080", true),
            std::make_pair("//localhost:8080/", true),
            std::make_pair("//localhost:8080?q=5", true),
            std::make_pair("//localhost:8080/?q=text", true),
            std::make_pair("//localhost:8080/?q=text#anchor1", true),
            std::make_pair("//github:st235@website.com/some_path", true),
            std::make_pair("//github:st235@website.com/some_path#anchor1", true),
            // '?' goes into fragment as fragment accepts it.
            std::make_pair("//localhost:8080/#thisisabigfragment?q=text", true),
            std::make_pair("/", true),
            std::make_pair("/site.co.uk:3036", true),
            std::make_pair("/site.co.uk:3036/", true),
            std::make_pair("/github:st235@website.com/some_path", true),
            std::make_pair("site.co.uk:3036", true),
            std::make_pair("site.co.uk:3036/", true),
            std::make_pair("github:st235@website.com/some_path", true),
            // Should be parsed as path-rootless.
            std::make_pair("://localhost:8080", true),
            std::make_pair("st235.me/about/early-career", true)
        )
);

TEST_P(UriParserRelativeRefTestingFixture, TestThatRelativeRefParsingIsCorrect) {
    const auto& pair = GetParam();

    const auto& text = pair.first;
    const auto& expected_result = pair.second;

    uri::__internal::TokenReader reader(text);
    EXPECT_EQ(uri::__internal::relativeRef(reader) && !reader.hasNext(), expected_result);
}
