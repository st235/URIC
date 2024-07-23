#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"
#include "utils/parser_test_utils.h"

using tests::ParserTestPayload;

class UriParserUserInfoTestingFixture: public ::testing::TestWithParam<ParserTestPayload> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserUserInfoTests,
        UriParserUserInfoTestingFixture,
        ::testing::Values(
            ParserTestPayload::error("#asdasd"),
            ParserTestPayload::error("/text"),
            ParserTestPayload::error("?notauserinfo"),

            ParserTestPayload::success(""),
            ParserTestPayload::success("github:st235"),
            ParserTestPayload::success("hell018"),
            ParserTestPayload::success("some_text"),
            ParserTestPayload::success("key=value&user=password")
        )
);

TEST_P(UriParserUserInfoTestingFixture, TestThatUserInfoParsingIsCorrect) {
    const auto& validation_data = GetParam();

    const auto& original_text = validation_data.original_text;
    const auto& expected_status = validation_data.expected_status;
    const auto& expected_text = validation_data.expected_text;

    std::optional<std::string> parsed_value;
    uri::__internal::TokenReader reader(original_text);

    EXPECT_EQ(uri::__internal::userInfo(reader, parsed_value) && !reader.hasNext(), expected_status);

    // Check only fully matched inputs.
    if (!reader.hasNext()) {
        EXPECT_EQ(parsed_value, expected_text);
    }
}
