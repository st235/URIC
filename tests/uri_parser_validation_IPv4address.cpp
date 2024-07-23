#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"
#include "utils/parser_test_utils.h"

using tests::ParserTestPayload;

class UriParserIPv4addressTestingFixture: public ::testing::TestWithParam<ParserTestPayload> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserIPv4addressTests,
        UriParserIPv4addressTestingFixture,
        ::testing::Values(
            ParserTestPayload::error(""),
            ParserTestPayload::error("abcsd"),
            ParserTestPayload::error("1"),
            ParserTestPayload::error("1."),
            ParserTestPayload::error("1.."),
            ParserTestPayload::error("1..."),
            ParserTestPayload::error("1."),
            ParserTestPayload::error("1.2."),
            ParserTestPayload::error("1.2.3."),
            ParserTestPayload::error("256.256.256.256"),
            ParserTestPayload::error("-1.1.1.1"),

            ParserTestPayload::success("1.1.1.1"),
            ParserTestPayload::success("1.2.3.4"),
            ParserTestPayload::success("240.61.57.214"),
            ParserTestPayload::success("15.170.164.83"),
            ParserTestPayload::success("248.176.111.71"),
            ParserTestPayload::success("183.5.156.132"),
            ParserTestPayload::success("75.204.127.115"),
            ParserTestPayload::success("43.181.85.76"),
            ParserTestPayload::success("111.56.86.199"),
            ParserTestPayload::success("161.97.115.172"),
            ParserTestPayload::success("31.65.212.249"),
            ParserTestPayload::success("160.30.239.153"),
            ParserTestPayload::success("55.16.69.241"),
            ParserTestPayload::success("133.90.28.223"),
            ParserTestPayload::success("215.126.103.174"),
            ParserTestPayload::success("235.129.168.182"),
            ParserTestPayload::success("126.250.190.81"),
            ParserTestPayload::success("20.156.35.151"),
            ParserTestPayload::success("5.75.252.164"),
            ParserTestPayload::success("188.24.112.27"),
            ParserTestPayload::success("217.66.134.227"),
            ParserTestPayload::success("118.127.45.80"),
            ParserTestPayload::success("216.97.162.109"),
            ParserTestPayload::success("55.103.248.181"),
            ParserTestPayload::success("113.143.88.205"),
            ParserTestPayload::success("222.3.87.85"),
            ParserTestPayload::success("241.141.151.55"),
            ParserTestPayload::success("171.246.14.99"),
            ParserTestPayload::success("2.219.31.220"),
            ParserTestPayload::success("16.59.90.192"),
            ParserTestPayload::success("39.78.137.115"),
            ParserTestPayload::success("69.67.41.18"),
            ParserTestPayload::success("143.223.80.23"),
            ParserTestPayload::success("62.56.133.36"),
            ParserTestPayload::success("112.143.193.115"),
            ParserTestPayload::success("220.50.147.41"),
            ParserTestPayload::success("243.151.125.71"),
            ParserTestPayload::success("29.232.187.76"),
            ParserTestPayload::success("174.206.68.212"),
            ParserTestPayload::success("241.54.49.84"),
            ParserTestPayload::success("132.176.4.198"),
            ParserTestPayload::success("153.116.75.202"),
            ParserTestPayload::success("110.136.24.162"),
            ParserTestPayload::success("142.169.243.52"),
            ParserTestPayload::success("93.170.246.41"),
            ParserTestPayload::success("1.207.43.146"),
            ParserTestPayload::success("95.116.121.16"),
            ParserTestPayload::success("98.228.27.169"),
            ParserTestPayload::success("221.198.235.155"),
            ParserTestPayload::success("7.220.32.113"),
            ParserTestPayload::success("64.0.106.98"),
            ParserTestPayload::success("165.110.234.43")
        )
);

TEST_P(UriParserIPv4addressTestingFixture, TestThatIPv4addressParsingIsCorrect) {
    const auto& validation_data = GetParam();

    const auto& original_text = validation_data.original_text;
    const auto& expected_status = validation_data.expected_status;
    const auto& expected_text = validation_data.expected_text;

    std::optional<std::string> parsed_value;
    uri::__internal::TokenReader reader(original_text);

    EXPECT_EQ(uri::__internal::IPv4address(reader, parsed_value) && !reader.hasNext(), expected_status);

    // Check only fully matched inputs.
    if (!reader.hasNext()) {
        EXPECT_EQ(parsed_value, expected_text);
    }
}
