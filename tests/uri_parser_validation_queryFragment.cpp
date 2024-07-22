#include <gtest/gtest.h>

#include <optional>
#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"
#include "utils/parser_test_utils.h"

using tests::ParserTestPayload;

class UriParserQueryFragmentTestingFixture: public ::testing::TestWithParam<ParserTestPayload> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserQueryFragmentTests,
        UriParserQueryFragmentTestingFixture,
        ::testing::Values(
            ParserTestPayload::error("[]"),
            ParserTestPayload::error("a[]"),
            ParserTestPayload::error("a#b"),

            ParserTestPayload::success(""),
            ParserTestPayload::success("a"),
            ParserTestPayload::success("a01/"),
            ParserTestPayload::success("a01/b:as"),
            ParserTestPayload::success("0(hello)"),
            ParserTestPayload::success("abc0$asdads91+sdasd?"),
            ParserTestPayload::success("a=0@@@asw:")
        )
);

TEST_P(UriParserQueryFragmentTestingFixture, TestThatQueryFragmentParsingIsCorrect) {
    const auto& validation_data = GetParam();

    const auto& original_text = validation_data.original_text;
    const auto& expected_status = validation_data.expected_status;
    const auto& expected_text = validation_data.expected_text;

    std::optional<std::string> parsed_value;
    uri::__internal::TokenReader reader(original_text);

    EXPECT_EQ(uri::__internal::queryFragment(reader, parsed_value) && !reader.hasNext(), expected_status);

    // Check only fully matched inputs.
    if (!reader.hasNext()) {
        EXPECT_EQ(parsed_value, expected_text);
    }
}
