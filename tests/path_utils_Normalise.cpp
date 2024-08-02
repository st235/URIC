#include <gtest/gtest.h>

#include <string>
#include <utility>
#include <vector>

#include "path_utils.h"

using TestPayload = std::pair<std::string, std::string>;
class PathUtilsNormaliseTestingFixture: public ::testing::TestWithParam<TestPayload> {};

INSTANTIATE_TEST_SUITE_P(
        PathUtilsTests,
        PathUtilsNormaliseTestingFixture,
        ::testing::Values(
            std::make_pair("", ""),
            std::make_pair("/", ""),
            std::make_pair("a", "a"),
            std::make_pair("a/", "a"),
            std::make_pair("ab", "ab"),
            std::make_pair("ab/cd/e", "ab/cd/e"),
            std::make_pair("ab/%31/", "ab/1"),
            std::make_pair("ab/ /..", "ab"),
            std::make_pair("ab/ /.", "ab/%20"),
            std::make_pair("ab/%5e", "ab/%5E"),
            std::make_pair("ab/%48%65%6c%6C%6f%5f%77%6F%72%6C%64/", "ab/Hello_world"),
            std::make_pair("ab/he%6c%6C%6f_w%6F%72%6C%64", "ab/hello_world"),
            std::make_pair("ab ", "ab%20"),
            std::make_pair("ab .", "ab%20."),
            std::make_pair("/`so called string`/a", "/%60so%20called%20string%60/a"),
            std::make_pair("a/b/c/./././d/e/./f/g/./h", "a/b/c/d/e/f/g/h"),
            std::make_pair("a/b/c/././../d/e/../f/g/../h", "a/b/d/f/h"),
            std::make_pair("a/b/c/./../../../../../../../../", ""),
            std::make_pair("a/b/c/./../../../../../../../../h", "h"),
            std::make_pair("ab%30%31", "ab01"),
            std::make_pair("ab%41%42%5A", "abABZ"),
            std::make_pair("ab%61%63%7A", "abacz"),
            std::make_pair("%2D%2E%5F%7E", "-._~"),
            std::make_pair("<generic>", "%3Cgeneric%3E"),
            std::make_pair("ab %5b %8E %aa", "ab%20%5B%20%8E%20%AA")
        )
);

TEST_P(PathUtilsNormaliseTestingFixture, NormaliseReturnsRightSegmentation) {
    const auto& pair = GetParam();

    const auto& path = pair.first;
    const auto& expected_path = pair.second;

    EXPECT_EQ(uri::path::Normalise(path), expected_path);
}
