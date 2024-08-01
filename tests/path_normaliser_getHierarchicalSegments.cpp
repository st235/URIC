#include <gtest/gtest.h>

#include <string>
#include <utility>
#include <vector>

#include "path_normaliser.h"

using uri::PathNormaliser;

using segments_t = std::vector<std::string>;

using TestPayload = std::pair<std::string, segments_t>;
class PathNormaliserGetHierarchicalSegmentsTestingFixture: public ::testing::TestWithParam<TestPayload> {};

INSTANTIATE_TEST_SUITE_P(
        PathNormaliserTests,
        PathNormaliserGetHierarchicalSegmentsTestingFixture,
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

TEST_P(PathNormaliserGetHierarchicalSegmentsTestingFixture, GetHierarchicalSegmentsReturnsRightSegmentation) {
    const auto& pair = GetParam();

    const auto& input = pair.first;
    const auto& expected_segments = pair.second;

    EXPECT_EQ(PathNormaliser::getHierarchicalSegments(input), expected_segments);
}
