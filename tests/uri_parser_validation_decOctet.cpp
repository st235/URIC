#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"

using ValidationData = std::pair<std::string, bool>;

class UriParserDecOctetTestingFixture: public ::testing::TestWithParam<ValidationData> {};

// dec-octet = DIGIT                 ; 0-9
//             / %x31-39 DIGIT       ; 10-99
//             / "1" 2DIGIT          ; 100-199
//             / "2" %x30-34 DIGIT   ; 200-249
//             / "25" %x30-35        ; 250-255
INSTANTIATE_TEST_SUITE_P(
        UriParserDecOctetTests,
        UriParserDecOctetTestingFixture,
        ::testing::Values(
            std::make_pair("", false),
            std::make_pair("256", false),
            std::make_pair("261", false),
            std::make_pair("300", false),
            std::make_pair("311", false),
            std::make_pair("547", false),
            std::make_pair("1000", false),
            std::make_pair("01", false),
            std::make_pair("025", false),

            std::make_pair("0", true),
            std::make_pair("1", true),
            std::make_pair("5", true),
            std::make_pair("9", true),
            std::make_pair("10", true),
            std::make_pair("99", true),
            std::make_pair("55", true),
            std::make_pair("100", true),
            std::make_pair("199", true),
            std::make_pair("200", true),
            std::make_pair("249", true),
            std::make_pair("250", true),
            std::make_pair("255", true)
        )
);

TEST_P(UriParserDecOctetTestingFixture, TestThatDecOctetParsingIsCorrect) {
    const auto& pair = GetParam();

    const auto& text = pair.first;
    const auto& expected_result = pair.second;

    uri::__internal::TokenReader reader(text);
    EXPECT_EQ(uri::__internal::decOctet(reader) && !reader.hasNext(), expected_result);
}
