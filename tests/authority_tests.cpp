#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "authority.h"

using uri::Authority;

TEST(UriAuthority, AuthoritiesWithSameContentAreEqual) {
    Authority a("www.mozila.com");
    Authority b(std::nullopt, "www.mozila.com", std::nullopt);
    EXPECT_EQ(a, b);
}

TEST(UriAuthority, AuthoritiesWithDifferentContentAreNotEqual) {
    Authority a("www.mozila.com", "80");
    Authority b(std::nullopt, "www.mozila.com", std::nullopt);
    EXPECT_NE(a, b);
}

class AuthorityTestingFixture: public ::testing::TestWithParam<std::pair<std::string, Authority>> {};

INSTANTIATE_TEST_SUITE_P(
        AuthorityParsingTests,
        AuthorityTestingFixture,
        ::testing::Values(
            std::make_pair("some@103.218.46.129:37324", Authority("some", "103.218.46.129", "37324")),
            std::make_pair("111.214.215.218:54506", Authority(std::nullopt, "111.214.215.218", "54506")),
            std::make_pair("147.11.235.42:62447", Authority(std::nullopt, "147.11.235.42", "62447")),
            std::make_pair("[8e4d:b902:92d5:8f3:9ef7:f1dc:1218:d84a]", Authority(std::nullopt, "8e4d:b902:92d5:8f3:9ef7:f1dc:1218:d84a", std::nullopt)),
            std::make_pair("206.184.19.245:46529", Authority(std::nullopt, "206.184.19.245", "46529")),
            std::make_pair("court@[62f:a49e:5dfa:cca7:ccd8:55fe:8806:bf69]", Authority("court", "62f:a49e:5dfa:cca7:ccd8:55fe:8806:bf69", std::nullopt)),
            std::make_pair("record@wilson.frazier.harper.org", Authority("record", "wilson.frazier.harper.org", std::nullopt)),
            std::make_pair("just@allen.mcguire.biz", Authority("just", "allen.mcguire.biz", std::nullopt)),
            std::make_pair("water@186.190.32.211", Authority("water", "186.190.32.211", std::nullopt)),
            std::make_pair("notice@cabrera.com", Authority("notice", "cabrera.com", std::nullopt)),
            std::make_pair("several@8.26.145.207", Authority("several", "8.26.145.207", std::nullopt)),
            std::make_pair("[e08b:cb59:5a3:4a76:bd46:860d:b5fe:e3b8]", Authority(std::nullopt, "e08b:cb59:5a3:4a76:bd46:860d:b5fe:e3b8", std::nullopt)),
            std::make_pair("security@68.237.55.210:40313", Authority("security", "68.237.55.210", "40313")),
            std::make_pair("kelley.lewis.com", Authority(std::nullopt, "kelley.lewis.com", std::nullopt)),
            std::make_pair("[86b8:36cd:d44a:bcf3:b347:3:bab8:8ec0]", Authority(std::nullopt, "86b8:36cd:d44a:bcf3:b347:3:bab8:8ec0", std::nullopt)),
            std::make_pair("establish@143.158.94.161:1848", Authority("establish", "143.158.94.161", "1848")),
            std::make_pair("83.234.161.14", Authority(std::nullopt, "83.234.161.14", std::nullopt)),
            std::make_pair("explain@pena.mcclure.com", Authority("explain", "pena.mcclure.com", std::nullopt)),
            std::make_pair("all@[c184:7b30:52c9:7ba8:507f:a089:832f:5a9f]", Authority("all", "c184:7b30:52c9:7ba8:507f:a089:832f:5a9f", std::nullopt)),
            std::make_pair("risk@ware.dunn.booth.com", Authority("risk", "ware.dunn.booth.com", std::nullopt)),
            std::make_pair("establish@allen.ray.powers-franco.net", Authority("establish", "allen.ray.powers-franco.net", std::nullopt)),
            std::make_pair("188.183.6.140", Authority(std::nullopt, "188.183.6.140", std::nullopt)),
            std::make_pair("155.63.194.228:47036", Authority(std::nullopt, "155.63.194.228", "47036")),
            std::make_pair("101.15.93.234:21475", Authority(std::nullopt, "101.15.93.234", "21475")),
            std::make_pair("177.36.52.78:56948", Authority(std::nullopt, "177.36.52.78", "56948")),
            std::make_pair("pena.com", Authority(std::nullopt, "pena.com", std::nullopt)),
            std::make_pair("hernandez-reid.estes.harmon.com", Authority(std::nullopt, "hernandez-reid.estes.harmon.com", std::nullopt)),
            std::make_pair("177.28.61.252", Authority(std::nullopt, "177.28.61.252", std::nullopt)),
            std::make_pair("208.211.234.22:52177", Authority(std::nullopt, "208.211.234.22", "52177")),
            std::make_pair("land@222.226.4.28", Authority("land", "222.226.4.28", std::nullopt)),
            std::make_pair("148.168.247.196", Authority(std::nullopt, "148.168.247.196", std::nullopt)),
            std::make_pair("190.228.65.248", Authority(std::nullopt, "190.228.65.248", std::nullopt)),
            std::make_pair("cup@[d21d:258c:3bd:4af3:a44a:d24f:9e8e:47c5]", Authority("cup", "d21d:258c:3bd:4af3:a44a:d24f:9e8e:47c5", std::nullopt)),
            std::make_pair("71.226.240.166", Authority(std::nullopt, "71.226.240.166", std::nullopt)),
            std::make_pair("walk@zimmerman.saunders-owens.com", Authority("walk", "zimmerman.saunders-owens.com", std::nullopt)),
            std::make_pair("put@112.205.34.187", Authority("put", "112.205.34.187", std::nullopt)),
            std::make_pair("after@[b462:b319:f65f:a62b:4f7f:e7cc:d25a:2d7c]", Authority("after", "b462:b319:f65f:a62b:4f7f:e7cc:d25a:2d7c", std::nullopt)),
            std::make_pair("black@77.65.179.119:49687", Authority("black", "77.65.179.119", "49687")),
            std::make_pair("[e6cf:50cc:568e:5aac:4cb4:d651:cb15:64c5]", Authority(std::nullopt, "e6cf:50cc:568e:5aac:4cb4:d651:cb15:64c5", std::nullopt)),
            std::make_pair("183.12.209.160", Authority(std::nullopt, "183.12.209.160", std::nullopt)),
            std::make_pair("129.130.93.27:38028", Authority(std::nullopt, "129.130.93.27", "38028")),
            std::make_pair("baby@74.89.165.5:7297", Authority("baby", "74.89.165.5", "7297")),
            std::make_pair("budget@92.204.244.118:12863", Authority("budget", "92.204.244.118", "12863")),
            std::make_pair("others@16.223.201.229:15395", Authority("others", "16.223.201.229", "15395")),
            std::make_pair("item@[325f:1a72:13f5:e7bd:c05f:b5c6:638a:f1a8]", Authority("item", "325f:1a72:13f5:e7bd:c05f:b5c6:638a:f1a8", std::nullopt)),
            std::make_pair("now@154.90.189.39", Authority("now", "154.90.189.39", std::nullopt)),
            std::make_pair("case@[8932:48ae:ef84:fa07:3501:d98f:b9ed:a954]", Authority("case", "8932:48ae:ef84:fa07:3501:d98f:b9ed:a954", std::nullopt)),
            std::make_pair("39.175.198.88", Authority(std::nullopt, "39.175.198.88", std::nullopt)),
            std::make_pair("90.212.165.125", Authority(std::nullopt, "90.212.165.125", std::nullopt)),
            std::make_pair("199.127.41.116", Authority(std::nullopt, "199.127.41.116", std::nullopt))
        )
);

TEST_P(AuthorityTestingFixture, TestThatH16ParsingIsCorrect) {
    const auto& pair = GetParam();

    const auto& input = pair.first;
    const auto& expected_authority = pair.second;

    const auto& actual_authority = Authority::parse(input);
    EXPECT_EQ(actual_authority.value(), expected_authority);
}

class AuthoritySerialisationTestingFixture: public ::testing::TestWithParam<std::pair<Authority, std::string>> {};

INSTANTIATE_TEST_SUITE_P(
        AuthoritySerialisationTests,
        AuthoritySerialisationTestingFixture,
        ::testing::Values(
            std::make_pair(Authority("some", "103.218.46.129", "37324"), "some@103.218.46.129:37324"),
            std::make_pair(Authority(std::nullopt, "111.214.215.218", "54506"), "111.214.215.218:54506"),
            std::make_pair(Authority(std::nullopt, "147.11.235.42", "62447"), "147.11.235.42:62447"),
            std::make_pair(Authority(std::nullopt, "8e4d:b902:92d5:8f3:9ef7:f1dc:1218:d84a", std::nullopt), "[8e4d:b902:92d5:8f3:9ef7:f1dc:1218:d84a]"),
            std::make_pair(Authority(std::nullopt, "206.184.19.245", "46529"), "206.184.19.245:46529"),
            std::make_pair(Authority("court", "62f:a49e:5dfa:cca7:ccd8:55fe:8806:bf69", std::nullopt), "court@[62f:a49e:5dfa:cca7:ccd8:55fe:8806:bf69]"),
            std::make_pair(Authority("record", "wilson.frazier.harper.org", std::nullopt), "record@wilson.frazier.harper.org"),
            std::make_pair(Authority("just", "allen.mcguire.biz", std::nullopt), "just@allen.mcguire.biz"),
            std::make_pair(Authority("water", "186.190.32.211", std::nullopt), "water@186.190.32.211"),
            std::make_pair(Authority("notice", "cabrera.com", std::nullopt), "notice@cabrera.com"),
            std::make_pair(Authority("several", "8.26.145.207", std::nullopt), "several@8.26.145.207"),
            std::make_pair(Authority(std::nullopt, "e08b:cb59:5a3:4a76:bd46:860d:b5fe:e3b8", std::nullopt), "[e08b:cb59:5a3:4a76:bd46:860d:b5fe:e3b8]"),
            std::make_pair(Authority("security", "68.237.55.210", "40313"), "security@68.237.55.210:40313"),
            std::make_pair(Authority(std::nullopt, "kelley.lewis.com", std::nullopt), "kelley.lewis.com"),
            std::make_pair(Authority(std::nullopt, "86b8:36cd:d44a:bcf3:b347:3:bab8:8ec0", std::nullopt), "[86b8:36cd:d44a:bcf3:b347:3:bab8:8ec0]"),
            std::make_pair(Authority("establish", "143.158.94.161", "1848"), "establish@143.158.94.161:1848"),
            std::make_pair(Authority(std::nullopt, "83.234.161.14", std::nullopt), "83.234.161.14"),
            std::make_pair(Authority("explain", "pena.mcclure.com", std::nullopt), "explain@pena.mcclure.com"),
            std::make_pair(Authority("all", "c184:7b30:52c9:7ba8:507f:a089:832f:5a9f", std::nullopt), "all@[c184:7b30:52c9:7ba8:507f:a089:832f:5a9f]"),
            std::make_pair(Authority("risk", "ware.dunn.booth.com", std::nullopt), "risk@ware.dunn.booth.com"),
            std::make_pair(Authority("establish", "allen.ray.powers-franco.net", std::nullopt), "establish@allen.ray.powers-franco.net"),
            std::make_pair(Authority(std::nullopt, "188.183.6.140", std::nullopt), "188.183.6.140"),
            std::make_pair(Authority(std::nullopt, "155.63.194.228", "47036"), "155.63.194.228:47036"),
            std::make_pair(Authority(std::nullopt, "101.15.93.234", "21475"), "101.15.93.234:21475"),
            std::make_pair(Authority(std::nullopt, "177.36.52.78", "56948"), "177.36.52.78:56948"),
            std::make_pair(Authority(std::nullopt, "pena.com", std::nullopt), "pena.com"),
            std::make_pair(Authority(std::nullopt, "hernandez-reid.estes.harmon.com", std::nullopt), "hernandez-reid.estes.harmon.com"),
            std::make_pair(Authority(std::nullopt, "177.28.61.252", std::nullopt), "177.28.61.252"),
            std::make_pair(Authority(std::nullopt, "208.211.234.22", "52177"), "208.211.234.22:52177"),
            std::make_pair(Authority("land", "222.226.4.28", std::nullopt), "land@222.226.4.28"),
            std::make_pair(Authority(std::nullopt, "148.168.247.196", std::nullopt), "148.168.247.196"),
            std::make_pair(Authority(std::nullopt, "190.228.65.248", std::nullopt), "190.228.65.248"),
            std::make_pair(Authority("cup", "d21d:258c:3bd:4af3:a44a:d24f:9e8e:47c5", std::nullopt), "cup@[d21d:258c:3bd:4af3:a44a:d24f:9e8e:47c5]"),
            std::make_pair(Authority(std::nullopt, "71.226.240.166", std::nullopt), "71.226.240.166"),
            std::make_pair(Authority("walk", "zimmerman.saunders-owens.com", std::nullopt), "walk@zimmerman.saunders-owens.com"),
            std::make_pair(Authority("put", "112.205.34.187", std::nullopt), "put@112.205.34.187"),
            std::make_pair(Authority("after", "b462:b319:f65f:a62b:4f7f:e7cc:d25a:2d7c", std::nullopt), "after@[b462:b319:f65f:a62b:4f7f:e7cc:d25a:2d7c]"),
            std::make_pair(Authority("black", "77.65.179.119", "49687"), "black@77.65.179.119:49687"),
            std::make_pair(Authority(std::nullopt, "e6cf:50cc:568e:5aac:4cb4:d651:cb15:64c5", std::nullopt), "[e6cf:50cc:568e:5aac:4cb4:d651:cb15:64c5]"),
            std::make_pair(Authority(std::nullopt, "183.12.209.160", std::nullopt), "183.12.209.160"),
            std::make_pair(Authority(std::nullopt, "129.130.93.27", "38028"), "129.130.93.27:38028"),
            std::make_pair(Authority("baby", "74.89.165.5", "7297"), "baby@74.89.165.5:7297"),
            std::make_pair(Authority("budget", "92.204.244.118", "12863"), "budget@92.204.244.118:12863"),
            std::make_pair(Authority("others", "16.223.201.229", "15395"), "others@16.223.201.229:15395"),
            std::make_pair(Authority("item", "325f:1a72:13f5:e7bd:c05f:b5c6:638a:f1a8", std::nullopt), "item@[325f:1a72:13f5:e7bd:c05f:b5c6:638a:f1a8]"),
            std::make_pair(Authority("now", "154.90.189.39", std::nullopt), "now@154.90.189.39"),
            std::make_pair(Authority("case", "8932:48ae:ef84:fa07:3501:d98f:b9ed:a954", std::nullopt), "case@[8932:48ae:ef84:fa07:3501:d98f:b9ed:a954]"),
            std::make_pair(Authority(std::nullopt, "39.175.198.88", std::nullopt), "39.175.198.88"),
            std::make_pair(Authority(std::nullopt, "90.212.165.125", std::nullopt), "90.212.165.125"),
            std::make_pair(Authority(std::nullopt, "199.127.41.116", std::nullopt), "199.127.41.116")
        )
);

TEST_P(AuthoritySerialisationTestingFixture, TestSerialisationIsSuccessful) {
    const auto& pair = GetParam();

    const auto& authority = pair.first;
    const auto& expected_string = pair.second;

    const auto& actual_authority = Authority::parse(expected_string);
    EXPECT_EQ(actual_authority.value(), authority);
}
