#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"
#include "utils/parser_test_utils.h"

using tests::ParserTestPayload;

class UriParserPortTestingFixture: public ::testing::TestWithParam<ParserTestPayload> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserPortTests,
        UriParserPortTestingFixture,
        ::testing::Values(
            ParserTestPayload::error("AAAAA"),
            ParserTestPayload::error("G"),

            ParserTestPayload::success(""),
            ParserTestPayload::success("1"),
            ParserTestPayload::success("18"),
            ParserTestPayload::success("80"),
            ParserTestPayload::success("3036"),
            ParserTestPayload::success("8080"),
            ParserTestPayload::success("21"),
            ParserTestPayload::success("22"),
            ParserTestPayload::success("23"),
            ParserTestPayload::success("143"),
            ParserTestPayload::success("443"),
            ParserTestPayload::success("20")
        )
);

TEST_P(UriParserPortTestingFixture, TestThatPortParsingIsCorrect) {
    const auto& validation_data = GetParam();

    const auto& original_text = validation_data.original_text;
    const auto& expected_status = validation_data.expected_status;
    const auto& expected_text = validation_data.expected_text;

    std::optional<std::string> parsed_value;
    uri::__internal::TokenReader reader(original_text);

    EXPECT_EQ(uri::__internal::port(reader, parsed_value) && !reader.hasNext(), expected_status);

    // Check only fully matched inputs.
    if (!reader.hasNext()) {
        EXPECT_EQ(parsed_value, expected_text);
    }
}
