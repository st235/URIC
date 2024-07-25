#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"
#include "utils/parser_test_utils.h"

using tests::ParserTestPayload;

class UriParserPathAbsoluteTestingFixture: public ::testing::TestWithParam<ParserTestPayload> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserPathAbsoluteTests,
        UriParserPathAbsoluteTestingFixture,
        ::testing::Values(
            ParserTestPayload::error(""),
            ParserTestPayload::error("0"),
            ParserTestPayload::error("a/sdas"),
            ParserTestPayload::error("//"),

            ParserTestPayload::success("/"),
            ParserTestPayload::success("/a"),
            ParserTestPayload::success("/1b"),
            ParserTestPayload::success("/c2%20"),
            ParserTestPayload::success("/ab0/aaa/swes"),
            ParserTestPayload::success("/a_b0/a21%20a/")
        )
);

TEST_P(UriParserPathAbsoluteTestingFixture, TestThatPathAbsoluteParsingIsCorrect) {
    const auto& validation_data = GetParam();

    const auto& original_text = validation_data.original_text;
    const auto& expected_status = validation_data.expected_status;
    const auto& expected_text = validation_data.expected_text;

    std::optional<std::string> parsed_value;
    uri::__internal::TokenReader reader(original_text);

    EXPECT_EQ(uri::__internal::pathAbsolute(reader, parsed_value) && !reader.hasNext(), expected_status);

    // Check only fully matched inputs.
    if (!reader.hasNext()) {
        EXPECT_EQ(parsed_value, expected_text);
    }
}
