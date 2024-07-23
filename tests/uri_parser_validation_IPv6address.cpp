#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "token_reader.h"
#include "uri_parser.h"

using ValidationData = std::pair<std::string, bool>;

class UriParserIPv6addressTestingFixture: public ::testing::TestWithParam<ValidationData> {};

INSTANTIATE_TEST_SUITE_P(
        UriParserIPv6addressTests,
        UriParserIPv6addressTestingFixture,
        ::testing::Values(
            std::make_pair("", false),
            std::make_pair("abcsd", false),
            std::make_pair(":::::", false),
            std::make_pair(":1275:ed01:0afb:1b32:76b5::", false),
            std::make_pair(":ffff:1275:ed01:0afb:1b32:76b5::", false),
            std::make_pair("1acd:ffff:1275:ed01:0afb:1b32:76b5::1b", false),
            std::make_pair("::81e31a8f:2acf", false),
            std::make_pair("zzzz::81e3:1a8f:2acf", false),
            std::make_pair("abcd::9a37:0012:eb41:1241:81e3:1a8f:2acf", false),
            std::make_pair("abcd::9a37:0012:eb41:1241:81e3:67.21.0.33", false),

            //                            6( h16 ":" ) ls32
            std::make_pair("16ca:fb0e:d992:5544:75d2:4d2d:3e2f:b43a", true),
            std::make_pair("7fac:e5e4:99b8:5fb8:e4e2:fb7a:3275:42c7", true),
            std::make_pair("49d7:476c:e0bc:b84c:8e80:092e:5540:0e98", true),
            std::make_pair("11ab:ea54:ba9b:d4ee:31a3:f488:2f22:aa2c", true),
            std::make_pair("4e69:c6f8:1ecb:5d68:858f:2c4b:660c:7e2d", true),
            std::make_pair("7f99:346d:e9d9:e70d:6f6a:1b66:8e76:b666", true),
            std::make_pair("067e:26f9:b6e7:1342:014f:a6aa:ef67:a322", true),
            std::make_pair("b264:fb81:b220:e908:5d29:2993:5743:83ea", true),
            std::make_pair("724e:da79:3a84:4472:8f68:0ce0:6f0f:018f", true),
            std::make_pair("69c6:a159:a166:3f83:3f89:d6ff:f113:5027", true),
            std::make_pair("4788:3213:bb03:468f:59bd:ac0c:c4be:fb94", true),
            std::make_pair("c1e8:97c3:e927:d50c:53b7:3d64:59c1:a87d", true),
            std::make_pair("ce77:8b33:1054:5071:9cab:1123:33a4:be00", true),
            std::make_pair("7897:c6d5:fef9:011c:3d32:63af:abae:6bc0", true),
            std::make_pair("7408:00da:91fc:8552:5a21:2962:b746:d090", true),
            std::make_pair("0d47:8745:ba13:2b1f:83b5:7286:e323:bdaf", true),
            std::make_pair("cf26:0fd8:b68f:7a97:965f:c86b:1d2e:46ba", true),
            std::make_pair("3053:7236:f0b1:4783:ed02:3641:9daf:1f9b", true),
            std::make_pair("a628:da90:65bb:b1c2:155b:776e:5189:22ed", true),
            std::make_pair("1fd2:23b4:4c96:1bed:4c89:3f5c:98ed:0494", true),
            std::make_pair("9856:a4a7:a6e6:14bc:4e1a:1838:57fb:d8b3", true),
            std::make_pair("fad5:33fd:65a5:fc28:9fe1:7788:808f:9c6e", true),
            std::make_pair("2892:7591:bda8:367d:a3fe:8441:e6db:42cf", true),
            std::make_pair("1fab:ee65:2865:9377:9183:ca4b:64c8:da4d", true),
            std::make_pair("a2de:e3ba:9e2f:c0f5:e615:9da2:c154:7469", true),
            std::make_pair("c5f4:689d:0fad:04de:e213:40f6:b416:353d", true),
            std::make_pair("77fb:f5c5:2587:e962:bdc0:44fb:3d18:8ae0", true),
            std::make_pair("b31e:e443:6fa2:63b1:1a2d:502b:dae7:2c01", true),
            std::make_pair("ffdc:db0f:8c6f:01b5:47bd:b979:f0d9:2c92", true),
            std::make_pair("f591:fb85:2d26:cd68:8c15:e1f5:e48e:5b53", true),
            std::make_pair("203f:e4ea:0bbe:216f:0766:00cf:5cf9:5659", true),
            std::make_pair("cd85:d212:420c:d97f:307f:52a4:07a6:ff96", true),
            std::make_pair("a304:2b21:d00a:e41f:9827:f648:85b5:a01a", true),
            std::make_pair("5710:a8da:b6b2:f843:eb01:df60:8e01:df38", true),
            std::make_pair("4eb6:7ae3:7ac1:113a:355e:8e79:dfbe:e350", true),
            std::make_pair("825d:a836:4ead:7945:2860:2b57:da8a:f106", true),
            std::make_pair("2e7c:c332:401f:e445:2ae5:7c5d:6948:6e3f", true),
            std::make_pair("1a43:41d1:5105:94e0:f9bf:4899:3658:9b40", true),
            std::make_pair("c400:2acc:7216:e5b2:bbf0:dcb4:d6f8:b934", true),
            std::make_pair("987d:1e66:4fb0:90de:fc7c:7fc1:e9b2:f4c8", true),
            std::make_pair("10e0:bb63:34de:ec5b:b024:b205:0350:753b", true),
            std::make_pair("adef:cc24:8b52:ce9d:1126:40d9:4071:0774", true),
            std::make_pair("38cf:afb1:45b5:e56b:93db:9f02:77a6:0ebe", true),
            std::make_pair("88a3:253b:29ad:69fe:60be:8959:477f:c1a9", true),
            std::make_pair("6be9:ecf1:5bc8:31db:948d:b520:372b:ad0c", true),
            std::make_pair("6e2a:5395:97d3:8bbd:dbbe:8052:8819:d258", true),
            std::make_pair("c515:5c5d:67ee:bf93:44d6:6f91:e07c:05ba", true),
            std::make_pair("4c33:e25a:9d59:b006:36de:df2e:6a8a:828b", true),
            std::make_pair("4434:d8d2:0a5c:492a:7be1:5173:182d:bc85", true),
            std::make_pair("d55e:1b6e:5d6d:a7ca:67e7:0846:5214:222a", true),
            std::make_pair("1679:d50a:ce5e:d4c8:d958:ad4b:cab0:4778", true),
            std::make_pair("b0f8:b4d8:c6c9:ddda:ba92:b35e:ac57:ddec", true),
            std::make_pair("c28d:c218:1b41:5e39:b7cb:a2c5:7559:b1de", true),
            std::make_pair("2349:6e74:57ac:f7f1:fbca:a671:7c2e:fa7d", true),
            std::make_pair("6229:5218:5c83:3c8f:c0fc:13c4:46ad:fe46", true),
            std::make_pair("90cc:cf6a:d3c8:1485:053a:1dbe:51b4:1e95", true),
            std::make_pair("ee3d:2605:09f0:285c:ee61:3db3:33f1:19b8", true),
            std::make_pair("2224:872e:b80a:75b3:a42e:2dd4:98d1:1fcc", true),
            std::make_pair("6bb8:f62c:4b2c:091d:5fd2:3932:56fb:a548", true),
            std::make_pair("679c:4d3e:0076:9b53:f676:2dd9:8d64:6b80", true),
            std::make_pair("0949:7bf8:c585:c775:2a3b:6188:0d1c:36c1", true),
            std::make_pair("6915:69c7:6446:bbc4:4bd3:e941:819f:a0c0", true),
            std::make_pair("d562:7b4c:8bd8:56b1:572b:c5a5:93d6:e432", true),
            std::make_pair("5f23:bfc2:d6c5:0221:d11e:61a1:cc5e:9033", true),
            std::make_pair("2f4c:0dc0:04bb:e461:98eb:9c19:b6c8:93bc", true),
            std::make_pair("714c:252b:e83a:4af5:7170:9c3c:4735:d04d", true),
            std::make_pair("788d:ee34:9be6:ef2e:a242:9aef:9d99:f516", true),
            std::make_pair("9558:cde1:46eb:641f:f61d:b9a7:4bb4:b316", true),
            std::make_pair("690c:1100:12b8:c32c:fc75:80f4:44d0:2b10", true),
            std::make_pair("de68:7797:9224:257c:c424:59eb:5fce:031d", true),
            std::make_pair("d5b5:a2eb:fa86:42d6:d8dc:2d30:6717:1468", true),
            std::make_pair("795b:970a:3324:cc73:0d9f:1dcc:5236:38db", true),
            std::make_pair("e2a1:e1a6:01cd:1ff0:700e:e33c:1db5:7220", true),
            std::make_pair("785c:b999:0328:6f89:a60b:5289:d305:6b1e", true),
            std::make_pair("7045:dbe1:0833:05ed:4666:9801:1577:28a2", true),
            std::make_pair("c5d3:c85d:10ff:6322:4762:1a70:e2ea:af34", true),
            std::make_pair("0438:e9ab:ff8d:e141:fc5b:daf7:0188:10ce", true),
            std::make_pair("d666:5079:eef3:1cda:94e3:80af:b448:e84c", true),
            std::make_pair("fef7:db1b:7130:74a9:9859:5f06:5c45:fef7", true),
            std::make_pair("511d:3f72:f1af:99d5:b8ec:8f2e:b800:2e8b", true),
            std::make_pair("1ec8:6c4e:aa2f:6872:485a:c2a7:fe69:df0c", true),
            std::make_pair("91b7:703f:c6b3:a933:8da5:23e0:dbc7:6ba5", true),
            std::make_pair("ec37:1ff6:0a4c:1dfc:2c03:89d5:1763:1bde", true),
            std::make_pair("013d:7d4b:1c34:769e:9039:0893:3f67:d089", true),
            std::make_pair("a341:6453:ce62:485d:129a:20d3:3202:807c", true),
            std::make_pair("7a65:5995:ef9c:dce6:2a87:523f:a33c:f6e8", true),
            std::make_pair("06f6:2eaf:09bf:9c01:7a0b:7c29:ab05:783b", true),
            std::make_pair("79b7:1f7b:751a:0fe8:602b:2c82:a947:95df", true),
            std::make_pair("fe74:b54d:aeb7:d74e:9482:0617:5539:0720", true),
            std::make_pair("5460:833b:f47c:6afa:72ca:aa93:87aa:82de", true),
            std::make_pair("a5f7:512d:45d9:d935:6d56:e3ec:0311:45bc", true),
            std::make_pair("1d37:c643:22ab:db83:a18d:3719:f6d1:a6ff", true),
            std::make_pair("a7a1:41b8:727b:44bf:f129:d20e:f4ec:ceb9", true),
            std::make_pair("51ff:db46:8a43:6f68:3299:cbd5:6e09:b319", true),
            std::make_pair("7b96:05a7:ab7f:945a:2abb:fbee:90b3:bd94", true),
            std::make_pair("d607:d7e0:ca22:6366:deb6:14d1:c6c3:432e", true),
            std::make_pair("b86e:7275:8946:15f7:7c42:5434:d16d:c113", true),
            std::make_pair("75c8:ef56:8ab9:eb56:5306:c6c1:b619:fe89", true),
            std::make_pair("e93d:7ed6:2ee6:cb9b:8ae0:51ed:28de:b5cc", true),
            std::make_pair("76b5:ddc0:2669:50ac:89b9:7508:347d:cef6", true),

            //                       "::" 5( h16 ":" ) ls32
            std::make_pair("::9a37:0012:eb41:1241:81e3:1a8f:2acf", true),

            // [               h16 ] "::" 4( h16 ":" ) ls32
            std::make_pair("2e3c::0012:eb41:1241:81e3:1.255.0.12", true),
            std::make_pair("2e3c::0012:eb41:1241:81e3:1a8f:2acf", true),
            std::make_pair("::0012:eb41:1241:81e3:1a8f:2acf", true),

            // [ *1( h16 ":" ) h16 ] "::" 3( h16 ":" ) ls32
            std::make_pair("ea3c:1f22::eb41:1241:81e3:1a8f:2acf", true),
            std::make_pair("1f22::eb41:1241:81e3:1a8f:2acf", true),
            std::make_pair("::eb41:1241:81e3:1a8f:2acf", true),

            // [ *2( h16 ":" ) h16 ] "::" 2( h16 ":" ) ls32
            std::make_pair("19bd:00fc:1a99::1241:81e3:1a8f:2acf", true),
            std::make_pair("00fc:1a99::1241:81e3:1a8f:2acf", true),
            std::make_pair("1a99::1241:81e3:1a8f:2acf", true),
            std::make_pair("::1241:81e3:1a8f:2acf", true),

            // [ *3( h16 ":" ) h16 ] "::"    h16 ":"   ls32
            std::make_pair("6901:bb1c:119a:7a26::81e3:1a8f:2acf", true),
            std::make_pair("bb1c:119a:7a26::81e3:1a8f:2acf", true),
            std::make_pair("119a:7a26::81e3:1a8f:2acf", true),
            std::make_pair("7a26::81e3:1a8f:2acf", true),
            std::make_pair("::81e3:1a8f:2acf", true),

            // [ *4( h16 ":" ) h16 ] "::"              ls32
            std::make_pair("1:2271:ab23:9812:2c1e::1.1.1.1", true),
            std::make_pair("1:2271:ab23:9812:2c1e::1a8f:2acf", true),
            std::make_pair("2271:ab23:9812:2c1e::1a8f:2acf", true),
            std::make_pair("ab23:9812:2c1e::1a8f:2acf", true),
            std::make_pair("9812:2c1e::1a8f:2acf", true),
            std::make_pair("2c1e::1a8f:2acf", true),
            std::make_pair("::1a8f:2acf", true),

            // [ *5( h16 ":" ) h16 ] "::"              h16
            std::make_pair("09ab:efab:ffac:bd1a:1a71:8fcd::1a8f", true),
            std::make_pair("efab:ffac:bd1a:1a71:8fcd::1a8f", true),
            std::make_pair("ffac:bd1a:1a71:8fcd::1a8f", true),
            std::make_pair("bd1a:1a71:8fcd::1a8f", true),
            std::make_pair("1a71:8fcd::1a8f", true),
            std::make_pair("8fcd::1a8f", true),
            std::make_pair("::1a8f", true),

            // [ *6( h16 ":" ) h16 ] "::"
            std::make_pair("1b27:ffff:1275:ed01:0afb:1b32:76b5::", true),
            std::make_pair("ffff:1275:ed01:0afb:1b32:76b5::", true),
            std::make_pair("1275:ed01:0afb:1b32:76b5::", true),
            std::make_pair("ed01:0afb:1b32:76b5::", true),
            std::make_pair("0afb:1b32:76b5::", true),
            std::make_pair("1b32:76b5::", true),
            std::make_pair("1b3:76b5::", true),
            std::make_pair("76b5::", true),
            std::make_pair("76A::", true),
            std::make_pair("76::", true),
            std::make_pair("::", true)
        )
);

TEST_P(UriParserIPv6addressTestingFixture, TestThatIPv6addressParsingIsCorrect) {
    const auto& pair = GetParam();

    const auto& text = pair.first;
    const auto& expected_result = pair.second;

    uri::__internal::TokenReader reader(text);
    EXPECT_EQ(uri::__internal::IPv6address(reader) && !reader.hasNext(), expected_result);
}
