#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"

using ValidationData = std::pair<std::string, bool>;

class UriParserAbsoluteUriTestingFixture: public ::testing::TestWithParam<ValidationData> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserAbsoluteUriTests,
        UriParserAbsoluteUriTestingFixture,
        ::testing::Values(
            std::make_pair("", false),
            std::make_pair(":", false),
            std::make_pair(":website.com?q=5", false),
            std::make_pair("localhost", false),
            std::make_pair("https://website.com#fragment_is_illegal_in_absolute_uri", false),

            std::make_pair("https://example.com/mongodb-mercurial-cache-angular-information-architecture/s", true),
            std::make_pair("https://example.com/content-marketing-responsive-mongodb-gcp-ab-testing/9", true),
            std::make_pair("https://example.com/seo-bounce-rate-mvc-wireframe-call-to-action/4", true),
            std::make_pair("https://example.com/responsive-kubernetes-cache-landing-page-docker/m", true),
            std::make_pair("https://example.com/joomla-mysql-github-svn-wireframe/r", true),
            std::make_pair("https://example.com/express-wordpress-python-ppc-vue/p", true),
            std::make_pair("https://example.com/digitalocean-content-strategy-drupal-jquery-ab-testing/R", true),
            std::make_pair("https://example.com/jquery-server-python-framework-gitlab/N", true),
            std::make_pair("https://example.com/cdn-bitbucket-drupal-react-node/r", true),
            std::make_pair("https://example.com/angular-rails-azure-wordpress-spring/f?q=5k_fasdasd", true),

            std::make_pair("mailto:email@org.com", true)
        )
);

TEST_P(UriParserAbsoluteUriTestingFixture, TestThatAbsoluteUriParsingIsCorrect) {
    const auto& pair = GetParam();

    const auto& text = pair.first;
    const auto& expected_result = pair.second;

    uri::__internal::TokenReader reader(text);
    EXPECT_EQ(uri::__internal::absoluteUri(reader), expected_result);
}
