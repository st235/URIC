#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"
#include "utils/parser_test_utils.h"

using tests::ParserTestPayload;

class UriParserRegNameTestingFixture: public ::testing::TestWithParam<ParserTestPayload> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserRegNameTests,
        UriParserRegNameTestingFixture,
        ::testing::Values(
            ParserTestPayload::error(":"),
            ParserTestPayload::error("@"),
            ParserTestPayload::error("abc:sdas"),
            ParserTestPayload::error("/sdasds"),
            ParserTestPayload::error("/1b"),
            ParserTestPayload::error("?q=5"),
            ParserTestPayload::error("#fragment"),
            ParserTestPayload::error("[ololo]"),
            ParserTestPayload::error("@gmail.com"),

            ParserTestPayload::success(""),
            ParserTestPayload::success("0"),
            ParserTestPayload::success("ab"),
            ParserTestPayload::success("a.sdas"),
            ParserTestPayload::success("~echo"),
            ParserTestPayload::success("1_000_000"),
            ParserTestPayload::success("(Hello%20world)"),
            ParserTestPayload::success("q=5&f=7"),
            ParserTestPayload::success("a01-sdas-bgdf%20")
        )
);

TEST_P(UriParserRegNameTestingFixture, TestThatRegNameParsingIsCorrect) {
    const auto& validation_data = GetParam();

    const auto& original_text = validation_data.original_text;
    const auto& expected_status = validation_data.expected_status;
    const auto& expected_text = validation_data.expected_text;

    std::optional<std::string> parsed_value;
    uri::__internal::TokenReader reader(original_text);

    EXPECT_EQ(uri::__internal::regName(reader, parsed_value) && !reader.hasNext(), expected_status);

    // Check only fully matched inputs.
    if (!reader.hasNext()) {
        EXPECT_EQ(parsed_value, expected_text);
    }
}
