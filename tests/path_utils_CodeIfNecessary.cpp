#include <gtest/gtest.h>

#include <string>
#include <utility>
#include <vector>

#include "path_utils.h"

using TestPayload = std::pair<std::string, std::string>;
class PathUtilsCodeIfNecessaryTestingFixture: public ::testing::TestWithParam<TestPayload> {};

INSTANTIATE_TEST_SUITE_P(
        PathUtilsTests,
        PathUtilsCodeIfNecessaryTestingFixture,
        ::testing::Values(
            std::make_pair("", ""),
            std::make_pair("a", "a"),
            std::make_pair("ab", "ab"),
            std::make_pair("ab ", "ab%20"),

            // Decode.
            //  Numbers.
            std::make_pair("ab%30%31", "ab01"),
            //  Alphabet.
            std::make_pair("ab%41%42%5A", "abABZ"),
            std::make_pair("ab%61%63%7A", "abacz"),
            // Special.
            std::make_pair("%2D%2E%5F%7E", "-._~"),

            // Encoding.
            std::make_pair("<generic>", "%3Cgeneric%3E"),

            // Capitalisation of PCT Encoded symbols.
            std::make_pair("ab %5b %8E %aa", "ab%20%5B%20%8E%20%AA")
        )
);

TEST_P(PathUtilsCodeIfNecessaryTestingFixture, CodeIfNecessaryReturnsRightSegmentation) {
    const auto& pair = GetParam();

    const auto& path = pair.first;
    const auto& expected_path = pair.second;

    EXPECT_EQ(uri::path::CodeIfNecessary(path), expected_path);
}
