#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"
#include "utils/parser_test_utils.h"

using tests::ParserTestPayload;

class UriParserIPLiteralTestingFixture: public ::testing::TestWithParam<ParserTestPayload> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserIPLiteralTests,
        UriParserIPLiteralTestingFixture,
        ::testing::Values(
            ParserTestPayload::error(""),
            ParserTestPayload::error("a"),
            ParserTestPayload::error("v."),
            ParserTestPayload::error("v1."),
            ParserTestPayload::error("v.12345"),
            ParserTestPayload::error("v4.11:25:]"),
            ParserTestPayload::error("1fd2:23b4:4c96:1bed:4c89:3f5c:98ed:0494]"),
            ParserTestPayload::error("efab:ffac:bd1a:1a71:8fcd::1a8f]"),
            ParserTestPayload::error("[v4.11:25:"),
            ParserTestPayload::error("[1fd2:23b4:4c96:1bed:4c89:3f5c:98ed:0494"),
            ParserTestPayload::error("[efab:ffac:bd1a:1a71:8fcd::1a8f"),

            ParserTestPayload::success("[v4.11]", "v4.11"),
            ParserTestPayload::success("[v4.11:25]", "v4.11:25"),
            ParserTestPayload::success("[v4.11:25:]", "v4.11:25:"),
            ParserTestPayload::success("[1fd2:23b4:4c96:1bed:4c89:3f5c:98ed:0494]", "1fd2:23b4:4c96:1bed:4c89:3f5c:98ed:0494"),
            ParserTestPayload::success("[efab:ffac:bd1a:1a71:8fcd::1a8f]", "efab:ffac:bd1a:1a71:8fcd::1a8f"),
            ParserTestPayload::success("[v77.abz:25:]", "v77.abz:25:")
        )
);

TEST_P(UriParserIPLiteralTestingFixture, TestThatIPLiteralParsingIsCorrect) {
    const auto& validation_data = GetParam();

    const auto& original_text = validation_data.original_text;
    const auto& expected_status = validation_data.expected_status;
    const auto& expected_text = validation_data.expected_text;

    std::optional<std::string> parsed_value;
    uri::__internal::TokenReader reader(original_text);

    EXPECT_EQ(uri::__internal::IPLiteral(reader, parsed_value) && !reader.hasNext(), expected_status);

    // Check only fully matched inputs.
    if (!reader.hasNext()) {
        EXPECT_EQ(parsed_value, expected_text);
    }
}
