#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"
#include "utils/parser_test_utils.h"

using tests::ParserTestPayload;

class UriParserPathEmptyTestingFixture: public ::testing::TestWithParam<ParserTestPayload> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserPathEmptyTests,
        UriParserPathEmptyTestingFixture,
        ::testing::Values(
            ParserTestPayload::error("/"),
            ParserTestPayload::error("/a"),
            ParserTestPayload::error("/1b"),
            ParserTestPayload::error("/c2\%20"),
            ParserTestPayload::error("/ab0/aaa/swes"),
            ParserTestPayload::error("/a_b0/a21\%20a/"),
            ParserTestPayload::error(":"),
            ParserTestPayload::error("0"),
            ParserTestPayload::error("ab"),
            ParserTestPayload::error("a/sdas"),
            ParserTestPayload::error("a01/sdas/bgdf%20"),

            ParserTestPayload::success("")
        )
);

TEST_P(UriParserPathEmptyTestingFixture, TestThatPathEmptyParsingIsCorrect) {
    const auto& validation_data = GetParam();

    const auto& original_text = validation_data.original_text;
    const auto& expected_status = validation_data.expected_status;
    const auto& expected_text = validation_data.expected_text;

    std::optional<std::string> parsed_value;
    uri::__internal::TokenReader reader(original_text);

    EXPECT_EQ(uri::__internal::pathEmpty(reader, parsed_value) && !reader.hasNext(), expected_status);

    // Check only fully matched inputs.
    if (!reader.hasNext()) {
        EXPECT_EQ(parsed_value, expected_text);
    }
}
