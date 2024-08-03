#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"
#include "utils/parser_test_utils.h"

using UriTestPayload = tests::UriTestPayload;

class UriParserUriReferenceTestingFixture: public ::testing::TestWithParam<UriTestPayload> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserUriReferenceTests,
        UriParserUriReferenceTestingFixture,
        ::testing::Values(
            UriTestPayload::success("")
                .expectPath(""),

            UriTestPayload::success("/")
                .expectPath("/"),

            UriTestPayload::success("http://34.159.184.124/tag/wp-content/posts?filter=active")
                .expectScheme("http")
                .expectHost("34.159.184.124", uri::__internal::HostType::kIPv4)
                .expectPath("/tag/wp-content/posts")
                .expectQuery("filter=active"),

            UriTestPayload::success("http://93.235.104.52:42560/search/blog/tags/blog#footer")
                .expectScheme("http")
                .expectHost("93.235.104.52", uri::__internal::HostType::kIPv4)
                .expectPort("42560")
                .expectPath("/search/blog/tags/blog")
                .expectFragment("footer"),

            UriTestPayload::success("http://152.35.176.42/list/app/wp-content#section2")
                .expectScheme("http")
                .expectHost("152.35.176.42", uri::__internal::HostType::kIPv4)
                .expectPath("/list/app/wp-content")
                .expectFragment("section2"),

            UriTestPayload::success("http://[8bd1:bbfa:fbee:9799:a368:e0b7:d214:75cb]/categories/list?id=123")
                .expectScheme("http")
                .expectHost("8bd1:bbfa:fbee:9799:a368:e0b7:d214:75cb", uri::__internal::HostType::kIPLiteral)
                .expectPath("/categories/list")
                .expectQuery("id=123"),

            UriTestPayload::success("http://hernandez-monroe.com/tag/search/blog?name=test")
                .expectScheme("http")
                .expectHost("hernandez-monroe.com")
                .expectPath("/tag/search/blog")
                .expectQuery("name=test"),

            UriTestPayload::success("http://135.3.47.89:19900/category/app/app/categories/wp-content?name=test#home")
                .expectScheme("http")
                .expectHost("135.3.47.89", uri::__internal::HostType::kIPv4)
                .expectPort("19900")
                .expectPath("/category/app/app/categories/wp-content")
                .expectQuery("name=test")
                .expectFragment("home"),

            UriTestPayload::success("http://178.108.232.60/tags/list/explore?id=123#about")
                .expectScheme("http")
                .expectHost("178.108.232.60", uri::__internal::HostType::kIPv4)
                .expectPath("/tags/list/explore")
                .expectQuery("id=123")
                .expectFragment("about"),

            UriTestPayload::success("http://45.211.216.208/list/posts?name=test#home")
                .expectScheme("http")
                .expectHost("45.211.216.208", uri::__internal::HostType::kIPv4)
                .expectPath("/list/posts")
                .expectQuery("name=test")
                .expectFragment("home"),

            UriTestPayload::success("https://aguirre.org/category/list/wp-content/tag?sort=asc&page=2")
                .expectScheme("https")
                .expectHost("aguirre.org")
                .expectPath("/category/list/wp-content/tag")
                .expectQuery("sort=asc&page=2"),

            UriTestPayload::success("http://128.235.96.110/tags/category?name=test")
                .expectScheme("http")
                .expectHost("128.235.96.110", uri::__internal::HostType::kIPv4)
                .expectPath("/tags/category")
                .expectQuery("name=test"),

            UriTestPayload::success("//164.243.116.133/app/list/list/explore#footer")
                .expectHost("164.243.116.133", uri::__internal::HostType::kIPv4)
                .expectPath("/app/list/list/explore")
                .expectFragment("footer"),

            UriTestPayload::success("//173.161.162.64/list/tag?filter=active#section1")
                .expectHost("173.161.162.64", uri::__internal::HostType::kIPv4)
                .expectPath("/list/tag")
                .expectQuery("filter=active")
                .expectFragment("section1"),

            UriTestPayload::success("//71.219.19.61/blog/tags/category/app/explore")
                .expectHost("71.219.19.61", uri::__internal::HostType::kIPv4)
                .expectPath("/blog/tags/category/app/explore"),

            UriTestPayload::success("//[9ae3:5ac4:30fe:9024:328f:dcd7:52ac:b87a]/app")
                .expectHost("9ae3:5ac4:30fe:9024:328f:dcd7:52ac:b87a", uri::__internal::HostType::kIPLiteral)
                .expectPath("/app"),

            UriTestPayload::success("//208.50.229.245/main/search/posts/tags/tag?q=keyword#section1")
                .expectHost("208.50.229.245", uri::__internal::HostType::kIPv4)
                .expectPath("/main/search/posts/tags/tag")
                .expectQuery("q=keyword")
                .expectFragment("section1"),

            UriTestPayload::success("//[f030:82ad:9392:b56:f172:66f7:5c2b:2083]/category/posts/blog?search=query#contact")
                .expectHost("f030:82ad:9392:b56:f172:66f7:5c2b:2083", uri::__internal::HostType::kIPLiteral)
                .expectPath("/category/posts/blog")
                .expectQuery("search=query")
                .expectFragment("contact"),

            UriTestPayload::success("//11.153.210.178:21253/blog/posts?beginner=brass&art=bone#home")
                .expectHost("11.153.210.178", uri::__internal::HostType::kIPv4)
                .expectPort("21253")
                .expectPath("/blog/posts")
                .expectQuery("beginner=brass&art=bone")
                .expectFragment("home"),

            UriTestPayload::success("//212.224.97.107:54858/main")
                .expectHost("212.224.97.107", uri::__internal::HostType::kIPv4)
                .expectPort("54858")
                .expectPath("/main"),

            UriTestPayload::success("//[2ce3:abf7:2741:777d:daf5:9bb6:3df:9a28]/explore/tag/main/posts/main")
                .expectHost("2ce3:abf7:2741:777d:daf5:9bb6:3df:9a28", uri::__internal::HostType::kIPLiteral)
                .expectPath("/explore/tag/main/posts/main"),

            UriTestPayload::success("//garcia-washington.net/tags/main")
                .expectHost("garcia-washington.net")
                .expectPath("/tags/main"),

            UriTestPayload::success("/blog/categories/explore/app/blog?name=test")
                .expectPath("/blog/categories/explore/app/blog")
                .expectQuery("name=test"),

            UriTestPayload::success("/category")
                .expectPath("/category"),

            UriTestPayload::success("/category/categories/list?search=query#home")
                .expectPath("/category/categories/list")
                .expectQuery("search=query")
                .expectFragment("home"),

            UriTestPayload::success("/tags?id=123#about")
                .expectPath("/tags")
                .expectQuery("id=123")
                .expectFragment("about"),

            UriTestPayload::success("/posts/category/list#about")
                .expectPath("/posts/category/list")
                .expectFragment("about"),

            UriTestPayload::success("/list/tag/posts/tags/explore?name=test#section2")
                .expectPath("/list/tag/posts/tags/explore")
                .expectQuery("name=test")
                .expectFragment("section2"),

            UriTestPayload::success("/search/app/blog/list")
                .expectPath("/search/app/blog/list"),

            UriTestPayload::success("/posts/posts/blog/explore/list")
                .expectPath("/posts/posts/blog/explore/list"),

            UriTestPayload::success("/search/wp-content#home")
                .expectPath("/search/wp-content")
                .expectFragment("home"),

            UriTestPayload::success("/explore/tags/list/search?filter=active#contact")
                .expectPath("/explore/tags/list/search")
                .expectQuery("filter=active")
                .expectFragment("contact"),

            UriTestPayload::success("search/wp-content/blog/search/wp-content#contact")
                .expectPath("search/wp-content/blog/search/wp-content")
                .expectFragment("contact"),

            UriTestPayload::success("tag/blog/main/wp-content/category?q=keyword#about")
                .expectPath("tag/blog/main/wp-content/category")
                .expectQuery("q=keyword")
                .expectFragment("about"),

            UriTestPayload::success("category/explore/category/category/app?name=test")
                .expectPath("category/explore/category/category/app")
                .expectQuery("name=test"),

            UriTestPayload::success("tag/category/categories/tags?id=123")
                .expectPath("tag/category/categories/tags")
                .expectQuery("id=123"),

            UriTestPayload::success("explore/blog/wp-content?beginner=brass&art=bone#home")
                .expectPath("explore/blog/wp-content")
                .expectQuery("beginner=brass&art=bone")
                .expectFragment("home"),

            UriTestPayload::success("blog/category/tags/list")
                .expectPath("blog/category/tags/list"),

            UriTestPayload::success("wp-content/posts/wp-content/tags/main?id=123#contact")
                .expectPath("wp-content/posts/wp-content/tags/main")
                .expectQuery("id=123")
                .expectFragment("contact"),

            UriTestPayload::success("category/categories/app?id=123")
                .expectPath("category/categories/app")
                .expectQuery("id=123"),

            UriTestPayload::success("list/explore/wp-content?sort=asc&page=2")
                .expectPath("list/explore/wp-content")
                .expectQuery("sort=asc&page=2"),

            UriTestPayload::success("main/explore/categories/posts/list?id=123")
                .expectPath("main/explore/categories/posts/list")
                .expectQuery("id=123")
        )
);

TEST_P(UriParserUriReferenceTestingFixture, TestThatUriParsingIsCorrect) {
    const auto& authority_payload = GetParam();

    const auto& original_text = authority_payload.original_text;

    const auto& expected_status = authority_payload.expected_status;
    const auto& expected_scheme = authority_payload.expected_scheme;
    const auto& expected_userInfo = authority_payload.expected_userInfo;
    const auto& expected_host = authority_payload.expected_host;
    const auto& expected_host_type = authority_payload.expected_host_type;
    const auto& expected_port = authority_payload.expected_port;
    const auto& expected_path = authority_payload.expected_path;
    const auto& expected_query = authority_payload.expected_query;
    const auto& expected_fragment = authority_payload.expected_fragment;

    std::optional<std::string> parsed_scheme;
    std::optional<std::string> parsed_userInfo;
    std::optional<std::string> parsed_host;
    std::optional<uri::__internal::HostType> parsed_host_type;
    std::optional<std::string> parsed_port;
    std::optional<std::string> parsed_path;
    std::optional<std::string> parsed_query;
    std::optional<std::string> parsed_fragment;
    uri::__internal::TokenReader reader(original_text);

    EXPECT_EQ(
        uri::__internal::UriReference(reader,
            parsed_scheme,
            parsed_userInfo, parsed_host, parsed_host_type, parsed_port,
            parsed_path,
            parsed_query, parsed_fragment), expected_status);

    EXPECT_EQ(parsed_scheme, expected_scheme);
    EXPECT_EQ(parsed_userInfo, expected_userInfo);
    EXPECT_EQ(parsed_host, expected_host);
    EXPECT_EQ(parsed_host_type, expected_host_type);
    EXPECT_EQ(parsed_port, expected_port);
    EXPECT_EQ(parsed_path, expected_path);
    EXPECT_EQ(parsed_query, expected_query);
    EXPECT_EQ(parsed_fragment, expected_fragment);
}
