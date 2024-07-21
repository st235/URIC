#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"

using ValidationData = std::pair<std::string, bool>;

class UriParserIPv4addressTestingFixture: public ::testing::TestWithParam<ValidationData> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserIPv4addressTests,
        UriParserIPv4addressTestingFixture,
        ::testing::Values(
            std::make_pair("", false),
            std::make_pair("abcsd", false),
            std::make_pair("1", false),
            std::make_pair("1.", false),
            std::make_pair("1..", false),
            std::make_pair("1...", false),
            std::make_pair("1.", false),
            std::make_pair("1.2.", false),
            std::make_pair("1.2.3.", false),
            std::make_pair("256.256.256.256", false),
            std::make_pair("-1.1.1.1", false),

            std::make_pair("1.1.1.1", true),
            std::make_pair("1.2.3.4", true),
            std::make_pair("240.61.57.214", true),
            std::make_pair("15.170.164.83", true),
            std::make_pair("248.176.111.71", true),
            std::make_pair("183.5.156.132", true),
            std::make_pair("75.204.127.115", true),
            std::make_pair("43.181.85.76", true),
            std::make_pair("111.56.86.199", true),
            std::make_pair("161.97.115.172", true),
            std::make_pair("31.65.212.249", true),
            std::make_pair("160.30.239.153", true),
            std::make_pair("55.16.69.241", true),
            std::make_pair("133.90.28.223", true),
            std::make_pair("215.126.103.174", true),
            std::make_pair("235.129.168.182", true),
            std::make_pair("126.250.190.81", true),
            std::make_pair("20.156.35.151", true),
            std::make_pair("5.75.252.164", true),
            std::make_pair("188.24.112.27", true),
            std::make_pair("217.66.134.227", true),
            std::make_pair("118.127.45.80", true),
            std::make_pair("216.97.162.109", true),
            std::make_pair("55.103.248.181", true),
            std::make_pair("113.143.88.205", true),
            std::make_pair("222.3.87.85", true),
            std::make_pair("241.141.151.55", true),
            std::make_pair("171.246.14.99", true),
            std::make_pair("2.219.31.220", true),
            std::make_pair("16.59.90.192", true),
            std::make_pair("39.78.137.115", true),
            std::make_pair("69.67.41.18", true),
            std::make_pair("143.223.80.23", true),
            std::make_pair("62.56.133.36", true),
            std::make_pair("112.143.193.115", true),
            std::make_pair("220.50.147.41", true),
            std::make_pair("243.151.125.71", true),
            std::make_pair("29.232.187.76", true),
            std::make_pair("174.206.68.212", true),
            std::make_pair("241.54.49.84", true),
            std::make_pair("132.176.4.198", true),
            std::make_pair("153.116.75.202", true),
            std::make_pair("110.136.24.162", true),
            std::make_pair("142.169.243.52", true),
            std::make_pair("93.170.246.41", true),
            std::make_pair("1.207.43.146", true),
            std::make_pair("95.116.121.16", true),
            std::make_pair("98.228.27.169", true),
            std::make_pair("221.198.235.155", true),
            std::make_pair("7.220.32.113", true),
            std::make_pair("64.0.106.98", true),
            std::make_pair("165.110.234.43", true)
        )
);

TEST_P(UriParserIPv4addressTestingFixture, TestThatIPv4addressParsingIsCorrect) {
    const auto& pair = GetParam();

    const auto& text = pair.first;
    const auto& expected_result = pair.second;

    uri::__internal::TokenReader reader(text);
    EXPECT_EQ(uri::__internal::IPv4address(reader) && !reader.hasNext(), expected_result);
}
