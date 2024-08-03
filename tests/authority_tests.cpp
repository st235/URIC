#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "authority.h"

using uri::Authority;

TEST(UriAuthority, AuthoritiesWithSameContentAreEqual) {
    Authority a("www.mozila.com");
    Authority b("www.mozila.com", std::nullopt);
    EXPECT_EQ(a, b);
}

TEST(UriAuthority, AuthoritiesWithDifferentContentAreNotEqual) {
    Authority a("www.mozila.com", "80");
    Authority b("www.mozila.com", std::nullopt);
    EXPECT_NE(a, b);
}

class AuthorityTestingFixture: public ::testing::TestWithParam<std::pair<std::string, Authority>> {};

INSTANTIATE_TEST_SUITE_P(
        AuthorityParsingTests,
        AuthorityTestingFixture,
        ::testing::Values(
            std::make_pair("some@103.218.46.129:37324", Authority("103.218.46.129", "37324", "some")),
            std::make_pair("111.214.215.218:54506", Authority("111.214.215.218", "54506", std::nullopt)),
            std::make_pair("147.11.235.42:62447", Authority("147.11.235.42", "62447", std::nullopt)),
            std::make_pair("[8e4d:b902:92d5:8f3:9ef7:f1dc:1218:d84a]", Authority("8e4d:b902:92d5:8f3:9ef7:f1dc:1218:d84a", std::nullopt, std::nullopt, /* isHostIPLiteral= */ true)),
            std::make_pair("206.184.19.245:46529", Authority("206.184.19.245", "46529", std::nullopt)),
            std::make_pair("court@[62f:a49e:5dfa:cca7:ccd8:55fe:8806:bf69]", Authority("62f:a49e:5dfa:cca7:ccd8:55fe:8806:bf69", std::nullopt, "court", /* isHostIPLiteral= */ true)),
            std::make_pair("record@wilson.frazier.harper.org", Authority("wilson.frazier.harper.org", std::nullopt, "record")),
            std::make_pair("just@allen.mcguire.biz", Authority("allen.mcguire.biz", std::nullopt, "just")),
            std::make_pair("water@186.190.32.211", Authority("186.190.32.211", std::nullopt, "water")),
            std::make_pair("notice@cabrera.com", Authority("cabrera.com", std::nullopt, "notice")),
            std::make_pair("several@8.26.145.207", Authority("8.26.145.207", std::nullopt, "several")),
            std::make_pair("[e08b:cb59:5a3:4a76:bd46:860d:b5fe:e3b8]", Authority("e08b:cb59:5a3:4a76:bd46:860d:b5fe:e3b8", std::nullopt, std::nullopt, /* isHostIPLiteral= */ true)),
            std::make_pair("security@68.237.55.210:40313", Authority("68.237.55.210", "40313", "security")),
            std::make_pair("kelley.lewis.com", Authority("kelley.lewis.com", std::nullopt, std::nullopt)),
            std::make_pair("[86b8:36cd:d44a:bcf3:b347:3:bab8:8ec0]", Authority("86b8:36cd:d44a:bcf3:b347:3:bab8:8ec0", std::nullopt, std::nullopt, /* isHostIPLiteral= */ true)),
            std::make_pair("establish@143.158.94.161:1848", Authority("143.158.94.161", "1848", "establish")),
            std::make_pair("83.234.161.14", Authority("83.234.161.14", std::nullopt, std::nullopt)),
            std::make_pair("explain@pena.mcclure.com", Authority("pena.mcclure.com", std::nullopt, "explain")),
            std::make_pair("all@[c184:7b30:52c9:7ba8:507f:a089:832f:5a9f]", Authority("c184:7b30:52c9:7ba8:507f:a089:832f:5a9f", std::nullopt, "all", /* isHostIPLiteral= */ true)),
            std::make_pair("risk@ware.dunn.booth.com", Authority("ware.dunn.booth.com", std::nullopt, "risk")),
            std::make_pair("establish@allen.ray.powers-franco.net", Authority("allen.ray.powers-franco.net", std::nullopt, "establish")),
            std::make_pair("188.183.6.140", Authority("188.183.6.140", std::nullopt, std::nullopt)),
            std::make_pair("155.63.194.228:47036", Authority("155.63.194.228", "47036", std::nullopt)),
            std::make_pair("101.15.93.234:21475", Authority("101.15.93.234", "21475", std::nullopt)),
            std::make_pair("177.36.52.78:56948", Authority("177.36.52.78", "56948", std::nullopt)),
            std::make_pair("pena.com", Authority("pena.com", std::nullopt, std::nullopt)),
            std::make_pair("hernandez-reid.estes.harmon.com", Authority("hernandez-reid.estes.harmon.com", std::nullopt, std::nullopt)),
            std::make_pair("177.28.61.252", Authority("177.28.61.252", std::nullopt, std::nullopt)),
            std::make_pair("208.211.234.22:52177", Authority("208.211.234.22", "52177", std::nullopt)),
            std::make_pair("land@222.226.4.28", Authority("222.226.4.28", std::nullopt, "land")),
            std::make_pair("148.168.247.196", Authority("148.168.247.196", std::nullopt, std::nullopt)),
            std::make_pair("190.228.65.248", Authority("190.228.65.248", std::nullopt, std::nullopt)),
            std::make_pair("cup@[d21d:258c:3bd:4af3:a44a:d24f:9e8e:47c5]", Authority("d21d:258c:3bd:4af3:a44a:d24f:9e8e:47c5", std::nullopt, "cup", /* isHostIPLiteral= */ true)),
            std::make_pair("71.226.240.166", Authority("71.226.240.166", std::nullopt, std::nullopt)),
            std::make_pair("walk@zimmerman.saunders-owens.com", Authority("zimmerman.saunders-owens.com", std::nullopt, "walk")),
            std::make_pair("put@112.205.34.187", Authority("112.205.34.187", std::nullopt, "put")),
            std::make_pair("after@[b462:b319:f65f:a62b:4f7f:e7cc:d25a:2d7c]", Authority("b462:b319:f65f:a62b:4f7f:e7cc:d25a:2d7c", std::nullopt, "after", /* isHostIPLiteral= */ true)),
            std::make_pair("black@77.65.179.119:49687", Authority("77.65.179.119", "49687", "black")),
            std::make_pair("[e6cf:50cc:568e:5aac:4cb4:d651:cb15:64c5]", Authority("e6cf:50cc:568e:5aac:4cb4:d651:cb15:64c5", std::nullopt, std::nullopt, /* isHostIPLiteral= */ true)),
            std::make_pair("183.12.209.160", Authority("183.12.209.160", std::nullopt, std::nullopt)),
            std::make_pair("129.130.93.27:38028", Authority("129.130.93.27", "38028", std::nullopt)),
            std::make_pair("baby@74.89.165.5:7297", Authority("74.89.165.5", "7297", "baby")),
            std::make_pair("budget@92.204.244.118:12863", Authority("92.204.244.118", "12863", "budget")),
            std::make_pair("others@16.223.201.229:15395", Authority("16.223.201.229", "15395", "others")),
            std::make_pair("item@[325f:1a72:13f5:e7bd:c05f:b5c6:638a:f1a8]", Authority("325f:1a72:13f5:e7bd:c05f:b5c6:638a:f1a8", std::nullopt, "item", /* isHostIPLiteral= */ true)),
            std::make_pair("now@154.90.189.39", Authority("154.90.189.39", std::nullopt, "now")),
            std::make_pair("case@[8932:48ae:ef84:fa07:3501:d98f:b9ed:a954]", Authority("8932:48ae:ef84:fa07:3501:d98f:b9ed:a954", std::nullopt, "case", /* isHostIPLiteral= */ true)),
            std::make_pair("39.175.198.88", Authority("39.175.198.88", std::nullopt, std::nullopt)),
            std::make_pair("90.212.165.125", Authority("90.212.165.125", std::nullopt, std::nullopt)),
            std::make_pair("199.127.41.116", Authority("199.127.41.116", std::nullopt, std::nullopt))
        )
);

TEST_P(AuthorityTestingFixture, TestThatH16ParsingIsCorrect) {
    const auto& pair = GetParam();

    const auto& input = pair.first;
    const auto& expected_authority = pair.second;

    const auto& actual_authority = Authority::parse(input);
    EXPECT_EQ(actual_authority.value(), expected_authority);
}

// class AuthoritySerialisationTestingFixture: public ::testing::TestWithParam<std::pair<Authority, std::string>> {};

// INSTANTIATE_TEST_SUITE_P(
//         AuthoritySerialisationTests,
//         AuthoritySerialisationTestingFixture,
//         ::testing::Values(
//             std::make_pair(Authority("103.218.46.129", "37324", "some"), "some@103.218.46.129:37324"),
//             std::make_pair(Authority("111.214.215.218", "54506", std::nullopt), "111.214.215.218:54506"),
//             std::make_pair(Authority("147.11.235.42", "62447", std::nullopt), "147.11.235.42:62447"),
//             std::make_pair(Authority("8e4d:b902:92d5:8f3:9ef7:f1dc:1218:d84a", std::nullopt, std::nullopt), "[8e4d:b902:92d5:8f3:9ef7:f1dc:1218:d84a]"),
//             std::make_pair(Authority("206.184.19.245", "46529", std::nullopt), "206.184.19.245:46529"),
//             std::make_pair(Authority("62f:a49e:5dfa:cca7:ccd8:55fe:8806:bf69", std::nullopt, "court"), "court@[62f:a49e:5dfa:cca7:ccd8:55fe:8806:bf69]"),
//             std::make_pair(Authority("wilson.frazier.harper.org", std::nullopt, "record"), "record@wilson.frazier.harper.org"),
//             std::make_pair(Authority("allen.mcguire.biz", std::nullopt, "just"), "just@allen.mcguire.biz"),
//             std::make_pair(Authority("186.190.32.211", std::nullopt, "water"), "water@186.190.32.211"),
//             std::make_pair(Authority("cabrera.com", std::nullopt, "notice"), "notice@cabrera.com"),
//             std::make_pair(Authority("8.26.145.207", std::nullopt, "several"), "several@8.26.145.207"),
//             std::make_pair(Authority("e08b:cb59:5a3:4a76:bd46:860d:b5fe:e3b8", std::nullopt, std::nullopt), "[e08b:cb59:5a3:4a76:bd46:860d:b5fe:e3b8]"),
//             std::make_pair(Authority("68.237.55.210", "40313", "security"), "security@68.237.55.210:40313"),
//             std::make_pair(Authority("kelley.lewis.com", std::nullopt, std::nullopt), "kelley.lewis.com"),
//             std::make_pair(Authority("86b8:36cd:d44a:bcf3:b347:3:bab8:8ec0", std::nullopt, std::nullopt), "[86b8:36cd:d44a:bcf3:b347:3:bab8:8ec0]"),
//             std::make_pair(Authority("143.158.94.161", "1848", "establish"), "establish@143.158.94.161:1848"),
//             std::make_pair(Authority("83.234.161.14", std::nullopt, std::nullopt), "83.234.161.14"),
//             std::make_pair(Authority("pena.mcclure.com", std::nullopt, "explain"), "explain@pena.mcclure.com"),
//             std::make_pair(Authority("c184:7b30:52c9:7ba8:507f:a089:832f:5a9f", std::nullopt, "all"), "all@[c184:7b30:52c9:7ba8:507f:a089:832f:5a9f]"),
//             std::make_pair(Authority("ware.dunn.booth.com", std::nullopt, "risk"), "risk@ware.dunn.booth.com"),
//             std::make_pair(Authority("allen.ray.powers-franco.net", std::nullopt, "establish"), "establish@allen.ray.powers-franco.net"),
//             std::make_pair(Authority("188.183.6.140", std::nullopt, std::nullopt), "188.183.6.140"),
//             std::make_pair(Authority("155.63.194.228", "47036", std::nullopt), "155.63.194.228:47036"),
//             std::make_pair(Authority("101.15.93.234", "21475", std::nullopt), "101.15.93.234:21475"),
//             std::make_pair(Authority("177.36.52.78", "56948", std::nullopt), "177.36.52.78:56948"),
//             std::make_pair(Authority("pena.com", std::nullopt, std::nullopt), "pena.com"),
//             std::make_pair(Authority("hernandez-reid.estes.harmon.com", std::nullopt, std::nullopt), "hernandez-reid.estes.harmon.com"),
//             std::make_pair(Authority("177.28.61.252", std::nullopt, std::nullopt), "177.28.61.252"),
//             std::make_pair(Authority("208.211.234.22", "52177", std::nullopt), "208.211.234.22:52177"),
//             std::make_pair(Authority("222.226.4.28", std::nullopt, "land"), "land@222.226.4.28"),
//             std::make_pair(Authority("148.168.247.196", std::nullopt, std::nullopt), "148.168.247.196"),
//             std::make_pair(Authority("190.228.65.248", std::nullopt, std::nullopt), "190.228.65.248"),
//             std::make_pair(Authority("d21d:258c:3bd:4af3:a44a:d24f:9e8e:47c5", std::nullopt, "cup"), "cup@[d21d:258c:3bd:4af3:a44a:d24f:9e8e:47c5]"),
//             std::make_pair(Authority("71.226.240.166", std::nullopt, std::nullopt), "71.226.240.166"),
//             std::make_pair(Authority("zimmerman.saunders-owens.com", std::nullopt, "walk"), "walk@zimmerman.saunders-owens.com"),
//             std::make_pair(Authority("112.205.34.187", std::nullopt, "put"), "put@112.205.34.187"),
//             std::make_pair(Authority("b462:b319:f65f:a62b:4f7f:e7cc:d25a:2d7c", std::nullopt, "after"), "after@[b462:b319:f65f:a62b:4f7f:e7cc:d25a:2d7c]"),
//             std::make_pair(Authority("77.65.179.119", "49687", "black"), "black@77.65.179.119:49687"),
//             std::make_pair(Authority("e6cf:50cc:568e:5aac:4cb4:d651:cb15:64c5", std::nullopt, std::nullopt), "[e6cf:50cc:568e:5aac:4cb4:d651:cb15:64c5]"),
//             std::make_pair(Authority("183.12.209.160", std::nullopt, std::nullopt), "183.12.209.160"),
//             std::make_pair(Authority("129.130.93.27", "38028", std::nullopt), "129.130.93.27:38028"),
//             std::make_pair(Authority("74.89.165.5", "7297", "baby"), "baby@74.89.165.5:7297"),
//             std::make_pair(Authority("92.204.244.118", "12863", "budget"), "budget@92.204.244.118:12863"),
//             std::make_pair(Authority("16.223.201.229", "15395", "others"), "others@16.223.201.229:15395"),
//             std::make_pair(Authority("325f:1a72:13f5:e7bd:c05f:b5c6:638a:f1a8", std::nullopt, "item"), "item@[325f:1a72:13f5:e7bd:c05f:b5c6:638a:f1a8]"),
//             std::make_pair(Authority("154.90.189.39", std::nullopt, "now"), "now@154.90.189.39"),
//             std::make_pair(Authority("8932:48ae:ef84:fa07:3501:d98f:b9ed:a954", std::nullopt, "case"), "case@[8932:48ae:ef84:fa07:3501:d98f:b9ed:a954]"),
//             std::make_pair(Authority("39.175.198.88", std::nullopt, std::nullopt), "39.175.198.88"),
//             std::make_pair(Authority("90.212.165.125", std::nullopt, std::nullopt), "90.212.165.125"),
//             std::make_pair(Authority("199.127.41.116", std::nullopt, std::nullopt), "199.127.41.116")
//         )
// );

// TEST_P(AuthoritySerialisationTestingFixture, TestSerialisationIsSuccessful) {
//     const auto& pair = GetParam();

//     const auto& authority = pair.first;
//     const auto& expected_string = pair.second;

//     const auto& actual_authority = Authority::parse(expected_string);
//     EXPECT_EQ(actual_authority.value(), authority);
// }
