#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"
#include "utils/parser_test_utils.h"

using UriTestPayload = tests::UriTestPayload;

class UriParserUriTestingFixture: public ::testing::TestWithParam<UriTestPayload> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserUriTests,
        UriParserUriTestingFixture,
        ::testing::Values(
            UriTestPayload::error(""),
            UriTestPayload::error(":"),
            UriTestPayload::error(":website.com?q=5"),
            UriTestPayload::error("localhost"),

            UriTestPayload::success("https://29.207.245.29:14523/search/search/blog")
                .expectScheme("https")
                .expectHost("29.207.245.29", uri::__internal::HostType::kIPv4)
                .expectPort("14523")
                .expectPath("/search/search/blog"),

            UriTestPayload::success("https://51.117.140.166:834/wp-content/search/posts/list")
                .expectScheme("https")
                .expectHost("51.117.140.166", uri::__internal::HostType::kIPv4)
                .expectPort("834")
                .expectPath("/wp-content/search/posts/list"),

            UriTestPayload::success("https://207.186.106.171:17186/category/app?search=query")
                .expectScheme("https")
                .expectHost("207.186.106.171", uri::__internal::HostType::kIPv4)
                .expectPort("17186")
                .expectPath("/category/app")
                .expectQuery("search=query"),

            UriTestPayload::success("https://[c303:b8a0:8a17:f9d7:889e:1de1:b2d5:e01b]/list/search/tags#footer")
                .expectScheme("https")
                .expectHost("c303:b8a0:8a17:f9d7:889e:1de1:b2d5:e01b", uri::__internal::HostType::kIPLiteral)
                .expectPath("/list/search/tags")
                .expectFragment("footer"),

            UriTestPayload::success("http://132.134.156.17/tags/list/categories?name=test")
                .expectScheme("http")
                .expectHost("132.134.156.17", uri::__internal::HostType::kIPv4)
                .expectPath("/tags/list/categories")
                .expectQuery("name=test"),

            UriTestPayload::success("http://51.53.53.0/tags/posts/wp-content/app?id=123")
                .expectScheme("http")
                .expectHost("51.53.53.0", uri::__internal::HostType::kIPv4)
                .expectPath("/tags/posts/wp-content/app")
                .expectQuery("id=123"),

            UriTestPayload::success("http://douglas.flores-whitaker.richardson.com/app/posts?filter=active#section2")
                .expectScheme("http")
                .expectHost("douglas.flores-whitaker.richardson.com")
                .expectPath("/app/posts")
                .expectQuery("filter=active")
                .expectFragment("section2"),

            UriTestPayload::success("http://melendez.roberts-weaver.org/tags/main?id=123#section2")
                .expectScheme("http")
                .expectHost("melendez.roberts-weaver.org")
                .expectPath("/tags/main")
                .expectQuery("id=123")
                .expectFragment("section2"),

            UriTestPayload::success("http://65.56.186.121/explore")
                .expectScheme("http")
                .expectHost("65.56.186.121", uri::__internal::HostType::kIPv4)
                .expectPath("/explore"),

            UriTestPayload::success("http://207.249.221.157/categories/blog/search?filter=active#about")
                .expectScheme("http")
                .expectHost("207.249.221.157", uri::__internal::HostType::kIPv4)
                .expectPath("/categories/blog/search")
                .expectQuery("filter=active")
                .expectFragment("about"),

            UriTestPayload::success("http://2.40.215.163/main")
                .expectScheme("http")
                .expectHost("2.40.215.163", uri::__internal::HostType::kIPv4)
                .expectPath("/main"),

            UriTestPayload::success("https://young-fitzpatrick.martin-scott.com/tags?search=query")
                .expectScheme("https")
                .expectHost("young-fitzpatrick.martin-scott.com")
                .expectPath("/tags")
                .expectQuery("search=query"),

            UriTestPayload::success("http://mckinney-miller.biz/main/tags/category/explore#contact")
                .expectScheme("http")
                .expectHost("mckinney-miller.biz")
                .expectPath("/main/tags/category/explore")
                .expectFragment("contact"),

            UriTestPayload::success("http://54.125.110.75/search/wp-content/search/list?id=123")
                .expectScheme("http")
                .expectHost("54.125.110.75", uri::__internal::HostType::kIPv4)
                .expectPath("/search/wp-content/search/list")
                .expectQuery("id=123"),

            UriTestPayload::success("https://[6d47:9f20:6d24:3b85:f393:62d4:6753:4fd5]/explore/blog")
                .expectScheme("https")
                .expectHost("6d47:9f20:6d24:3b85:f393:62d4:6753:4fd5", uri::__internal::HostType::kIPLiteral)
                .expectPath("/explore/blog"),

            UriTestPayload::success("http://[5bc6:7a4a:ee68:64be:4331:f0f2:f6ef:c81d]/category/blog/categories/categories")
                .expectScheme("http")
                .expectHost("5bc6:7a4a:ee68:64be:4331:f0f2:f6ef:c81d", uri::__internal::HostType::kIPLiteral)
                .expectPath("/category/blog/categories/categories"),

            UriTestPayload::success("http://104.118.236.176/category?id=123#section1")
                .expectScheme("http")
                .expectHost("104.118.236.176", uri::__internal::HostType::kIPv4)
                .expectPath("/category")
                .expectQuery("id=123")
                .expectFragment("section1"),

            UriTestPayload::success("https://walls.davis.com/app/tags/search/explore/wp-content")
                .expectScheme("https")
                .expectHost("walls.davis.com")
                .expectPath("/app/tags/search/explore/wp-content"),

            UriTestPayload::success("https://30.167.52.247/posts?search=query")
                .expectScheme("https")
                .expectHost("30.167.52.247", uri::__internal::HostType::kIPv4)
                .expectPath("/posts")
                .expectQuery("search=query"),

            UriTestPayload::success("http://[c303:b8a0:8a17:f9d7:889e:1de1:b2d5:e01b]/app/posts#section2")
                .expectScheme("http")
                .expectHost("c303:b8a0:8a17:f9d7:889e:1de1:b2d5:e01b", uri::__internal::HostType::kIPLiteral)
                .expectPath("/app/posts")
                .expectFragment("section2"),

            UriTestPayload::success("http://44.29.125.56/app/blog#about")
                .expectScheme("http")
                .expectHost("44.29.125.56", uri::__internal::HostType::kIPv4)
                .expectPath("/app/blog")
                .expectFragment("about"),

            UriTestPayload::success("https://1.72.11.45:45663/blog/posts/tags/category")
                .expectScheme("https")
                .expectHost("1.72.11.45", uri::__internal::HostType::kIPv4)
                .expectPort("45663")
                .expectPath("/blog/posts/tags/category"),

            UriTestPayload::success("http://[2380:dd0b:e6fc:a9c2:f16e:fb50:f37d:bb81]/explore/main/main/tag#section1")
                .expectScheme("http")
                .expectHost("2380:dd0b:e6fc:a9c2:f16e:fb50:f37d:bb81", uri::__internal::HostType::kIPLiteral)
                .expectPath("/explore/main/main/tag")
                .expectFragment("section1"),

            UriTestPayload::success("https://reid.com/wp-content/blog/tags/posts/main#section2")
                .expectScheme("https")
                .expectHost("reid.com")
                .expectPath("/wp-content/blog/tags/posts/main")
                .expectFragment("section2"),

            UriTestPayload::success("http://28.202.39.174/tag/explore/explore/main/blog")
                .expectScheme("http")
                .expectHost("28.202.39.174", uri::__internal::HostType::kIPv4)
                .expectPath("/tag/explore/explore/main/blog"),

            UriTestPayload::success("https://128.12.90.183:22020/wp-content/categories/blog/categories/posts?sort=asc&page=2#home")
                .expectScheme("https")
                .expectHost("128.12.90.183", uri::__internal::HostType::kIPv4)
                .expectPort("22020")
                .expectPath("/wp-content/categories/blog/categories/posts")
                .expectQuery("sort=asc&page=2")
                .expectFragment("home"),

            UriTestPayload::success("http://burgess-gentry.lopez-bennett.com/posts/tags/categories?q=keyword#footer")
                .expectScheme("http")
                .expectHost("burgess-gentry.lopez-bennett.com")
                .expectPath("/posts/tags/categories")
                .expectQuery("q=keyword")
                .expectFragment("footer"),

            UriTestPayload::success("http://[8c66:ddc9:712b:404:ec9a:c12f:ffd7:d174]/app/posts?search=query")
                .expectScheme("http")
                .expectHost("8c66:ddc9:712b:404:ec9a:c12f:ffd7:d174", uri::__internal::HostType::kIPLiteral)
                .expectPath("/app/posts")
                .expectQuery("search=query"),

            UriTestPayload::success("https://116.255.113.200/search/search/app/main/search?name=test#section2")
                .expectScheme("https")
                .expectHost("116.255.113.200", uri::__internal::HostType::kIPv4)
                .expectPath("/search/search/app/main/search")
                .expectQuery("name=test")
                .expectFragment("section2"),

            UriTestPayload::success("https://107.11.193.13:46118/main/posts/category")
                .expectScheme("https")
                .expectHost("107.11.193.13", uri::__internal::HostType::kIPv4)
                .expectPort("46118")
                .expectPath("/main/posts/category"),

            UriTestPayload::success("https://[6750:7422:1208:8a02:90aa:368f:fb16:f40b]/tags/blog")
                .expectScheme("https")
                .expectHost("6750:7422:1208:8a02:90aa:368f:fb16:f40b", uri::__internal::HostType::kIPLiteral)
                .expectPath("/tags/blog"),

            UriTestPayload::success("https://107.11.193.13:46118/posts/search/list/blog?name=test")
                .expectScheme("https")
                .expectHost("107.11.193.13", uri::__internal::HostType::kIPv4)
                .expectPort("46118")
                .expectPath("/posts/search/list/blog")
                .expectQuery("name=test"),

            UriTestPayload::success("https://22.143.166.143:2609/explore/wp-content/app/search?sort=asc&page=2")
                .expectScheme("https")
                .expectHost("22.143.166.143", uri::__internal::HostType::kIPv4)
                .expectPort("2609")
                .expectPath("/explore/wp-content/app/search")
                .expectQuery("sort=asc&page=2"),

            UriTestPayload::success("http://14.153.50.131/tags/list/posts/main/tags")
                .expectScheme("http")
                .expectHost("14.153.50.131", uri::__internal::HostType::kIPv4)
                .expectPath("/tags/list/posts/main/tags"),

            UriTestPayload::success("https://12.205.108.85:45021/tags/category/category/list?q=keyword#section1")
                .expectScheme("https")
                .expectHost("12.205.108.85", uri::__internal::HostType::kIPv4)
                .expectPort("45021")
                .expectPath("/tags/category/category/list")
                .expectQuery("q=keyword")
                .expectFragment("section1"),

            UriTestPayload::success("https://79.192.141.47:5060/blog#home")
                .expectScheme("https")
                .expectHost("79.192.141.47", uri::__internal::HostType::kIPv4)
                .expectPort("5060")
                .expectPath("/blog")
                .expectFragment("home"),

            UriTestPayload::success("https://84.11.92.98:11399/category?sort=asc&page=2")
                .expectScheme("https")
                .expectHost("84.11.92.98", uri::__internal::HostType::kIPv4)
                .expectPort("11399")
                .expectPath("/category")
                .expectQuery("sort=asc&page=2"),

            UriTestPayload::success("https://42.206.127.28:696/list/category/list/blog#about")
                .expectScheme("https")
                .expectHost("42.206.127.28", uri::__internal::HostType::kIPv4)
                .expectPort("696")
                .expectPath("/list/category/list/blog")
                .expectFragment("about"),

            UriTestPayload::success("http://131.24.193.86:50052/list/category")
                .expectScheme("http")
                .expectHost("131.24.193.86", uri::__internal::HostType::kIPv4)
                .expectPort("50052")
                .expectPath("/list/category"),

            UriTestPayload::success("https://williams-bradley.haynes.info/explore/app/tag?search=query#home")
                .expectScheme("https")
                .expectHost("williams-bradley.haynes.info")
                .expectPath("/explore/app/tag")
                .expectQuery("search=query")
                .expectFragment("home"),

            UriTestPayload::success("http://154.100.192.120/blog#footer")
                .expectScheme("http")
                .expectHost("154.100.192.120", uri::__internal::HostType::kIPv4)
                .expectPath("/blog")
                .expectFragment("footer"),

            UriTestPayload::success("http://johnson-lopez.henry.com/wp-content/app#section2")
                .expectScheme("http")
                .expectHost("johnson-lopez.henry.com")
                .expectPath("/wp-content/app")
                .expectFragment("section2"),

            UriTestPayload::success("https://119.87.39.107:23306/main#about")
                .expectScheme("https")
                .expectHost("119.87.39.107", uri::__internal::HostType::kIPv4)
                .expectPort("23306")
                .expectPath("/main")
                .expectFragment("about"),

            UriTestPayload::success("http://[3cae:94be:ae5a:4b85:22e2:edfd:e140:731a]/tags/tags/list/tag/category?sort=asc&page=2#home")
                .expectScheme("http")
                .expectHost("3cae:94be:ae5a:4b85:22e2:edfd:e140:731a", uri::__internal::HostType::kIPLiteral)
                .expectPath("/tags/tags/list/tag/category")
                .expectQuery("sort=asc&page=2")
                .expectFragment("home"),

            UriTestPayload::success("http://85.240.90.52/wp-content/wp-content/tag/app?name=test")
                .expectScheme("http")
                .expectHost("85.240.90.52", uri::__internal::HostType::kIPv4)
                .expectPath("/wp-content/wp-content/tag/app")
                .expectQuery("name=test"),

            UriTestPayload::success("http://melendez.roberts-weaver.org/main/list/blog#about")
                .expectScheme("http")
                .expectHost("melendez.roberts-weaver.org")
                .expectPath("/main/list/blog")
                .expectFragment("about"),

            UriTestPayload::success("http://[2545:5b5c:638a:5e18:4e06:bba3:395a:9719]/main/tags/category/explore?id=123")
                .expectScheme("http")
                .expectHost("2545:5b5c:638a:5e18:4e06:bba3:395a:9719", uri::__internal::HostType::kIPLiteral)
                .expectPath("/main/tags/category/explore")
                .expectQuery("id=123"),

            UriTestPayload::success("http://150.244.161.202:56832/tags/posts/wp-content/app?id=123#about")
                .expectScheme("http")
                .expectHost("150.244.161.202", uri::__internal::HostType::kIPv4)
                .expectPort("56832")
                .expectPath("/tags/posts/wp-content/app")
                .expectQuery("id=123")
                .expectFragment("about"),

            UriTestPayload::success("https://143.6.202.72:38240/explore#contact")
                .expectScheme("https")
                .expectHost("143.6.202.72", uri::__internal::HostType::kIPv4)
                .expectPort("38240")
                .expectPath("/explore")
                .expectFragment("contact"),

            UriTestPayload::success("https://80.131.192.95/tags/list/posts/main/tags")
                .expectScheme("https")
                .expectHost("80.131.192.95", uri::__internal::HostType::kIPv4)
                .expectPath("/tags/list/posts/main/tags"),

            UriTestPayload::success("https://85.118.106.26/category/tags")
                .expectScheme("https")
                .expectHost("85.118.106.26", uri::__internal::HostType::kIPv4)
                .expectPath("/category/tags"),

            UriTestPayload::success("https://[1622:658a:5ae8:ece5:3f45:302c:33a0:8e4a]/category/explore/tags/wp-content#section2")
                .expectScheme("https")
                .expectHost("1622:658a:5ae8:ece5:3f45:302c:33a0:8e4a", uri::__internal::HostType::kIPLiteral)
                .expectPath("/category/explore/tags/wp-content")
                .expectFragment("section2"),

            UriTestPayload::success("https://29.207.245.29:14523/tag#section2")
                .expectScheme("https")
                .expectHost("29.207.245.29", uri::__internal::HostType::kIPv4)
                .expectPort("14523")
                .expectPath("/tag")
                .expectFragment("section2"),

            UriTestPayload::success("http://[23b5:726c:52a4:5c7c:ebfc:1459:6dfa:ab88]/main/category/posts/category?name=test")
                .expectScheme("http")
                .expectHost("23b5:726c:52a4:5c7c:ebfc:1459:6dfa:ab88", uri::__internal::HostType::kIPLiteral)
                .expectPath("/main/category/posts/category")
                .expectQuery("name=test"),

            UriTestPayload::success("https://[7648:648:fec7:dd8:2cc3:906a:7b71:a1d3]/search/tags/tags/tags/main")
                .expectScheme("https")
                .expectHost("7648:648:fec7:dd8:2cc3:906a:7b71:a1d3", uri::__internal::HostType::kIPLiteral)
                .expectPath("/search/tags/tags/tags/main"),

            UriTestPayload::success("https://boyd-diaz.white.net/posts/search/list/blog")
                .expectScheme("https")
                .expectHost("boyd-diaz.white.net")
                .expectPath("/posts/search/list/blog"),

            UriTestPayload::success("https://213.80.129.61:9232/posts/wp-content#section2")
                .expectScheme("https")
                .expectHost("213.80.129.61", uri::__internal::HostType::kIPv4)
                .expectPort("9232")
                .expectPath("/posts/wp-content")
                .expectFragment("section2"),

            UriTestPayload::success("http://marquez.sellers.moore-case.com/categories/main#about")
                .expectScheme("http")
                .expectHost("marquez.sellers.moore-case.com")
                .expectPath("/categories/main")
                .expectFragment("about"),

            UriTestPayload::success("http://36.235.130.35/tags/main?q=keyword#section1")
                .expectScheme("http")
                .expectHost("36.235.130.35", uri::__internal::HostType::kIPv4)
                .expectPath("/tags/main")
                .expectQuery("q=keyword")
                .expectFragment("section1"),

            UriTestPayload::success("https://[663c:11d9:8ddb:e50d:c3da:8d9b:fd79:a6cb]/categories/app/categories/blog/tag?sort=asc&page=2#contact")
                .expectScheme("https")
                .expectHost("663c:11d9:8ddb:e50d:c3da:8d9b:fd79:a6cb", uri::__internal::HostType::kIPLiteral)
                .expectPath("/categories/app/categories/blog/tag")
                .expectQuery("sort=asc&page=2")
                .expectFragment("contact"),

            UriTestPayload::success("http://26.88.68.48:2803/tags#contact")
                .expectScheme("http")
                .expectHost("26.88.68.48", uri::__internal::HostType::kIPv4)
                .expectPort("2803")
                .expectPath("/tags")
                .expectFragment("contact"),

            UriTestPayload::success("http://144.82.50.109/posts/search/posts/list#about")
                .expectScheme("http")
                .expectHost("144.82.50.109", uri::__internal::HostType::kIPv4)
                .expectPath("/posts/search/posts/list")
                .expectFragment("about"),

            UriTestPayload::success("https://[420f:62cd:adff:2a79:83ec:30fa:12ba:1a80]/list/list/blog/blog?name=test")
                .expectScheme("https")
                .expectHost("420f:62cd:adff:2a79:83ec:30fa:12ba:1a80", uri::__internal::HostType::kIPLiteral)
                .expectPath("/list/list/blog/blog")
                .expectQuery("name=test"),

            UriTestPayload::success("https://[4ed4:4e7b:8e35:a6e5:7edf:90e7:af26:5aae]/search/app/blog/wp-content?sort=asc&page=2")
                .expectScheme("https")
                .expectHost("4ed4:4e7b:8e35:a6e5:7edf:90e7:af26:5aae", uri::__internal::HostType::kIPLiteral)
                .expectPath("/search/app/blog/wp-content")
                .expectQuery("sort=asc&page=2"),

            UriTestPayload::success("https://115.240.252.125/main#footer")
                .expectScheme("https")
                .expectHost("115.240.252.125", uri::__internal::HostType::kIPv4)
                .expectPath("/main")
                .expectFragment("footer"),

            UriTestPayload::success("https://27.112.228.241/posts/posts/app#footer")
                .expectScheme("https")
                .expectHost("27.112.228.241", uri::__internal::HostType::kIPv4)
                .expectPath("/posts/posts/app")
                .expectFragment("footer"),

            UriTestPayload::success("https://henderson.houston.harding.com/category/app?sort=asc&page=2")
                .expectScheme("https")
                .expectHost("henderson.houston.harding.com")
                .expectPath("/category/app")
                .expectQuery("sort=asc&page=2"),

            UriTestPayload::success("https://[c2da:b97b:f1aa:8555:ae87:34bc:341a:8508]/app/tags/category#section2")
                .expectScheme("https")
                .expectHost("c2da:b97b:f1aa:8555:ae87:34bc:341a:8508", uri::__internal::HostType::kIPLiteral)
                .expectPath("/app/tags/category")
                .expectFragment("section2"),

            UriTestPayload::success("http://134.221.193.153:54434/main?name=test")
                .expectScheme("http")
                .expectHost("134.221.193.153", uri::__internal::HostType::kIPv4)
                .expectPort("54434")
                .expectPath("/main")
                .expectQuery("name=test"),

            UriTestPayload::success("https://finley-monroe.sanchez.brown-hanson.com/search/list/blog/category?sort=asc&page=2")
                .expectScheme("https")
                .expectHost("finley-monroe.sanchez.brown-hanson.com")
                .expectPath("/search/list/blog/category")
                .expectQuery("sort=asc&page=2"),

            UriTestPayload::success("http://154.38.94.137:15183/tag/main/wp-content")
                .expectScheme("http")
                .expectHost("154.38.94.137", uri::__internal::HostType::kIPv4)
                .expectPort("15183")
                .expectPath("/tag/main/wp-content"),

            UriTestPayload::success("http://[d73b:10f7:b1b9:ba80:423d:dcee:6e2e:48f3]/main")
                .expectScheme("http")
                .expectHost("d73b:10f7:b1b9:ba80:423d:dcee:6e2e:48f3", uri::__internal::HostType::kIPLiteral)
                .expectPath("/main"),

            UriTestPayload::success("https://mccarty-martinez.hernandez.com/tags/tag/app/tag/posts#about")
                .expectScheme("https")
                .expectHost("mccarty-martinez.hernandez.com")
                .expectPath("/tags/tag/app/tag/posts")
                .expectFragment("about"),

            UriTestPayload::success("https://[3a86:531b:4edc:45c4:86c:9c56:bcdf:b0f8]/wp-content/search/tags/blog/search?sort=asc&page=2")
                .expectScheme("https")
                .expectHost("3a86:531b:4edc:45c4:86c:9c56:bcdf:b0f8", uri::__internal::HostType::kIPLiteral)
                .expectPath("/wp-content/search/tags/blog/search")
                .expectQuery("sort=asc&page=2"),

            UriTestPayload::success("https://baker-bates.net/wp-content/app/tag/search/main#home")
                .expectScheme("https")
                .expectHost("baker-bates.net")
                .expectPath("/wp-content/app/tag/search/main")
                .expectFragment("home"),

            UriTestPayload::success("https://murray.net/categories/wp-content/explore/categories?search=query")
                .expectScheme("https")
                .expectHost("murray.net")
                .expectPath("/categories/wp-content/explore/categories")
                .expectQuery("search=query"),

            UriTestPayload::success("https://douglas.flores-whitaker.richardson.com/wp-content/posts/app?filter=active#about")
                .expectScheme("https")
                .expectHost("douglas.flores-whitaker.richardson.com")
                .expectPath("/wp-content/posts/app")
                .expectQuery("filter=active")
                .expectFragment("about"),

            UriTestPayload::success("https://[7261:eace:7c76:4805:ced2:52e:9589:426d]/explore?search=query")
                .expectScheme("https")
                .expectHost("7261:eace:7c76:4805:ced2:52e:9589:426d", uri::__internal::HostType::kIPLiteral)
                .expectPath("/explore")
                .expectQuery("search=query"),

            UriTestPayload::success("http://53.140.131.195:41658/categories/wp-content/explore/categories?filter=active#contact")
                .expectScheme("http")
                .expectHost("53.140.131.195", uri::__internal::HostType::kIPv4)
                .expectPort("41658")
                .expectPath("/categories/wp-content/explore/categories")
                .expectQuery("filter=active")
                .expectFragment("contact"),

            UriTestPayload::success("https://[838f:2bfc:bb5b:c589:1828:f6aa:ac4:bb48]/categories/main?name=test#section2")
                .expectScheme("https")
                .expectHost("838f:2bfc:bb5b:c589:1828:f6aa:ac4:bb48", uri::__internal::HostType::kIPLiteral)
                .expectPath("/categories/main")
                .expectQuery("name=test")
                .expectFragment("section2"),

            UriTestPayload::success("https://ortiz.com/tags/tags/list/tag/category?id=123#contact")
                .expectScheme("https")
                .expectHost("ortiz.com")
                .expectPath("/tags/tags/list/tag/category")
                .expectQuery("id=123")
                .expectFragment("contact"),

            UriTestPayload::success("https://158.140.11.179:24791/list")
                .expectScheme("https")
                .expectHost("158.140.11.179", uri::__internal::HostType::kIPv4)
                .expectPort("24791")
                .expectPath("/list"),

            UriTestPayload::success("https://[6d47:9f20:6d24:3b85:f393:62d4:6753:4fd5]/blog/tags/search/posts/blog?id=123#about")
                .expectScheme("https")
                .expectHost("6d47:9f20:6d24:3b85:f393:62d4:6753:4fd5", uri::__internal::HostType::kIPLiteral)
                .expectPath("/blog/tags/search/posts/blog")
                .expectQuery("id=123")
                .expectFragment("about"),

            UriTestPayload::success("http://williams.nash.mahoney.com/posts/category/explore/categories/wp-content?name=test#footer")
                .expectScheme("http")
                .expectHost("williams.nash.mahoney.com")
                .expectPath("/posts/category/explore/categories/wp-content")
                .expectQuery("name=test")
                .expectFragment("footer"),

            UriTestPayload::success("https://[3a98:b4f6:f7c1:b753:356:9af3:9a9e:64aa]/blog/posts/list/tag?name=test")
                .expectScheme("https")
                .expectHost("3a98:b4f6:f7c1:b753:356:9af3:9a9e:64aa", uri::__internal::HostType::kIPLiteral)
                .expectPath("/blog/posts/list/tag")
                .expectQuery("name=test"),

            UriTestPayload::success("https://[c6dc:2f35:f947:14ed:bd8a:2184:10e9:e629]/tag/app/list/posts?name=test")
                .expectScheme("https")
                .expectHost("c6dc:2f35:f947:14ed:bd8a:2184:10e9:e629", uri::__internal::HostType::kIPLiteral)
                .expectPath("/tag/app/list/posts")
                .expectQuery("name=test"),

            UriTestPayload::success("http://[72e:445e:c4fd:e57d:257:cb3c:5f8b:4cc]/main/wp-content#section1")
                .expectScheme("http")
                .expectHost("72e:445e:c4fd:e57d:257:cb3c:5f8b:4cc", uri::__internal::HostType::kIPLiteral)
                .expectPath("/main/wp-content")
                .expectFragment("section1"),

            UriTestPayload::success("http://182.54.217.246/categories/search/category/explore/list#about")
                .expectScheme("http")
                .expectHost("182.54.217.246", uri::__internal::HostType::kIPv4)
                .expectPath("/categories/search/category/explore/list")
                .expectFragment("about"),

            UriTestPayload::success("https://115.60.196.164/app/search/main/categories/list")
                .expectScheme("https")
                .expectHost("115.60.196.164", uri::__internal::HostType::kIPv4)
                .expectPath("/app/search/main/categories/list"),

            UriTestPayload::success("https://[cb1f:974d:353a:f6b5:da40:3bf3:5cc5:dfde]/list#section2")
                .expectScheme("https")
                .expectHost("cb1f:974d:353a:f6b5:da40:3bf3:5cc5:dfde", uri::__internal::HostType::kIPLiteral)
                .expectPath("/list")
                .expectFragment("section2"),

            UriTestPayload::success("http://[e8b9:4669:5c5c:b923:8a3a:bed:d00a:3cfb]/tag/category/search#about")
                .expectScheme("http")
                .expectHost("e8b9:4669:5c5c:b923:8a3a:bed:d00a:3cfb", uri::__internal::HostType::kIPLiteral)
                .expectPath("/tag/category/search")
                .expectFragment("about"),

            UriTestPayload::success("http://152.43.41.109/explore/wp-content/app/search")
                .expectScheme("http")
                .expectHost("152.43.41.109", uri::__internal::HostType::kIPv4)
                .expectPath("/explore/wp-content/app/search"),

            UriTestPayload::success("http://159.61.25.10:61026/explore/categories/wp-content?name=test#section2")
                .expectScheme("http")
                .expectHost("159.61.25.10", uri::__internal::HostType::kIPv4)
                .expectPort("61026")
                .expectPath("/explore/categories/wp-content")
                .expectQuery("name=test")
                .expectFragment("section2"),

            UriTestPayload::success("http://murphy.com/list?id=123")
                .expectScheme("http")
                .expectHost("murphy.com")
                .expectPath("/list")
                .expectQuery("id=123"),

            UriTestPayload::success("http://jackson.padilla-freeman.info/app/main/tag/explore/explore#section1")
                .expectScheme("http")
                .expectHost("jackson.padilla-freeman.info")
                .expectPath("/app/main/tag/explore/explore")
                .expectFragment("section1"),

            UriTestPayload::success("https://tucker.com/list/search/tags?id=123")
                .expectScheme("https")
                .expectHost("tucker.com")
                .expectPath("/list/search/tags")
                .expectQuery("id=123"),

            UriTestPayload::success("https://[3ffb:534a:6b78:6b27:2c88:fa1c:536f:9b90]/category/app#contact")
                .expectScheme("https")
                .expectHost("3ffb:534a:6b78:6b27:2c88:fa1c:536f:9b90", uri::__internal::HostType::kIPLiteral)
                .expectPath("/category/app")
                .expectFragment("contact"),

            UriTestPayload::success("https://144.39.43.228/search/tags/category/wp-content/category?sort=asc&page=2#contact")
                .expectScheme("https")
                .expectHost("144.39.43.228", uri::__internal::HostType::kIPv4)
                .expectPath("/search/tags/category/wp-content/category")
                .expectQuery("sort=asc&page=2")
                .expectFragment("contact"),

            UriTestPayload::success("https://[2bb0:f9dd:6b76:bf13:66fd:dc22:3b9f:cd3d]/category/list?search=query")
                .expectScheme("https")
                .expectHost("2bb0:f9dd:6b76:bf13:66fd:dc22:3b9f:cd3d", uri::__internal::HostType::kIPLiteral)
                .expectPath("/category/list")
                .expectQuery("search=query"),

            UriTestPayload::success("https://carroll-alexander.net/posts/search/posts/list?filter=active#contact")
                .expectScheme("https")
                .expectHost("carroll-alexander.net")
                .expectPath("/posts/search/posts/list")
                .expectQuery("filter=active")
                .expectFragment("contact"),

            UriTestPayload::success("http://175.244.168.165/categories/wp-content/explore/categories")
                .expectScheme("http")
                .expectHost("175.244.168.165", uri::__internal::HostType::kIPv4)
                .expectPath("/categories/wp-content/explore/categories"),

            UriTestPayload::success("http://158.238.146.203:45913/blog/list?q=keyword")
                .expectScheme("http")
                .expectHost("158.238.146.203", uri::__internal::HostType::kIPv4)
                .expectPort("45913")
                .expectPath("/blog/list")
                .expectQuery("q=keyword"),

            UriTestPayload::success("http://152.43.41.109/search?name=test#section1")
                .expectScheme("http")
                .expectHost("152.43.41.109", uri::__internal::HostType::kIPv4)
                .expectPath("/search")
                .expectQuery("name=test")
                .expectFragment("section1"),

            UriTestPayload::success("https://86.181.36.48/categories/posts")
                .expectScheme("https")
                .expectHost("86.181.36.48", uri::__internal::HostType::kIPv4)
                .expectPath("/categories/posts"),

            UriTestPayload::success("http://72.117.35.49/wp-content/explore#section2")
                .expectScheme("http")
                .expectHost("72.117.35.49", uri::__internal::HostType::kIPv4)
                .expectPath("/wp-content/explore")
                .expectFragment("section2"),

            UriTestPayload::success("http://williams-bradley.haynes.info/search/search/blog?id=123#footer")
                .expectScheme("http")
                .expectHost("williams-bradley.haynes.info")
                .expectPath("/search/search/blog")
                .expectQuery("id=123")
                .expectFragment("footer"),

            UriTestPayload::success("http://6.237.196.48:21853/categories/app/wp-content/category/wp-content?q=keyword#footer")
                .expectScheme("http")
                .expectHost("6.237.196.48", uri::__internal::HostType::kIPv4)
                .expectPort("21853")
                .expectPath("/categories/app/wp-content/category/wp-content")
                .expectQuery("q=keyword")
                .expectFragment("footer"),

            UriTestPayload::success("https://221.176.68.68:4073/search/list#section1")
                .expectScheme("https")
                .expectHost("221.176.68.68", uri::__internal::HostType::kIPv4)
                .expectPort("4073")
                .expectPath("/search/list")
                .expectFragment("section1"),

            UriTestPayload::success("https://72.5.139.161:34176/tags/tags/list")
                .expectScheme("https")
                .expectHost("72.5.139.161", uri::__internal::HostType::kIPv4)
                .expectPort("34176")
                .expectPath("/tags/tags/list"),

            UriTestPayload::success("http://larson.marks.com/category?sort=asc&page=2#section2")
                .expectScheme("http")
                .expectHost("larson.marks.com")
                .expectPath("/category")
                .expectQuery("sort=asc&page=2")
                .expectFragment("section2"),

            UriTestPayload::success("http://[afe8:ee1a:ff07:a27:c6cf:cde0:cd2a:801d]/list/category/category?name=test")
                .expectScheme("http")
                .expectHost("afe8:ee1a:ff07:a27:c6cf:cde0:cd2a:801d", uri::__internal::HostType::kIPLiteral)
                .expectPath("/list/category/category")
                .expectQuery("name=test"),

            UriTestPayload::success("https://215.215.167.20/categories/tag/categories")
                .expectScheme("https")
                .expectHost("215.215.167.20", uri::__internal::HostType::kIPv4)
                .expectPath("/categories/tag/categories"),

            UriTestPayload::success("http://118.207.3.210:39939/category/app?sort=asc&page=2")
                .expectScheme("http")
                .expectHost("118.207.3.210", uri::__internal::HostType::kIPv4)
                .expectPort("39939")
                .expectPath("/category/app")
                .expectQuery("sort=asc&page=2"),

            UriTestPayload::success("https://murray.net/wp-content/list/tag?name=test")
                .expectScheme("https")
                .expectHost("murray.net")
                .expectPath("/wp-content/list/tag")
                .expectQuery("name=test"),

            UriTestPayload::success("https://miller-lopez.rodriguez.malone.com/search/tag/main/tag?sort=asc&page=2")
                .expectScheme("https")
                .expectHost("miller-lopez.rodriguez.malone.com")
                .expectPath("/search/tag/main/tag")
                .expectQuery("sort=asc&page=2"),

            UriTestPayload::success("https://120.27.130.75/tags")
                .expectScheme("https")
                .expectHost("120.27.130.75", uri::__internal::HostType::kIPv4)
                .expectPath("/tags"),

            UriTestPayload::success("http://198.173.141.179:31494/blog?filter=active#home")
                .expectScheme("http")
                .expectHost("198.173.141.179", uri::__internal::HostType::kIPv4)
                .expectPort("31494")
                .expectPath("/blog")
                .expectQuery("filter=active")
                .expectFragment("home"),

            UriTestPayload::success("https://martinez.ryan.orr.info/tags?id=123#section1")
                .expectScheme("https")
                .expectHost("martinez.ryan.orr.info")
                .expectPath("/tags")
                .expectQuery("id=123")
                .expectFragment("section1"),

            UriTestPayload::success("http://[3f7e:d4c6:2bef:71ba:720b:b240:f67a:c50a]/tags/wp-content/blog?search=query")
                .expectScheme("http")
                .expectHost("3f7e:d4c6:2bef:71ba:720b:b240:f67a:c50a", uri::__internal::HostType::kIPLiteral)
                .expectPath("/tags/wp-content/blog")
                .expectQuery("search=query"),

            UriTestPayload::success("https://2.40.215.163/tags/wp-content#footer")
                .expectScheme("https")
                .expectHost("2.40.215.163", uri::__internal::HostType::kIPv4)
                .expectPath("/tags/wp-content")
                .expectFragment("footer"),

            UriTestPayload::success("http://168.111.28.137:16352/explore/blog/search/blog/blog?sort=asc&page=2#contact")
                .expectScheme("http")
                .expectHost("168.111.28.137", uri::__internal::HostType::kIPv4)
                .expectPort("16352")
                .expectPath("/explore/blog/search/blog/blog")
                .expectQuery("sort=asc&page=2")
                .expectFragment("contact"),

            UriTestPayload::success("https://[9e20:79a6:c0ad:798c:2f74:481d:2d34:3b8d]/category/search/app/blog")
                .expectScheme("https")
                .expectHost("9e20:79a6:c0ad:798c:2f74:481d:2d34:3b8d", uri::__internal::HostType::kIPLiteral)
                .expectPath("/category/search/app/blog"),

            UriTestPayload::success("https://207.230.200.123/explore/explore/app/list?name=test#about")
                .expectScheme("https")
                .expectHost("207.230.200.123", uri::__internal::HostType::kIPv4)
                .expectPath("/explore/explore/app/list")
                .expectQuery("name=test")
                .expectFragment("about"),

            UriTestPayload::success("https://kelly.copeland-miller.info/app?search=query#section1")
                .expectScheme("https")
                .expectHost("kelly.copeland-miller.info")
                .expectPath("/app")
                .expectQuery("search=query")
                .expectFragment("section1"),

            UriTestPayload::success("http://[b387:7aa8:364b:39e3:3bc5:755e:a0ec:fc87]/list/list/explore/posts?sort=asc&page=2#section1")
                .expectScheme("http")
                .expectHost("b387:7aa8:364b:39e3:3bc5:755e:a0ec:fc87", uri::__internal::HostType::kIPLiteral)
                .expectPath("/list/list/explore/posts")
                .expectQuery("sort=asc&page=2")
                .expectFragment("section1"),

            UriTestPayload::success("http://[bb90:dce0:3bc1:6654:95df:96c7:7c9f:4790]/explore/tags/search?q=keyword#section2")
                .expectScheme("http")
                .expectHost("bb90:dce0:3bc1:6654:95df:96c7:7c9f:4790", uri::__internal::HostType::kIPLiteral)
                .expectPath("/explore/tags/search")
                .expectQuery("q=keyword")
                .expectFragment("section2"),

            UriTestPayload::success("https://scott-miller.com/category/category#contact")
                .expectScheme("https")
                .expectHost("scott-miller.com")
                .expectPath("/category/category")
                .expectFragment("contact"),

            UriTestPayload::success("https://huff.lopez.org/categories/wp-content/explore/categories?q=keyword#section2")
                .expectScheme("https")
                .expectHost("huff.lopez.org")
                .expectPath("/categories/wp-content/explore/categories")
                .expectQuery("q=keyword")
                .expectFragment("section2"),

            UriTestPayload::success("https://young.edwards-hoffman.richardson.com/wp-content/app/categories")
                .expectScheme("https")
                .expectHost("young.edwards-hoffman.richardson.com")
                .expectPath("/wp-content/app/categories"),

            UriTestPayload::success("http://219.124.176.92:54758/blog/category?id=123#footer")
                .expectScheme("http")
                .expectHost("219.124.176.92", uri::__internal::HostType::kIPv4)
                .expectPort("54758")
                .expectPath("/blog/category")
                .expectQuery("id=123")
                .expectFragment("footer"),

            UriTestPayload::success("http://morris.jackson-owens.com/categories/wp-content/explore/categories")
                .expectScheme("http")
                .expectHost("morris.jackson-owens.com")
                .expectPath("/categories/wp-content/explore/categories"),

            UriTestPayload::success("http://93.45.178.197/posts/blog/app/list")
                .expectScheme("http")
                .expectHost("93.45.178.197", uri::__internal::HostType::kIPv4)
                .expectPath("/posts/blog/app/list"),

            UriTestPayload::success("https://104.54.11.45/blog/app/posts?sort=asc&page=2#home")
                .expectScheme("https")
                .expectHost("104.54.11.45", uri::__internal::HostType::kIPv4)
                .expectPath("/blog/app/posts")
                .expectQuery("sort=asc&page=2")
                .expectFragment("home"),

            UriTestPayload::success("https://[3c14:220:70ba:f1ea:28ca:949b:7ba1:92f0]/search#home")
                .expectScheme("https")
                .expectHost("3c14:220:70ba:f1ea:28ca:949b:7ba1:92f0", uri::__internal::HostType::kIPLiteral)
                .expectPath("/search")
                .expectFragment("home"),

            UriTestPayload::success("http://robbins-hutchinson.com/tags")
                .expectScheme("http")
                .expectHost("robbins-hutchinson.com")
                .expectPath("/tags"),

            UriTestPayload::success("http://[f0f9:36d5:1d75:1e89:d7a1:fe6b:4577:650e]/app/blog#section2")
                .expectScheme("http")
                .expectHost("f0f9:36d5:1d75:1e89:d7a1:fe6b:4577:650e", uri::__internal::HostType::kIPLiteral)
                .expectPath("/app/blog")
                .expectFragment("section2"),

            UriTestPayload::success("https://64.244.227.45:58746/tags/blog/category/list?q=keyword#home")
                .expectScheme("https")
                .expectHost("64.244.227.45", uri::__internal::HostType::kIPv4)
                .expectPort("58746")
                .expectPath("/tags/blog/category/list")
                .expectQuery("q=keyword")
                .expectFragment("home"),

            UriTestPayload::success("https://[93ff:8df5:90a8:436f:eeae:c0b1:1d2:4f79]/posts/tags#home")
                .expectScheme("https")
                .expectHost("93ff:8df5:90a8:436f:eeae:c0b1:1d2:4f79", uri::__internal::HostType::kIPLiteral)
                .expectPath("/posts/tags")
                .expectFragment("home"),

            UriTestPayload::success("http://[e973:c1fa:43a1:60ae:5d0f:5839:6873:d7e6]/tags/list/list/app")
                .expectScheme("http")
                .expectHost("e973:c1fa:43a1:60ae:5d0f:5839:6873:d7e6", uri::__internal::HostType::kIPLiteral)
                .expectPath("/tags/list/list/app"),

            UriTestPayload::success("https://88.119.253.196:21278/search/posts/tag/app/wp-content?filter=active#footer")
                .expectScheme("https")
                .expectHost("88.119.253.196", uri::__internal::HostType::kIPv4)
                .expectPort("21278")
                .expectPath("/search/posts/tag/app/wp-content")
                .expectQuery("filter=active")
                .expectFragment("footer"),

            UriTestPayload::success("https://27.112.228.241/categories/list/posts")
                .expectScheme("https")
                .expectHost("27.112.228.241", uri::__internal::HostType::kIPv4)
                .expectPath("/categories/list/posts"),

            UriTestPayload::success("https://banks.johnson.santos.com/tags/wp-content/posts/app/wp-content")
                .expectScheme("https")
                .expectHost("banks.johnson.santos.com")
                .expectPath("/tags/wp-content/posts/app/wp-content"),

            UriTestPayload::success("https://[4d75:fb85:165a:5872:ff69:aca4:a5b3:2adf]/tags/main")
                .expectScheme("https")
                .expectHost("4d75:fb85:165a:5872:ff69:aca4:a5b3:2adf", uri::__internal::HostType::kIPLiteral)
                .expectPath("/tags/main"),

            UriTestPayload::success("https://210.36.232.253:63988/list/blog/list/posts/category?filter=active#footer")
                .expectScheme("https")
                .expectHost("210.36.232.253", uri::__internal::HostType::kIPv4)
                .expectPort("63988")
                .expectPath("/list/blog/list/posts/category")
                .expectQuery("filter=active")
                .expectFragment("footer"),

            UriTestPayload::success("http://98.142.72.222:10898/blog/search/blog/posts/main")
                .expectScheme("http")
                .expectHost("98.142.72.222", uri::__internal::HostType::kIPv4)
                .expectPort("10898")
                .expectPath("/blog/search/blog/posts/main"),

            UriTestPayload::success("https://[506:dc73:23bb:62da:eab1:b8cd:7dfe:bb60]/search/explore?search=query#about")
                .expectScheme("https")
                .expectHost("506:dc73:23bb:62da:eab1:b8cd:7dfe:bb60", uri::__internal::HostType::kIPLiteral)
                .expectPath("/search/explore")
                .expectQuery("search=query")
                .expectFragment("about"),

            UriTestPayload::success("https://[95bf:8d77:63e3:b383:567a:1758:6bc9:1e8]/list/explore/tags")
                .expectScheme("https")
                .expectHost("95bf:8d77:63e3:b383:567a:1758:6bc9:1e8", uri::__internal::HostType::kIPLiteral)
                .expectPath("/list/explore/tags"),

            UriTestPayload::success("http://bryant-duarte.davis.biz/app/blog/categories/list/wp-content?q=keyword")
                .expectScheme("http")
                .expectHost("bryant-duarte.davis.biz")
                .expectPath("/app/blog/categories/list/wp-content")
                .expectQuery("q=keyword"),

            UriTestPayload::success("http://206.134.197.85/categories/wp-content/main/list/explore")
                .expectScheme("http")
                .expectHost("206.134.197.85", uri::__internal::HostType::kIPv4)
                .expectPath("/categories/wp-content/main/list/explore"),

            UriTestPayload::success("https://[22f3:dd7d:ba1c:9965:1117:a755:2c39:9b9f]/tags/main?id=123")
                .expectScheme("https")
                .expectHost("22f3:dd7d:ba1c:9965:1117:a755:2c39:9b9f", uri::__internal::HostType::kIPLiteral)
                .expectPath("/tags/main")
                .expectQuery("id=123"),

            UriTestPayload::success("https://85.240.31.107:23568/category/category/blog?search=query#contact")
                .expectScheme("https")
                .expectHost("85.240.31.107", uri::__internal::HostType::kIPv4)
                .expectPort("23568")
                .expectPath("/category/category/blog")
                .expectQuery("search=query")
                .expectFragment("contact"),

            UriTestPayload::success("http://9.186.78.96:33716/posts/tag?filter=active#section1")
                .expectScheme("http")
                .expectHost("9.186.78.96", uri::__internal::HostType::kIPv4)
                .expectPort("33716")
                .expectPath("/posts/tag")
                .expectQuery("filter=active")
                .expectFragment("section1"),

            UriTestPayload::success("https://91.171.68.223/tag/tag/list")
                .expectScheme("https")
                .expectHost("91.171.68.223", uri::__internal::HostType::kIPv4)
                .expectPath("/tag/tag/list"),

            UriTestPayload::success("https://188.127.221.191/blog/main/wp-content/list#section2")
                .expectScheme("https")
                .expectHost("188.127.221.191", uri::__internal::HostType::kIPv4)
                .expectPath("/blog/main/wp-content/list")
                .expectFragment("section2"),

            UriTestPayload::success("http://84.116.175.188/tags/categories/category/category/app")
                .expectScheme("http")
                .expectHost("84.116.175.188", uri::__internal::HostType::kIPv4)
                .expectPath("/tags/categories/category/category/app"),

            UriTestPayload::success("https://213.219.68.29:57389/app")
                .expectScheme("https")
                .expectHost("213.219.68.29", uri::__internal::HostType::kIPv4)
                .expectPort("57389")
                .expectPath("/app"),

            UriTestPayload::success("http://219.246.26.138/tags/blog/category/list#home")
                .expectScheme("http")
                .expectHost("219.246.26.138", uri::__internal::HostType::kIPv4)
                .expectPath("/tags/blog/category/list")
                .expectFragment("home"),

            UriTestPayload::success("http://38.255.251.187:46206/blog/blog/blog")
                .expectScheme("http")
                .expectHost("38.255.251.187", uri::__internal::HostType::kIPv4)
                .expectPort("46206")
                .expectPath("/blog/blog/blog"),

            UriTestPayload::success("http://walker-bryant.info/search/explore")
                .expectScheme("http")
                .expectHost("walker-bryant.info")
                .expectPath("/search/explore"),

            UriTestPayload::success("https://140.35.26.68:11219/explore?q=keyword#section1")
                .expectScheme("https")
                .expectHost("140.35.26.68", uri::__internal::HostType::kIPv4)
                .expectPort("11219")
                .expectPath("/explore")
                .expectQuery("q=keyword")
                .expectFragment("section1"),

            UriTestPayload::success("http://19.127.4.55/tag/explore/tags#about")
                .expectScheme("http")
                .expectHost("19.127.4.55", uri::__internal::HostType::kIPv4)
                .expectPath("/tag/explore/tags")
                .expectFragment("about"),

            UriTestPayload::success("https://223.208.124.253/category/categories/category#section2")
                .expectScheme("https")
                .expectHost("223.208.124.253", uri::__internal::HostType::kIPv4)
                .expectPath("/category/categories/category")
                .expectFragment("section2"),

            UriTestPayload::success("http://150.244.161.202:56832/wp-content?sort=asc&page=2")
                .expectScheme("http")
                .expectHost("150.244.161.202", uri::__internal::HostType::kIPv4)
                .expectPort("56832")
                .expectPath("/wp-content")
                .expectQuery("sort=asc&page=2"),

            UriTestPayload::success("http://97.19.194.61/categories/list/posts")
                .expectScheme("http")
                .expectHost("97.19.194.61", uri::__internal::HostType::kIPv4)
                .expectPath("/categories/list/posts"),

            UriTestPayload::success("https://124.4.40.236:50328/blog/explore?sort=asc&page=2")
                .expectScheme("https")
                .expectHost("124.4.40.236", uri::__internal::HostType::kIPv4)
                .expectPort("50328")
                .expectPath("/blog/explore")
                .expectQuery("sort=asc&page=2"),

            UriTestPayload::success("http://stewart.larson-johnson.house-douglas.com/blog/wp-content/wp-content/wp-content#about")
                .expectScheme("http")
                .expectHost("stewart.larson-johnson.house-douglas.com")
                .expectPath("/blog/wp-content/wp-content/wp-content")
                .expectFragment("about"),

            UriTestPayload::success("https://4.122.178.126:8326/blog?name=test")
                .expectScheme("https")
                .expectHost("4.122.178.126", uri::__internal::HostType::kIPv4)
                .expectPort("8326")
                .expectPath("/blog")
                .expectQuery("name=test"),

            UriTestPayload::success("https://[31f8:ad12:7778:f776:91d2:2a8b:7643:5f1d]/blog/explore")
                .expectScheme("https")
                .expectHost("31f8:ad12:7778:f776:91d2:2a8b:7643:5f1d", uri::__internal::HostType::kIPLiteral)
                .expectPath("/blog/explore"),

            UriTestPayload::success("http://54.10.135.56/search/search/wp-content/explore/app?name=test")
                .expectScheme("http")
                .expectHost("54.10.135.56", uri::__internal::HostType::kIPv4)
                .expectPath("/search/search/wp-content/explore/app")
                .expectQuery("name=test"),

            UriTestPayload::success("https://105.190.43.26/search")
                .expectScheme("https")
                .expectHost("105.190.43.26", uri::__internal::HostType::kIPv4)
                .expectPath("/search"),

            UriTestPayload::success("https://100.252.163.141/posts/app/main/search?filter=active")
                .expectScheme("https")
                .expectHost("100.252.163.141", uri::__internal::HostType::kIPv4)
                .expectPath("/posts/app/main/search")
                .expectQuery("filter=active"),

            UriTestPayload::success("http://[a714:21ef:fda:d209:948f:90c6:7507:bd50]/category/explore/main/categories?name=test")
                .expectScheme("http")
                .expectHost("a714:21ef:fda:d209:948f:90c6:7507:bd50", uri::__internal::HostType::kIPLiteral)
                .expectPath("/category/explore/main/categories")
                .expectQuery("name=test"),

            UriTestPayload::success("http://miller.scott.biz/explore/app/tags/categories/explore#about")
                .expectScheme("http")
                .expectHost("miller.scott.biz")
                .expectPath("/explore/app/tags/categories/explore")
                .expectFragment("about"),

            UriTestPayload::success("http://[f7e5:e73:c4a1:b25:3795:e9c2:f777:a35a]/search/categories")
                .expectScheme("http")
                .expectHost("f7e5:e73:c4a1:b25:3795:e9c2:f777:a35a", uri::__internal::HostType::kIPLiteral)
                .expectPath("/search/categories"),

            UriTestPayload::success("http://torres.kelley.davidson.com/search/blog/app/search/wp-content#section2")
                .expectScheme("http")
                .expectHost("torres.kelley.davidson.com")
                .expectPath("/search/blog/app/search/wp-content")
                .expectFragment("section2"),

            UriTestPayload::success("https://maldonado.morgan.biz/explore/categories/categories/search/categories?search=query")
                .expectScheme("https")
                .expectHost("maldonado.morgan.biz")
                .expectPath("/explore/categories/categories/search/categories")
                .expectQuery("search=query"),

            UriTestPayload::success("http://[dbbb:27bc:aeba:f1a5:d032:c0f5:77ae:8ffa]/explore/search/tag/list?filter=active#section1")
                .expectScheme("http")
                .expectHost("dbbb:27bc:aeba:f1a5:d032:c0f5:77ae:8ffa", uri::__internal::HostType::kIPLiteral)
                .expectPath("/explore/search/tag/list")
                .expectQuery("filter=active")
                .expectFragment("section1"),

            UriTestPayload::success("http://[4c72:5f2e:6be1:fab7:8eb0:af23:502a:94ec]/tag/posts/category?search=query#footer")
                .expectScheme("http")
                .expectHost("4c72:5f2e:6be1:fab7:8eb0:af23:502a:94ec", uri::__internal::HostType::kIPLiteral)
                .expectPath("/tag/posts/category")
                .expectQuery("search=query")
                .expectFragment("footer"),

            UriTestPayload::success("https://108.79.97.127:39090/tags/blog/categories/list/wp-content?search=query")
                .expectScheme("https")
                .expectHost("108.79.97.127", uri::__internal::HostType::kIPv4)
                .expectPort("39090")
                .expectPath("/tags/blog/categories/list/wp-content")
                .expectQuery("search=query"),

            UriTestPayload::success("http://[4e2:c5ad:f708:3c9:8127:d8d9:7eee:1cbc]/categories/app/main")
                .expectScheme("http")
                .expectHost("4e2:c5ad:f708:3c9:8127:d8d9:7eee:1cbc", uri::__internal::HostType::kIPLiteral)
                .expectPath("/categories/app/main"),

            UriTestPayload::success("http://96.104.216.128/posts")
                .expectScheme("http")
                .expectHost("96.104.216.128", uri::__internal::HostType::kIPv4)
                .expectPath("/posts"),

            UriTestPayload::success("http://147.180.73.158/app?sort=asc&page=2#section1")
                .expectScheme("http")
                .expectHost("147.180.73.158", uri::__internal::HostType::kIPv4)
                .expectPath("/app")
                .expectQuery("sort=asc&page=2")
                .expectFragment("section1"),

            UriTestPayload::success("https://29.207.245.29:14523/app/posts")
                .expectScheme("https")
                .expectHost("29.207.245.29", uri::__internal::HostType::kIPv4)
                .expectPort("14523")
                .expectPath("/app/posts"),

            UriTestPayload::success("https://168.173.136.80/list/blog?name=test")
                .expectScheme("https")
                .expectHost("168.173.136.80", uri::__internal::HostType::kIPv4)
                .expectPath("/list/blog")
                .expectQuery("name=test"),

            UriTestPayload::success("http://66.179.90.207:17186/categories/search?sort=asc&page=2")
                .expectScheme("http")
                .expectHost("66.179.90.207", uri::__internal::HostType::kIPv4)
                .expectPort("17186")
                .expectPath("/categories/search")
                .expectQuery("sort=asc&page=2"),

            UriTestPayload::success("http://[b3ae:44f:67c3:2185:901f:9e47:8ec3:ed39]/wp-content/categories/categories/blog/posts?filter=active")
                .expectScheme("http")
                .expectHost("b3ae:44f:67c3:2185:901f:9e47:8ec3:ed39", uri::__internal::HostType::kIPLiteral)
                .expectPath("/wp-content/categories/categories/blog/posts")
                .expectQuery("filter=active"),

            UriTestPayload::success("http://220.47.245.144:22902/category/category#about")
                .expectScheme("http")
                .expectHost("220.47.245.144", uri::__internal::HostType::kIPv4)
                .expectPort("22902")
                .expectPath("/category/category")
                .expectFragment("about"),

            UriTestPayload::success("https://[49df:f0ae:2bf9:e53f:1df1:fa12:c88:3efa]/main?sort=asc&page=2#contact")
                .expectScheme("https")
                .expectHost("49df:f0ae:2bf9:e53f:1df1:fa12:c88:3efa", uri::__internal::HostType::kIPLiteral)
                .expectPath("/main")
                .expectQuery("sort=asc&page=2")
                .expectFragment("contact"),

            UriTestPayload::success("http://carroll-turner.com/wp-content/wp-content/blog/main#footer")
                .expectScheme("http")
                .expectHost("carroll-turner.com")
                .expectPath("/wp-content/wp-content/blog/main")
                .expectFragment("footer"),

            UriTestPayload::success("http://nelson.ingram-lowe.com/main?q=keyword")
                .expectScheme("http")
                .expectHost("nelson.ingram-lowe.com")
                .expectPath("/main")
                .expectQuery("q=keyword"),

            UriTestPayload::success("http://62.91.40.142/tag/blog/blog/posts/wp-content?sort=asc&page=2")
                .expectScheme("http")
                .expectHost("62.91.40.142", uri::__internal::HostType::kIPv4)
                .expectPath("/tag/blog/blog/posts/wp-content")
                .expectQuery("sort=asc&page=2"),

            UriTestPayload::success("https://banks.johnson.santos.com/explore/explore/posts/blog")
                .expectScheme("https")
                .expectHost("banks.johnson.santos.com")
                .expectPath("/explore/explore/posts/blog"),

            UriTestPayload::success("https://115.61.75.167:19272/tag/explore/categories/explore?search=query")
                .expectScheme("https")
                .expectHost("115.61.75.167", uri::__internal::HostType::kIPv4)
                .expectPort("19272")
                .expectPath("/tag/explore/categories/explore")
                .expectQuery("search=query"),

            UriTestPayload::success("https://59.57.45.197/wp-content?name=test#section2")
                .expectScheme("https")
                .expectHost("59.57.45.197", uri::__internal::HostType::kIPv4)
                .expectPath("/wp-content")
                .expectQuery("name=test")
                .expectFragment("section2"),

            UriTestPayload::success("http://40.149.55.241/app/tag/main/list?search=query#section1")
                .expectScheme("http")
                .expectHost("40.149.55.241", uri::__internal::HostType::kIPv4)
                .expectPath("/app/tag/main/list")
                .expectQuery("search=query")
                .expectFragment("section1"),

            UriTestPayload::success("https://[6f85:2ec1:1e56:2c90:93a7:1235:d893:f4df]/app/posts#section1")
                .expectScheme("https")
                .expectHost("6f85:2ec1:1e56:2c90:93a7:1235:d893:f4df", uri::__internal::HostType::kIPLiteral)
                .expectPath("/app/posts")
                .expectFragment("section1"),

            UriTestPayload::success("http://2.40.215.163/wp-content/search/main/tag/list")
                .expectScheme("http")
                .expectHost("2.40.215.163", uri::__internal::HostType::kIPv4)
                .expectPath("/wp-content/search/main/tag/list"),

            UriTestPayload::success("https://rose-holt.goodman.com/main/wp-content/tags/tags?filter=active#about")
                .expectScheme("https")
                .expectHost("rose-holt.goodman.com")
                .expectPath("/main/wp-content/tags/tags")
                .expectQuery("filter=active")
                .expectFragment("about"),

            UriTestPayload::success("http://49.66.56.69/app/tag/main/list")
                .expectScheme("http")
                .expectHost("49.66.56.69", uri::__internal::HostType::kIPv4)
                .expectPath("/app/tag/main/list"),

            UriTestPayload::success("https://guzman.fowler.info/app/tag/main/list?search=query#contact")
                .expectScheme("https")
                .expectHost("guzman.fowler.info")
                .expectPath("/app/tag/main/list")
                .expectQuery("search=query")
                .expectFragment("contact")
        )
);

TEST_P(UriParserUriTestingFixture, TestThatUriParsingIsCorrect) {
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
        uri::__internal::Uri(reader,
            parsed_scheme,
            parsed_userInfo, parsed_host, parsed_host_type, parsed_port, parsed_path,
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
