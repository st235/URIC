#include <gtest/gtest.h>

#include <string>
#include <utility>
#include <unordered_map>

#include "url.h"

using uri::Url;

using query_params_t = std::unordered_map<std::string, std::string>;

using TestPayload = std::pair<std::string, query_params_t>;
class UrlQueryTestingFixture: public ::testing::TestWithParam<TestPayload> {};

INSTANTIATE_TEST_SUITE_P(
        UrlQueryParsingTests,
        UrlQueryTestingFixture,
        ::testing::Values(
            std::make_pair("http://github.com/st235?q=5", query_params_t({ {"q", "5"} })),
            std::make_pair("http://github.com/st235?q=5&&", query_params_t({ {"q", "5"} })),
            std::make_pair("http://github.com/st235?q1=9.88&a=b&re=t", query_params_t({ {"q1", "9.88"}, {"a", "b"}, {"re", "t"} })),
            std::make_pair("http://github.com/st235?a=hello&b=&", query_params_t({ {"a", "hello"}, {"b", ""} })),
            std::make_pair("http://github.com/st235?hello=world&=&", query_params_t({ {"hello", "world"}, {"", ""} })),
            std::make_pair("http://github.com/st235?hello=world&=&==", query_params_t({ {"hello", "world"}, {"", "="} })),
            std::make_pair("http://github.com/st235?===", query_params_t({ {"", "=="} })),
            std::make_pair("/posts/tag/app/search#contact", query_params_t())
        )
);

TEST_P(UrlQueryTestingFixture, TestThatH16ParsingIsCorrect) {
    const auto& pair = GetParam();

    const auto& input = pair.first;
    const auto& actual_url = Url::parse(input);
    const auto& expected_query_params = pair.second;

    EXPECT_EQ(actual_url.value().getQuery(), expected_query_params);
}
