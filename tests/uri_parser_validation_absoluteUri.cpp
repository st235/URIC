#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"
#include "utils/parser_test_utils.h"

using UriTestPayload = tests::UriTestPayload;

class UriParserAbsoluteUriTestingFixture: public ::testing::TestWithParam<UriTestPayload> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserAbsoluteUriTests,
        UriParserAbsoluteUriTestingFixture,
        ::testing::Values(
            UriTestPayload::error(""),
            UriTestPayload::error(":"),
            UriTestPayload::error(":website.com?q=5"),
            UriTestPayload::error("localhost"),
            UriTestPayload::error("https://website.com#fragment_is_illegal_in_absolute_uri"),

            UriTestPayload::success("https://example.com/mongodb-mercurial-cache-angular-information-architecture/s")
                .expectScheme("https")
                .expectHost("example.com")
                .expectPath("/mongodb-mercurial-cache-angular-information-architecture/s"),
            UriTestPayload::success("https://example.com/content-marketing-responsive-mongodb-gcp-ab-testing/9")
                .expectScheme("https")
                .expectHost("example.com")
                .expectPath("/content-marketing-responsive-mongodb-gcp-ab-testing/9"),
            UriTestPayload::success("https://example.com/seo-bounce-rate-mvc-wireframe-call-to-action/4")
                .expectScheme("https")
                .expectHost("example.com")
                .expectPath("/seo-bounce-rate-mvc-wireframe-call-to-action/4"),
            UriTestPayload::success("https://example.com/responsive-kubernetes-cache-landing-page-docker/m")
                .expectScheme("https")
                .expectHost("example.com")
                .expectPath("/responsive-kubernetes-cache-landing-page-docker/m"),
            UriTestPayload::success("https://example.com/joomla-mysql-github-svn-wireframe/r")
                .expectScheme("https")
                .expectHost("example.com")
                .expectPath("/joomla-mysql-github-svn-wireframe/r"),
            UriTestPayload::success("https://example.com/express-wordpress-python-ppc-vue/p")
                .expectScheme("https")
                .expectHost("example.com")
                .expectPath("/express-wordpress-python-ppc-vue/p"),
            UriTestPayload::success("https://example.com/digitalocean-content-strategy-drupal-jquery-ab-testing/R")
                .expectScheme("https")
                .expectHost("example.com")
                .expectPath("/digitalocean-content-strategy-drupal-jquery-ab-testing/R"),
            UriTestPayload::success("https://example.com/jquery-server-python-framework-gitlab/N")
                .expectScheme("https")
                .expectHost("example.com")
                .expectPath("/jquery-server-python-framework-gitlab/N"),
            UriTestPayload::success("https://example.com/cdn-bitbucket-drupal-react-node/r")
                .expectScheme("https")
                .expectHost("example.com")
                .expectPath("/cdn-bitbucket-drupal-react-node/r"),
            UriTestPayload::success("https://example.com/angular-rails-azure-wordpress-spring/f?q=5k_fasdasd")
                .expectScheme("https")
                .expectHost("example.com")
                .expectPath("/angular-rails-azure-wordpress-spring/f")
                .expectQuery("q=5k_fasdasd"),

            UriTestPayload::success("mailto:email@org.com")
                .expectScheme("mailto")
                .expectPath("email@org.com")
        )
);

TEST_P(UriParserAbsoluteUriTestingFixture, TestThatAbsoluteUriParsingIsCorrect) {
    const auto& authority_payload = GetParam();

    const auto& original_text = authority_payload.original_text;

    const auto& expected_status = authority_payload.expected_status;
    const auto& expected_scheme = authority_payload.expected_scheme;
    const auto& expected_userInfo = authority_payload.expected_userInfo;
    const auto& expected_host = authority_payload.expected_host;
    const auto& expected_port = authority_payload.expected_port;
    const auto& expected_path = authority_payload.expected_path;
    const auto& expected_query = authority_payload.expected_query;

    std::optional<std::string> parsed_scheme;
    std::optional<std::string> parsed_userInfo;
    std::optional<std::string> parsed_host;
    std::optional<std::string> parsed_port;
    std::optional<std::string> parsed_path;
    std::optional<std::string> parsed_query;
    uri::__internal::TokenReader reader(original_text);

    EXPECT_EQ(
        uri::__internal::absoluteUri(reader,
            parsed_scheme,
            parsed_userInfo, parsed_host, parsed_port, parsed_path,
            parsed_query) &&
        !reader.hasNext(), expected_status);

    // Check only fully matched inputs.
    if (!reader.hasNext()) {
        EXPECT_EQ(parsed_scheme, expected_scheme);
        EXPECT_EQ(parsed_userInfo, expected_userInfo);
        EXPECT_EQ(parsed_host, expected_host);
        EXPECT_EQ(parsed_port, expected_port);
        EXPECT_EQ(parsed_path, expected_path);
        EXPECT_EQ(parsed_query, expected_query);
    }
}
