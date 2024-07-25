#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"
#include "utils/parser_test_utils.h"

using tests::ParserTestPayload;

class UriParserPathTestingFixture: public ::testing::TestWithParam<ParserTestPayload> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserPathTests,
        UriParserPathTestingFixture,
        ::testing::Values(
            ParserTestPayload::error("?"),
            ParserTestPayload::error("#abc"),

            ParserTestPayload::success(""),
            ParserTestPayload::success("0"),
            ParserTestPayload::success("ab"),
            ParserTestPayload::success("abc"),
            ParserTestPayload::success("/a%20"),
            ParserTestPayload::success("abc/hello"),
            ParserTestPayload::success("0/hello"),
            ParserTestPayload::success("/hello/world"),
            ParserTestPayload::success("/hello/world/"),
            ParserTestPayload::success("/hello1//world/2"),
            ParserTestPayload::success("/1/2/3/4/5/6/7/8"),
            ParserTestPayload::success("/"),
            ParserTestPayload::success("//"),
            ParserTestPayload::success("//a//ab/0/////2"),
            ParserTestPayload::success("//hello/world"),
            ParserTestPayload::success("/hello_world"),
            ParserTestPayload::success("/hello-world"),
            ParserTestPayload::success("/hello=world")
        )
);

TEST_P(UriParserPathTestingFixture, TestThatPathParsingIsCorrect) {
    const auto& validation_data = GetParam();

    const auto& original_text = validation_data.original_text;
    const auto& expected_status = validation_data.expected_status;
    const auto& expected_text = validation_data.expected_text;

    std::optional<std::string> parsed_value;
    uri::__internal::TokenReader reader(original_text);

    EXPECT_EQ(uri::__internal::path(reader, parsed_value), expected_status);
    EXPECT_EQ(parsed_value, expected_text);
}
