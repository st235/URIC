#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"
#include "utils/parser_test_utils.h"

using tests::ParserTestPayload;

class UriParserPathNoschemeTestingFixture: public ::testing::TestWithParam<ParserTestPayload> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserPathNoschemeTests,
        UriParserPathNoschemeTestingFixture,
        ::testing::Values(
            ParserTestPayload::error(""),
            ParserTestPayload::error(":"),
            ParserTestPayload::error("/"),
            ParserTestPayload::error("/a"),
            ParserTestPayload::error("/1b"),
            ParserTestPayload::error("/c2%20"),
            ParserTestPayload::error("/ab0/aaa/swes"),
            ParserTestPayload::error("/a_b0/a21%20a/"),
            ParserTestPayload::error("//"),

            ParserTestPayload::success("0"),
            ParserTestPayload::success("ab"),
            ParserTestPayload::success("a/sdas"),
            ParserTestPayload::success("a01/sdas/bgdf%20")
        )
);

TEST_P(UriParserPathNoschemeTestingFixture, TestThatPathNoschemeParsingIsCorrect) {
    const auto& validation_data = GetParam();

    const auto& original_text = validation_data.original_text;
    const auto& expected_status = validation_data.expected_status;
    const auto& expected_text = validation_data.expected_text;

    std::optional<std::string> parsed_value;
    uri::__internal::TokenReader reader(original_text);

    EXPECT_EQ(uri::__internal::pathNoscheme(reader, parsed_value) && !reader.hasNext(), expected_status);

    // Check only fully matched inputs.
    if (!reader.hasNext()) {
        EXPECT_EQ(parsed_value, expected_text);
    }
}
