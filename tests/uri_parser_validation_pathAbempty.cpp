#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"
#include "utils/parser_test_utils.h"

using tests::ParserTestPayload;

class UriParserPathAbemptyTestingFixture: public ::testing::TestWithParam<ParserTestPayload> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserPathAbemptyTests,
        UriParserPathAbemptyTestingFixture,
        ::testing::Values(
            ParserTestPayload::error("abc"),
            ParserTestPayload::error("?"),
            ParserTestPayload::error("#abc"),
            ParserTestPayload::error("abc/hello"),
            ParserTestPayload::error("0/hello"),

            ParserTestPayload::success(""),
            ParserTestPayload::success("/hello/world"),
            ParserTestPayload::success("/hello/world/"),
            ParserTestPayload::success("/hello1//world/2"),
            ParserTestPayload::success("/1/2/3/4/5/6/7/8"),
            ParserTestPayload::success("/"),
            ParserTestPayload::success("//"),
            ParserTestPayload::success("//hello/world"),
            ParserTestPayload::success("/hello_world"),
            ParserTestPayload::success("/hello-world"),
            ParserTestPayload::success("/hello=world")
        )
);

TEST_P(UriParserPathAbemptyTestingFixture, TestThatPathAbemptyParsingIsCorrect) {
    const auto& validation_data = GetParam();

    const auto& original_text = validation_data.original_text;
    const auto& expected_status = validation_data.expected_status;
    const auto& expected_text = validation_data.expected_text;

    std::optional<std::string> parsed_value;
    uri::__internal::TokenReader reader(original_text);

    EXPECT_EQ(uri::__internal::pathAbempty(reader, parsed_value) && !reader.hasNext(), expected_status);

    // Check only fully matched inputs.
    if (!reader.hasNext()) {
        EXPECT_EQ(parsed_value, expected_text);
    }
}
