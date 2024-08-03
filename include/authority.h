#ifndef __URIC_AUTHORITY_H__
#define __URIC_AUTHORITY_H__

#include <iostream>
#include <optional>
#include <string>

namespace {

using optional_string_t = std::optional<std::string>;

constexpr char kUserInfoSeparator = '@';
constexpr char kPortSeparator = ':';
constexpr char kIPLiteralBegin = '[';
constexpr char kIPLiteralEnd = ']';

} // namespace

namespace uri {

class Authority {
public:
    static std::optional<Authority> parse(const std::string& input);

    Authority(const std::string& host,
              const optional_string_t& port = std::nullopt,
              const optional_string_t& userInfo = std::nullopt,
              bool is_host_ip_literal = false) noexcept:
        _userInfo(userInfo),
        _host(host),
        _is_host_ip_literal(is_host_ip_literal),
        _port(port) {
        // Empty on purpose.
    }

    Authority(const Authority& that) noexcept = default;
    Authority& operator=(const Authority& that) noexcept = default;
    Authority(Authority&& that) noexcept = default;
    Authority& operator=(Authority&& that) noexcept = default;

    bool operator==(const Authority& that) const {
        return (_userInfo == that._userInfo)
        && (_host == that._host)
        && (_is_host_ip_literal == that._is_host_ip_literal)
        && (_port == that._port);
    }

    bool operator!=(const Authority& that) const {
        return !operator==(that);
    }

    friend std::ostream& operator<<(std::ostream& stream, const Authority& that) { 
        if (that._userInfo) {
            stream << that._userInfo.value() << kUserInfoSeparator;
        }

        if (that._is_host_ip_literal) {
            stream << kIPLiteralBegin;
        }

        stream << that._host;

        if (that._is_host_ip_literal) {
            stream << kIPLiteralEnd;
        }

        if (that._port) {
            stream << kPortSeparator << that._port.value();
        }

        return stream;
    }

    inline const optional_string_t& getUserInfo() const {
        return _userInfo;
    }

    inline const std::string& getHost() const {
        return _host;
    }

    inline const optional_string_t& getPort() const {
        return _port;
    }

    ~Authority() = default;

private:
    optional_string_t _userInfo;
    std::string _host;
    bool _is_host_ip_literal;
    optional_string_t _port;
};

} // namespace uri

#endif // __URIC_AUTHORITY_H__
