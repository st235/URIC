#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"
#include "utils/parser_test_utils.h"

using tests::ParserTestPayload;

class UriParserSchemeTestingFixture: public ::testing::TestWithParam<ParserTestPayload> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserSchemeTests,
        UriParserSchemeTestingFixture,
        ::testing::Values(
            ParserTestPayload::error(""),

            ParserTestPayload::success("http"),
            ParserTestPayload::success("https"),
            ParserTestPayload::success("ws"),
            ParserTestPayload::success("ssh"),
            ParserTestPayload::success("mailto"),
            ParserTestPayload::success("ftp"),
            ParserTestPayload::success("a+b"),
            ParserTestPayload::success("a.b")
        )
);

TEST_P(UriParserSchemeTestingFixture, TestThatSchemeParsingIsCorrect) {
    const auto& validation_data = GetParam();

    const auto& original_text = validation_data.original_text;
    const auto& expected_status = validation_data.expected_status;
    const auto& expected_text = validation_data.expected_text;

    std::optional<std::string> parsed_value;
    uri::__internal::TokenReader reader(original_text);

    EXPECT_EQ(uri::__internal::scheme(reader, parsed_value) && !reader.hasNext(), expected_status);

    // Check only fully matched inputs.
    if (!reader.hasNext()) {
        EXPECT_EQ(parsed_value, expected_text);
    }
}
