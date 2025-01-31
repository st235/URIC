#include <gtest/gtest.h>

#include <string>
#include <utility>
#include <vector>

#include "path_utils.h"

using segments_t = std::vector<std::string>;

using TestPayload = std::pair<std::string, segments_t>;
class PathUtilsGetHierarchicalSegmentsTestingFixture: public ::testing::TestWithParam<TestPayload> {};

INSTANTIATE_TEST_SUITE_P(
        PathUtilsTests,
        PathUtilsGetHierarchicalSegmentsTestingFixture,
        ::testing::Values(
            std::make_pair("", segments_t({ { "" } })),
            std::make_pair("abcd", segments_t({ { "abcd" } })),
            std::make_pair("./", segments_t({ { "." } })),
            std::make_pair("./aa", segments_t({ { "." }, { "aa" } })),
            std::make_pair("./../..", segments_t({ { "." }, { ".." }, { ".." } })),
            std::make_pair("/./../..", segments_t({ { "" }, { "." }, { ".." }, { ".." } })),
            std::make_pair("abc/def", segments_t({ { "abc" }, { "def" } })),
            std::make_pair("a/./../b./c../a/.", segments_t({ { "a" }, { "." }, { ".." }, { "b." }, { "c.." }, { "a" }, { "." } }))
        )
);

TEST_P(PathUtilsGetHierarchicalSegmentsTestingFixture, GetHierarchicalSegmentsReturnsRightSegmentation) {
    const auto& pair = GetParam();

    const auto& input = pair.first;
    const auto& expected_segments = pair.second;

    EXPECT_EQ(uri::path::SplitHierarchicalSegments(input), expected_segments);
}
