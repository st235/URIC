#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"

using ValidationData = std::pair<std::string, bool>;

class UriParserUriReferenceTestingFixture: public ::testing::TestWithParam<ValidationData> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserUriReferenceTests,
        UriParserUriReferenceTestingFixture,
        ::testing::Values(
            std::make_pair("", true),

            std::make_pair("http://www.example.com/", true),
            std::make_pair("http://bath.example.com/?beginner=brass&art=bone", true),
            std::make_pair("https://www.example.com/", true),
            std::make_pair("https://example.com/#angle", true),
            std::make_pair("http://www.example.com/", true),
            std::make_pair("https://www.example.com/brother", true),
            std::make_pair("http://www.example.com/amusement", true),
            std::make_pair("https://www.example.com/books.php", true),
            std::make_pair("https://www.example.com/", true),
            std::make_pair("https://example.com/action", true),

            std::make_pair("//www.example.com/", true),
            std::make_pair("//bath.example.com/?beginner=brass&art=bone", true),
            std::make_pair("//www.example.com/", true),
            std::make_pair("//example.com/#angle", true),
            std::make_pair("//www.example.com/", true),
            std::make_pair("//www.example.com/brother", true),
            std::make_pair("//www.example.com/amusement", true),
            std::make_pair("//www.example.com/books.php", true),
            std::make_pair("//www.example.com/", true),
            std::make_pair("//example.com/action", true),

            std::make_pair("/", true),
            std::make_pair("/?beginner=brass&art=bone", true),
            std::make_pair("/#angle", true),
            std::make_pair("/brother", true),
            std::make_pair("/amusement", true),
            std::make_pair("/books.php", true),
            std::make_pair("/action", true),

            std::make_pair("?beginner=brass&art=bone", true),
            std::make_pair("brother", true),
            std::make_pair("amusement", true),
            std::make_pair("books.php", true)
        )
);

TEST_P(UriParserUriReferenceTestingFixture, TestThatUriParsingIsCorrect) {
    const auto& pair = GetParam();

    const auto& text = pair.first;
    const auto& expected_result = pair.second;

    uri::__internal::TokenReader reader(text);
    EXPECT_EQ(uri::__internal::uriReference(reader), expected_result);
}
