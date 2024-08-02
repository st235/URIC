#include <gtest/gtest.h>

#include <string>
#include <utility>
#include <vector>

#include "path_utils.h"

using segments_t = std::vector<std::string>;

using TestPayload = std::pair<segments_t, segments_t>;
class PathNormaliserRemoveDotSegmentsTestingFixture: public ::testing::TestWithParam<TestPayload> {};

INSTANTIATE_TEST_SUITE_P(
        PathNormaliserTests,
        PathNormaliserRemoveDotSegmentsTestingFixture,
        ::testing::Values(
            std::make_pair(segments_t({ { "" } }), segments_t({ { "" } })),
            std::make_pair(segments_t({ { "abcd" } }), segments_t({ { "abcd" } })),
            std::make_pair(segments_t({ { "abcd" }, { "." } }), segments_t({ { "abcd" } })),
            std::make_pair(segments_t({ { "." } }), segments_t({ { "" } })),
            std::make_pair(segments_t({ { ".." } }), segments_t({ { "" } })),
            std::make_pair(segments_t({ { "a" }, { ".." }, { ".." }, { ".." } }), segments_t({ { "" } })),
            std::make_pair(segments_t({ { "a" }, { "b" }, { ".." }, { "c" } }), segments_t({ { "a" }, { "c" } })),
            std::make_pair(segments_t({ { "a" }, { "b" }, { "." }, { "c" } }), segments_t({ { "a" }, { "b" }, { "c" } })),
            std::make_pair(segments_t({ { "a" }, { "b" }, { ".." }, { ".." } }), segments_t({ { "" } })),
            std::make_pair(segments_t({ { "a" }, { "." }, { ".." }, { "c" } }), segments_t({ { "c" } }))
        )
);

TEST_P(PathNormaliserRemoveDotSegmentsTestingFixture, RemoveDotSegmentsReturnsRightSegmentation) {
    const auto& pair = GetParam();

    const auto& input = pair.first;
    const auto& expected_segments = pair.second;

    EXPECT_EQ(uri::path::RemoveDotSegments(input), expected_segments);
}
