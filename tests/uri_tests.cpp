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
    Uri a("https", Authority("localhost", "80"), "/path");
    Uri b("ftp", Authority("localhost", "80"), "/path");
    EXPECT_NE(a, b);
}

using TestPayload = std::pair<std::string, Uri>;
class UriTestingFixture: public ::testing::TestWithParam<TestPayload> {};

INSTANTIATE_TEST_SUITE_P(
        UriParsingTests,
        UriTestingFixture,
        ::testing::Values(
            std::make_pair("https://able@218.110.62.47/explore?q=keyword#section1", Uri("https", Authority("able", "218.110.62.47", std::nullopt), "/explore", "q=keyword", "section1")),
            std::make_pair("http://couple@104.27.227.174:27422/wp-content?name=test", Uri("http", Authority("couple", "104.27.227.174", "27422"), "/wp-content", "name=test", std::nullopt)),
            std::make_pair("http://production@186.149.105.224:49784/explore/main/categories", Uri("http", Authority("production", "186.149.105.224", "49784"), "/explore/main/categories", std::nullopt, std::nullopt)),
            std::make_pair("https://appear@52.189.27.178/categories/list/wp-content/posts#about", Uri("https", Authority("appear", "52.189.27.178", std::nullopt), "/categories/list/wp-content/posts", std::nullopt, "about")),
            std::make_pair("http://often@[8c81:6c4f:3355:aea1:e2e7:22ba:ecf0:b427]/wp-content/tag?q=keyword#home", Uri("http", Authority("often", "8c81:6c4f:3355:aea1:e2e7:22ba:ecf0:b427", std::nullopt), "/wp-content/tag", "q=keyword", "home")),
            std::make_pair("http://97.115.225.46/wp-content/categories?search=query", Uri("http", Authority(std::nullopt, "97.115.225.46", std::nullopt), "/wp-content/categories", "search=query", std::nullopt)),
            std::make_pair("https://124.49.252.8:60271/categories/category/search/categories/category?filter=active", Uri("https", Authority(std::nullopt, "124.49.252.8", "60271"), "/categories/category/search/categories/category", "filter=active", std::nullopt)),
            std::make_pair("https://one@[b0c0:38d4:4c13:8570:9a6d:f1b1:8fc6:131e]/main", Uri("https", Authority("one", "b0c0:38d4:4c13:8570:9a6d:f1b1:8fc6:131e", std::nullopt), "/main", std::nullopt, std::nullopt)),
            std::make_pair("https://brown.lawrence-king.murray.info/blog/main/explore/list", Uri("https", Authority(std::nullopt, "brown.lawrence-king.murray.info", std::nullopt), "/blog/main/explore/list", std::nullopt, std::nullopt)),
            std::make_pair("https://greene.com/categories/category/search/categories/category?filter=active", Uri("https", Authority(std::nullopt, "greene.com", std::nullopt), "/categories/category/search/categories/category", "filter=active", std::nullopt)),
            std::make_pair("http://powell.herrera.lambert.info/tags/posts/categories#about", Uri("http", Authority(std::nullopt, "powell.herrera.lambert.info", std::nullopt), "/tags/posts/categories", std::nullopt, "about")),
            std::make_pair("https://12.150.26.161:63604/app/tags?filter=active", Uri("https", Authority(std::nullopt, "12.150.26.161", "63604"), "/app/tags", "filter=active", std::nullopt)),
            std::make_pair("http://along@[96c:25be:5333:60f2:5f45:e431:a55e:417c]/tags/explore/tags", Uri("http", Authority("along", "96c:25be:5333:60f2:5f45:e431:a55e:417c", std::nullopt), "/tags/explore/tags", std::nullopt, std::nullopt)),
            std::make_pair("https://hardy.torres.diaz.com/category/tag/explore/category?beginner=brass&art=bone", Uri("https", Authority(std::nullopt, "hardy.torres.diaz.com", std::nullopt), "/category/tag/explore/category", "beginner=brass&art=bone", std::nullopt)),
            std::make_pair("http://cisneros.solomon-wallace.calderon.com/posts/posts?id=123", Uri("http", Authority(std::nullopt, "cisneros.solomon-wallace.calderon.com", std::nullopt), "/posts/posts", "id=123", std::nullopt)),
            std::make_pair("http://main@[f3b3:b939:42d1:8ddb:495e:3572:f35b:e7d3]/search/blog/main/list?id=123#about", Uri("http", Authority("main", "f3b3:b939:42d1:8ddb:495e:3572:f35b:e7d3", std::nullopt), "/search/blog/main/list", "id=123", "about")),
            std::make_pair("http://often@131.219.134.164/list/wp-content?sort=asc&page=2", Uri("http", Authority("often", "131.219.134.164", std::nullopt), "/list/wp-content", "sort=asc&page=2", std::nullopt)),
            std::make_pair("https://166.118.130.239:15790/explore/search/app/wp-content?beginner=brass&art=bone", Uri("https", Authority(std::nullopt, "166.118.130.239", "15790"), "/explore/search/app/wp-content", "beginner=brass&art=bone", std::nullopt)),
            std::make_pair("https://209.114.131.164:1701/explore/main?id=123#footer", Uri("https", Authority(std::nullopt, "209.114.131.164", "1701"), "/explore/main", "id=123", "footer")),
            std::make_pair("http://light@155.1.19.240/search/blog/main/list?id=123", Uri("http", Authority("light", "155.1.19.240", std::nullopt), "/search/blog/main/list", "id=123", std::nullopt)),
            std::make_pair("https://59.183.22.179/tag/search/categories/app/list#contact", Uri("https", Authority(std::nullopt, "59.183.22.179", std::nullopt), "/tag/search/categories/app/list", std::nullopt, "contact")),
            std::make_pair("http://determine@78.226.247.243/main/app?sort=asc&page=2#contact", Uri("http", Authority("determine", "78.226.247.243", std::nullopt), "/main/app", "sort=asc&page=2", "contact")),
            std::make_pair("https://financial@107.75.63.4:50737/explore/tags/main/categories?search=query#section2", Uri("https", Authority("financial", "107.75.63.4", "50737"), "/explore/tags/main/categories", "search=query", "section2")),
            std::make_pair("http://seek@22.100.84.2/tag/posts/app/main/main", Uri("http", Authority("seek", "22.100.84.2", std::nullopt), "/tag/posts/app/main/main", std::nullopt, std::nullopt)),
            std::make_pair("https://quality@5.44.71.109/blog/list/blog?id=123#home", Uri("https", Authority("quality", "5.44.71.109", std::nullopt), "/blog/list/blog", "id=123", "home")),
            std::make_pair("http://16.11.12.9/tags/search?beginner=brass&art=bone", Uri("http", Authority(std::nullopt, "16.11.12.9", std::nullopt), "/tags/search", "beginner=brass&art=bone", std::nullopt)),
            std::make_pair("http://learn@151.223.5.254:45610/wp-content", Uri("http", Authority("learn", "151.223.5.254", "45610"), "/wp-content", std::nullopt, std::nullopt)),
            std::make_pair("https://sense@219.187.200.4:17661/posts/list", Uri("https", Authority("sense", "219.187.200.4", "17661"), "/posts/list", std::nullopt, std::nullopt)),
            std::make_pair("https://[23ef:f0d5:11bf:a61c:74cb:9aad:c998:a590]/app/wp-content/app?sort=asc&page=2", Uri("https", Authority(std::nullopt, "23ef:f0d5:11bf:a61c:74cb:9aad:c998:a590", std::nullopt), "/app/wp-content/app", "sort=asc&page=2", std::nullopt)),
            std::make_pair("http://168.37.253.220:329/explore#footer", Uri("http", Authority(std::nullopt, "168.37.253.220", "329"), "/explore", std::nullopt, "footer")),
            std::make_pair("https://179.110.255.252/wp-content/app?sort=asc&page=2", Uri("https", Authority(std::nullopt, "179.110.255.252", std::nullopt), "/wp-content/app", "sort=asc&page=2", std::nullopt)),
            std::make_pair("https://[7485:630b:1701:2df2:d96c:f74d:c9f8:19bb]/posts/app/categories/wp-content#home", Uri("https", Authority(std::nullopt, "7485:630b:1701:2df2:d96c:f74d:c9f8:19bb", std::nullopt), "/posts/app/categories/wp-content", std::nullopt, "home")),
            std::make_pair("https://116.200.139.220:42643/tag/wp-content/main#section1", Uri("https", Authority(std::nullopt, "116.200.139.220", "42643"), "/tag/wp-content/main", std::nullopt, "section1")),
            std::make_pair("https://23.1.106.5:46381/blog/category/app/blog/posts?search=query#home", Uri("https", Authority(std::nullopt, "23.1.106.5", "46381"), "/blog/category/app/blog/posts", "search=query", "home")),
            std::make_pair("https://mason.thompson.info/explore/explore", Uri("https", Authority(std::nullopt, "mason.thompson.info", std::nullopt), "/explore/explore", std::nullopt, std::nullopt)),
            std::make_pair("http://if@100.160.210.120/search#about", Uri("http", Authority("if", "100.160.210.120", std::nullopt), "/search", std::nullopt, "about")),
            std::make_pair("http://hernandez-erickson.biz/categories/wp-content", Uri("http", Authority(std::nullopt, "hernandez-erickson.biz", std::nullopt), "/categories/wp-content", std::nullopt, std::nullopt)),
            std::make_pair("https://hernandez-woods.moore.johnson.com/main/explore/explore/wp-content/tags?search=query#contact", Uri("https", Authority(std::nullopt, "hernandez-woods.moore.johnson.com", std::nullopt), "/main/explore/explore/wp-content/tags", "search=query", "contact")),
            std::make_pair("https://team@[ff7e:394b:a8fd:5f2a:af43:ca7e:eaea:9220]/search/category/tags?beginner=brass&art=bone", Uri("https", Authority("team", "ff7e:394b:a8fd:5f2a:af43:ca7e:eaea:9220", std::nullopt), "/search/category/tags", "beginner=brass&art=bone", std::nullopt)),
            std::make_pair("https://12.150.26.161:63604/categories?name=test#section2", Uri("https", Authority(std::nullopt, "12.150.26.161", "63604"), "/categories", "name=test", "section2")),
            std::make_pair("http://[9f31:702b:4451:a01d:8f7f:87c:51d5:b9fb]/posts/blog/blog/posts#footer", Uri("http", Authority(std::nullopt, "9f31:702b:4451:a01d:8f7f:87c:51d5:b9fb", std::nullopt), "/posts/blog/blog/posts", std::nullopt, "footer")),
            std::make_pair("https://also@[2adb:2cbd:a4ca:4a7c:b689:1914:6dba:8576]/categories#contact", Uri("https", Authority("also", "2adb:2cbd:a4ca:4a7c:b689:1914:6dba:8576", std::nullopt), "/categories", std::nullopt, "contact")),
            std::make_pair("http://jones.blackwell.arnold.com/list/tags/category/app/app", Uri("http", Authority(std::nullopt, "jones.blackwell.arnold.com", std::nullopt), "/list/tags/category/app/app", std::nullopt, std::nullopt)),
            std::make_pair("https://wind@martin.net/app?search=query#contact", Uri("https", Authority("wind", "martin.net", std::nullopt), "/app", "search=query", "contact")),
            std::make_pair("http://patterson-maldonado.smith.king.com/tag/blog/main?filter=active#section1", Uri("http", Authority(std::nullopt, "patterson-maldonado.smith.king.com", std::nullopt), "/tag/blog/main", "filter=active", "section1")),
            std::make_pair("http://ball@151.62.254.243:25743/app/app/wp-content/wp-content/search?beginner=brass&art=bone", Uri("http", Authority("ball", "151.62.254.243", "25743"), "/app/app/wp-content/wp-content/search", "beginner=brass&art=bone", std::nullopt)),
            std::make_pair("https://begin@rodriguez.com/blog/main/search", Uri("https", Authority("begin", "rodriguez.com", std::nullopt), "/blog/main/search", std::nullopt, std::nullopt)),
            std::make_pair("https://stuart.org/list/categories#section1", Uri("https", Authority(std::nullopt, "stuart.org", std::nullopt), "/list/categories", std::nullopt, "section1")),
            std::make_pair("http://gun@190.103.217.207/posts/list", Uri("http", Authority("gun", "190.103.217.207", std::nullopt), "/posts/list", std::nullopt, std::nullopt)),
            std::make_pair("http://attorney@62.238.186.134/tag/blog/main", Uri("http", Authority("attorney", "62.238.186.134", std::nullopt), "/tag/blog/main", std::nullopt, std::nullopt)),

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

    EXPECT_EQ(Uri::parse(input).value(), expected_uri);
}
