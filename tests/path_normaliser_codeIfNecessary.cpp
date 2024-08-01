#include <gtest/gtest.h>

#include <string>
#include <utility>
#include <vector>

#include "path_normaliser.h"

using uri::PathNormaliser;

using segments_t = std::vector<std::string>;

using TestPayload = std::pair<segments_t, segments_t>;
class PathNormaliserCodeIfNecessaryTestingFixture: public ::testing::TestWithParam<TestPayload> {};

INSTANTIATE_TEST_SUITE_P(
        PathNormaliserTests,
        PathNormaliserCodeIfNecessaryTestingFixture,
        ::testing::Values(
            std::make_pair(segments_t({ { "" } }), segments_t({ { "" } })),
            std::make_pair(segments_t({ { "a" } }), segments_t({ { "a" } })),
            std::make_pair(segments_t({ { "ab" } }), segments_t({ { "ab" } })),
            std::make_pair(segments_t({ { "ab " } }), segments_t({ { "ab%20" } })),

            // Decode.
            //  Numbers.
            std::make_pair(segments_t({ { "ab%30%31" } }), segments_t({ { "ab01" } })),
            //  Alphabet.
            std::make_pair(segments_t({ { "ab%41%42%5A" } }), segments_t({ { "abABZ" } })),
            std::make_pair(segments_t({ { "ab%61%63%7A" } }), segments_t({ { "abacz" } })),
            // Special.
            std::make_pair(segments_t({ { "%2D%2E%5F%7E" } }), segments_t({ { "-._~" } })),

            // Encoding.
            std::make_pair(segments_t({ { "<generic>" } }), segments_t({ { "%3Cgeneric%3E" } })),

            // Capitalisation of PCT Encoded symbols.
            std::make_pair(segments_t({ { "ab %5b %8E %aa" } }), segments_t({ { "ab%20%5B%20%8E%20%AA" } }))
        )
);

TEST_P(PathNormaliserCodeIfNecessaryTestingFixture, CodeIfNecessaryReturnsRightSegmentation) {
    const auto& pair = GetParam();

    const auto& input = pair.first;
    const auto& expected_segments = pair.second;

    EXPECT_EQ(PathNormaliser::codeIfNecessary(input), expected_segments);
}
