#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "uri.h"

using uri::Uri;
using uri::Authority;

TEST(UriTests, UrisWithSameContentAreEqual) {
    Uri a("/hello_world", "query", "fragment");
    Uri b("/hello_world", "query", "fragment");
    EXPECT_EQ(a, b);
}

TEST(UriTests, UrisWithDifferentContentAreNotEqual) {
    Uri a("https", Authority("80"), "/path", "localhost");
    Uri b("ftp", Authority("80"), "/path", "localhost");
    EXPECT_NE(a, b);
}

using TestPayload = std::pair<std::string, Uri>;
class UriTestingFixture: public ::testing::TestWithParam<TestPayload> {};

INSTANTIATE_TEST_SUITE_P(
        UriParsingTests,
        UriTestingFixture,
        ::testing::Values(
            std::make_pair("https://able@218.110.62.47/explore?q=keyword#section1", Uri("https", Authority("218.110.62.47", std::nullopt, "able"), "/explore", "q=keyword", "section1")),
            std::make_pair("http://couple@104.27.227.174:27422/wp-content?name=test", Uri("http", Authority("104.27.227.174", "27422", "couple"), "/wp-content", "name=test", std::nullopt)),
            std::make_pair("http://production@186.149.105.224:49784/explore/main/categories", Uri("http", Authority("186.149.105.224", "49784", "production"), "/explore/main/categories", std::nullopt, std::nullopt)),
            std::make_pair("https://appear@52.189.27.178/categories/list/wp-content/posts#about", Uri("https", Authority("52.189.27.178", std::nullopt, "appear"), "/categories/list/wp-content/posts", std::nullopt, "about")),
            std::make_pair("http://often@[8c81:6c4f:3355:aea1:e2e7:22ba:ecf0:b427]/wp-content/tag?q=keyword#home", Uri("http", Authority("8c81:6c4f:3355:aea1:e2e7:22ba:ecf0:b427", std::nullopt, "often", /* isHostIPLiteral= */ true), "/wp-content/tag", "q=keyword", "home")),
            std::make_pair("http://97.115.225.46/wp-content/categories?search=query", Uri("http", Authority("97.115.225.46", std::nullopt, std::nullopt), "/wp-content/categories", "search=query", std::nullopt)),
            std::make_pair("https://124.49.252.8:60271/categories/category/search/categories/category?filter=active", Uri("https", Authority("124.49.252.8", "60271", std::nullopt), "/categories/category/search/categories/category", "filter=active", std::nullopt)),
            std::make_pair("https://one@[b0c0:38d4:4c13:8570:9a6d:f1b1:8fc6:131e]/main", Uri("https", Authority("b0c0:38d4:4c13:8570:9a6d:f1b1:8fc6:131e", std::nullopt, "one", /* isHostIPLiteral= */ true), "/main", std::nullopt, std::nullopt)),
            std::make_pair("https://brown.lawrence-king.murray.info/blog/main/explore/list", Uri("https", Authority("brown.lawrence-king.murray.info", std::nullopt, std::nullopt), "/blog/main/explore/list", std::nullopt, std::nullopt)),
            std::make_pair("https://greene.com/categories/category/search/categories/category?filter=active", Uri("https", Authority("greene.com", std::nullopt, std::nullopt), "/categories/category/search/categories/category", "filter=active", std::nullopt)),
            std::make_pair("http://powell.herrera.lambert.info/tags/posts/categories#about", Uri("http", Authority("powell.herrera.lambert.info", std::nullopt, std::nullopt), "/tags/posts/categories", std::nullopt, "about")),
            std::make_pair("https://12.150.26.161:63604/app/tags?filter=active", Uri("https", Authority("12.150.26.161", "63604", std::nullopt), "/app/tags", "filter=active", std::nullopt)),
            std::make_pair("http://along@[96c:25be:5333:60f2:5f45:e431:a55e:417c]/tags/explore/tags", Uri("http", Authority("96c:25be:5333:60f2:5f45:e431:a55e:417c", std::nullopt, "along", /* isHostIPLiteral= */ true), "/tags/explore/tags", std::nullopt, std::nullopt)),
            std::make_pair("https://hardy.torres.diaz.com/category/tag/explore/category?beginner=brass&art=bone", Uri("https", Authority("hardy.torres.diaz.com", std::nullopt, std::nullopt), "/category/tag/explore/category", "beginner=brass&art=bone", std::nullopt)),
            std::make_pair("http://cisneros.solomon-wallace.calderon.com/posts/posts?id=123", Uri("http", Authority("cisneros.solomon-wallace.calderon.com", std::nullopt, std::nullopt), "/posts/posts", "id=123", std::nullopt)),
            std::make_pair("http://main@[f3b3:b939:42d1:8ddb:495e:3572:f35b:e7d3]/search/blog/main/list?id=123#about", Uri("http", Authority("f3b3:b939:42d1:8ddb:495e:3572:f35b:e7d3", std::nullopt, "main", /* isHostIPLiteral= */ true), "/search/blog/main/list", "id=123", "about")),
            std::make_pair("http://often@131.219.134.164/list/wp-content?sort=asc&page=2", Uri("http", Authority("131.219.134.164", std::nullopt, "often"), "/list/wp-content", "sort=asc&page=2", std::nullopt)),
            std::make_pair("https://166.118.130.239:15790/explore/search/app/wp-content?beginner=brass&art=bone", Uri("https", Authority("166.118.130.239", "15790", std::nullopt), "/explore/search/app/wp-content", "beginner=brass&art=bone", std::nullopt)),
            std::make_pair("https://209.114.131.164:1701/explore/main?id=123#footer", Uri("https", Authority("209.114.131.164", "1701", std::nullopt), "/explore/main", "id=123", "footer")),
            std::make_pair("http://light@155.1.19.240/search/blog/main/list?id=123", Uri("http", Authority("155.1.19.240", std::nullopt, "light"), "/search/blog/main/list", "id=123", std::nullopt)),
            std::make_pair("https://59.183.22.179/tag/search/categories/app/list#contact", Uri("https", Authority("59.183.22.179", std::nullopt, std::nullopt), "/tag/search/categories/app/list", std::nullopt, "contact")),
            std::make_pair("http://determine@78.226.247.243/main/app?sort=asc&page=2#contact", Uri("http", Authority("78.226.247.243", std::nullopt, "determine"), "/main/app", "sort=asc&page=2", "contact")),
            std::make_pair("https://financial@107.75.63.4:50737/explore/tags/main/categories?search=query#section2", Uri("https", Authority("107.75.63.4", "50737", "financial"), "/explore/tags/main/categories", "search=query", "section2")),
            std::make_pair("http://seek@22.100.84.2/tag/posts/app/main/main", Uri("http", Authority("22.100.84.2", std::nullopt, "seek"), "/tag/posts/app/main/main", std::nullopt, std::nullopt)),
            std::make_pair("https://quality@5.44.71.109/blog/list/blog?id=123#home", Uri("https", Authority("5.44.71.109", std::nullopt, "quality"), "/blog/list/blog", "id=123", "home")),
            std::make_pair("http://16.11.12.9/tags/search?beginner=brass&art=bone", Uri("http", Authority("16.11.12.9", std::nullopt, std::nullopt), "/tags/search", "beginner=brass&art=bone", std::nullopt)),
            std::make_pair("http://learn@151.223.5.254:45610/wp-content", Uri("http", Authority("151.223.5.254", "45610", "learn"), "/wp-content", std::nullopt, std::nullopt)),
            std::make_pair("https://sense@219.187.200.4:17661/posts/list", Uri("https", Authority("219.187.200.4", "17661", "sense"), "/posts/list", std::nullopt, std::nullopt)),
            std::make_pair("https://[23ef:f0d5:11bf:a61c:74cb:9aad:c998:a590]/app/wp-content/app?sort=asc&page=2", Uri("https", Authority("23ef:f0d5:11bf:a61c:74cb:9aad:c998:a590", std::nullopt, std::nullopt, /* isHostIPLiteral= */ true), "/app/wp-content/app", "sort=asc&page=2", std::nullopt)),
            std::make_pair("http://168.37.253.220:329/explore#footer", Uri("http", Authority("168.37.253.220", "329", std::nullopt), "/explore", std::nullopt, "footer")),
            std::make_pair("https://179.110.255.252/wp-content/app?sort=asc&page=2", Uri("https", Authority("179.110.255.252", std::nullopt, std::nullopt), "/wp-content/app", "sort=asc&page=2", std::nullopt)),
            std::make_pair("https://[7485:630b:1701:2df2:d96c:f74d:c9f8:19bb]/posts/app/categories/wp-content#home", Uri("https", Authority("7485:630b:1701:2df2:d96c:f74d:c9f8:19bb", std::nullopt, std::nullopt, /* isHostIPLiteral= */ true), "/posts/app/categories/wp-content", std::nullopt, "home")),
            std::make_pair("https://116.200.139.220:42643/tag/wp-content/main#section1", Uri("https", Authority("116.200.139.220", "42643", std::nullopt), "/tag/wp-content/main", std::nullopt, "section1")),
            std::make_pair("https://23.1.106.5:46381/blog/category/app/blog/posts?search=query#home", Uri("https", Authority("23.1.106.5", "46381", std::nullopt), "/blog/category/app/blog/posts", "search=query", "home")),
            std::make_pair("https://mason.thompson.info/explore/explore", Uri("https", Authority("mason.thompson.info", std::nullopt, std::nullopt), "/explore/explore", std::nullopt, std::nullopt)),
            std::make_pair("http://if@100.160.210.120/search#about", Uri("http", Authority("100.160.210.120", std::nullopt, "if"), "/search", std::nullopt, "about")),
            std::make_pair("http://hernandez-erickson.biz/categories/wp-content", Uri("http", Authority("hernandez-erickson.biz", std::nullopt, std::nullopt), "/categories/wp-content", std::nullopt, std::nullopt)),
            std::make_pair("https://hernandez-woods.moore.johnson.com/main/explore/explore/wp-content/tags?search=query#contact", Uri("https", Authority("hernandez-woods.moore.johnson.com", std::nullopt, std::nullopt), "/main/explore/explore/wp-content/tags", "search=query", "contact")),
            std::make_pair("https://team@[ff7e:394b:a8fd:5f2a:af43:ca7e:eaea:9220]/search/category/tags?beginner=brass&art=bone", Uri("https", Authority("ff7e:394b:a8fd:5f2a:af43:ca7e:eaea:9220", std::nullopt, "team", /* isHostIPLiteral= */ true), "/search/category/tags", "beginner=brass&art=bone", std::nullopt)),
            std::make_pair("https://12.150.26.161:63604/categories?name=test#section2", Uri("https", Authority("12.150.26.161", "63604", std::nullopt), "/categories", "name=test", "section2")),
            std::make_pair("http://[9f31:702b:4451:a01d:8f7f:87c:51d5:b9fb]/posts/blog/blog/posts#footer", Uri("http", Authority("9f31:702b:4451:a01d:8f7f:87c:51d5:b9fb", std::nullopt, std::nullopt, /* isHostIPLiteral= */ true), "/posts/blog/blog/posts", std::nullopt, "footer")),
            std::make_pair("https://also@[2adb:2cbd:a4ca:4a7c:b689:1914:6dba:8576]/categories#contact", Uri("https", Authority("2adb:2cbd:a4ca:4a7c:b689:1914:6dba:8576", std::nullopt, "also", /* isHostIPLiteral= */ true), "/categories", std::nullopt, "contact")),
            std::make_pair("http://jones.blackwell.arnold.com/list/tags/category/app/app", Uri("http", Authority("jones.blackwell.arnold.com", std::nullopt, std::nullopt), "/list/tags/category/app/app", std::nullopt, std::nullopt)),
            std::make_pair("https://wind@martin.net/app?search=query#contact", Uri("https", Authority("martin.net", std::nullopt, "wind"), "/app", "search=query", "contact")),
            std::make_pair("http://patterson-maldonado.smith.king.com/tag/blog/main?filter=active#section1", Uri("http", Authority("patterson-maldonado.smith.king.com", std::nullopt, std::nullopt), "/tag/blog/main", "filter=active", "section1")),
            std::make_pair("http://ball@151.62.254.243:25743/app/app/wp-content/wp-content/search?beginner=brass&art=bone", Uri("http", Authority("151.62.254.243", "25743", "ball"), "/app/app/wp-content/wp-content/search", "beginner=brass&art=bone", std::nullopt)),
            std::make_pair("https://begin@rodriguez.com/blog/main/search", Uri("https", Authority("rodriguez.com", std::nullopt, "begin"), "/blog/main/search", std::nullopt, std::nullopt)),
            std::make_pair("https://stuart.org/list/categories#section1", Uri("https", Authority("stuart.org", std::nullopt, std::nullopt), "/list/categories", std::nullopt, "section1")),
            std::make_pair("http://gun@190.103.217.207/posts/list", Uri("http", Authority("190.103.217.207", std::nullopt, "gun"), "/posts/list", std::nullopt, std::nullopt)),
            std::make_pair("http://attorney@62.238.186.134/tag/blog/main", Uri("http", Authority("62.238.186.134", std::nullopt, "attorney"), "/tag/blog/main", std::nullopt, std::nullopt)),

            std::make_pair("/main?beginner=brass&art=bone", Uri(std::nullopt, std::nullopt, "/main", "beginner=brass&art=bone", std::nullopt)),
            std::make_pair("/search/blog/posts?filter=active#home", Uri(std::nullopt, std::nullopt, "/search/blog/posts", "filter=active", "home")),
            std::make_pair("/main/categories/blog/wp-content/categories", Uri(std::nullopt, std::nullopt, "/main/categories/blog/wp-content/categories", std::nullopt, std::nullopt)),
            std::make_pair("/app/wp-content", Uri(std::nullopt, std::nullopt, "/app/wp-content", std::nullopt, std::nullopt)),
            std::make_pair("/search/main/list", Uri(std::nullopt, std::nullopt, "/search/main/list", std::nullopt, std::nullopt)),
            std::make_pair("/search/wp-content?filter=active#home", Uri(std::nullopt, std::nullopt, "/search/wp-content", "filter=active", "home")),
            std::make_pair("/posts/tags/categories/categories", Uri(std::nullopt, std::nullopt, "/posts/tags/categories/categories", std::nullopt, std::nullopt)),
            std::make_pair("/list/tags/explore/tag#about", Uri(std::nullopt, std::nullopt, "/list/tags/explore/tag", std::nullopt, "about")),
            std::make_pair("/app#home", Uri(std::nullopt, std::nullopt, "/app", std::nullopt, "home")),
            std::make_pair("/posts/tag/categories?search=query#section2", Uri(std::nullopt, std::nullopt, "/posts/tag/categories", "search=query", "section2")),
            std::make_pair("/app/main/wp-content/main", Uri(std::nullopt, std::nullopt, "/app/main/wp-content/main", std::nullopt, std::nullopt)),
            std::make_pair("/list/main", Uri(std::nullopt, std::nullopt, "/list/main", std::nullopt, std::nullopt)),
            std::make_pair("/explore?name=test", Uri(std::nullopt, std::nullopt, "/explore", "name=test", std::nullopt)),
            std::make_pair("/categories/tag/explore/tags/explore?id=123", Uri(std::nullopt, std::nullopt, "/categories/tag/explore/tags/explore", "id=123", std::nullopt)),
            std::make_pair("/posts/tag/app/search#contact", Uri(std::nullopt, std::nullopt, "/posts/tag/app/search", std::nullopt, "contact"))
        )
);

TEST_P(UriTestingFixture, TestThatH16ParsingIsCorrect) {
    const auto& pair = GetParam();

    const auto& input = pair.first;
    const auto& expected_uri = pair.second;

    const auto& actual_uri = Uri::parse(input);
    EXPECT_EQ(actual_uri.value(), expected_uri);
}
