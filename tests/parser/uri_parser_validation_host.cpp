#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"
#include "utils/parser_test_utils.h"

using tests::ParserTestPayload;

class UriParserHostTestingFixture: public ::testing::TestWithParam<ParserTestPayload> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserHostTests,
        UriParserHostTestingFixture,
        ::testing::Values(
            ParserTestPayload::error("v4.11:25:]"),
            ParserTestPayload::error("1fd2:23b4:4c96:1bed:4c89:3f5c:98ed:0494]"),
            ParserTestPayload::error("efab:ffac:bd1a:1a71:8fcd::1a8f]"),
            ParserTestPayload::error("[v4.11:25:"),
            ParserTestPayload::error("[1fd2:23b4:4c96:1bed:4c89:3f5c:98ed:0494"),
            ParserTestPayload::error("[efab:ffac:bd1a:1a71:8fcd::1a8f"),

            // IP-literal
            ParserTestPayload::success("[v4.11]", "v4.11"),
            ParserTestPayload::success("[v4.11:25]", "v4.11:25"),
            ParserTestPayload::success("[v4.11:25:]", "v4.11:25:"),
            ParserTestPayload::success("[1fd2:23b4:4c96:1bed:4c89:3f5c:98ed:0494]", "1fd2:23b4:4c96:1bed:4c89:3f5c:98ed:0494"),
            ParserTestPayload::success("[efab:ffac:bd1a:1a71:8fcd::1a8f]", "efab:ffac:bd1a:1a71:8fcd::1a8f"),
            ParserTestPayload::success("[v77.abz:25:]", "v77.abz:25:"),

            // IPv4address
            ParserTestPayload::success("82.239.179.164"),
            ParserTestPayload::success("23.6.209.89"),
            ParserTestPayload::success("86.143.252.23"),
            ParserTestPayload::success("124.1.165.76"),
            ParserTestPayload::success("91.24.186.22"),
            ParserTestPayload::success("88.36.159.30"),
            ParserTestPayload::success("24.25.81.113"),
            ParserTestPayload::success("7.75.209.57"),
            ParserTestPayload::success("11.6.36.223"),
            ParserTestPayload::success("233.155.227.64"),

            // reg-name
            ParserTestPayload::success(""),
            ParserTestPayload::success("a"),
            ParserTestPayload::success("v."),
            ParserTestPayload::success("v1."),
            ParserTestPayload::success("v.12345"),
            ParserTestPayload::success("localhost")
        )
);

TEST_P(UriParserHostTestingFixture, TestThatHostParsingIsCorrect) {
    const auto& validation_data = GetParam();

    const auto& original_text = validation_data.original_text;
    const auto& expected_status = validation_data.expected_status;
    const auto& expected_text = validation_data.expected_text;

    std::optional<std::string> parsed_host;
    std::optional<uri::__internal::HostType> parsed_host_type;
    uri::__internal::TokenReader reader(original_text);

    EXPECT_EQ(uri::__internal::host(reader, parsed_host, parsed_host_type) && !reader.hasNext(), expected_status);

    // Check only fully matched inputs.
    if (!reader.hasNext()) {
        EXPECT_EQ(parsed_host, expected_text);
    }
}
