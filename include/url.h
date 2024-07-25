#ifndef __URIC_URL_H__
#define __URIC_URL_H__

#include <optional>
#include <string>
#include <sstream>
#include <unordered_map>

#include "authority.h"
#include "uri.h"

namespace {

using optional_string_t = std::optional<std::string>;

} // namespace

namespace uri {

constexpr char kQueryItemsSeparator = '&';
constexpr char kQueryKeyValueSeparator = '=';

class Url {
public:
    static std::optional<Url> parse(const std::string& input) {
        const auto& uri_opt = Uri::parse(input);

        if (!uri_opt) {
            return std::nullopt;
        }

        return Url(uri_opt.value());
    }

    static std::optional<Url> fromParts(const std::string& raw_path,
                                        const optional_string_t& raw_scheme,
                                        const optional_string_t& raw_authority,
                                        const optional_string_t& raw_query,
                                        const optional_string_t& raw_fragment) {
        const auto& uri_opt = Uri::fromParts(raw_path, raw_scheme, raw_authority, raw_query, raw_fragment);

        if (!uri_opt) {
            return std::nullopt;
        }

        return Url(uri_opt.value());
    }

    explicit Url(const Uri& uri) noexcept:
        _uri(uri) {
        // Empty on purpose.
    }

    explicit Url(const std::string& path,
                 const optional_string_t& query = std::nullopt,
                 const optional_string_t& fragment = std::nullopt) noexcept:
        _uri(path, query, fragment) {
        // Empty on purpose.
    }

    Url(const optional_string_t& scheme,
        const std::optional<Authority>& authority,
        const std::string& path,
        const optional_string_t& query = std::nullopt,
        const optional_string_t& fragment = std::nullopt) noexcept:
        _uri(scheme, authority, path, query, fragment) {
        // Empty on purpose.
    }

    Url(const Url& that) = default;
    Url& operator=(const Url& that) = default;
    Url(Url&& that) = default;
    Url& operator=(Url&& that) = default;

    bool operator==(const Url& that) const {
        return (_uri == that._uri);
    }

    bool operator!=(const Url& that) const {
        return !operator==(that);
    }

    inline const optional_string_t& getScheme() const {
        return _uri.getScheme();
    }

    inline const std::optional<Authority>& getAuthority() const {
        return _uri.getAuthority();
    }

    inline const std::string& getPath() const {
        return _uri.getPath();
    }

    inline const optional_string_t& getRawQuery() const {
        return _uri.getQuery();
    }

    std::unordered_map<std::string, std::string> getQuery() const {
        std::unordered_map<std::string, std::string> queries;
        const auto& raw_query_opt = getRawQuery();

        if (!raw_query_opt) {
            return std::unordered_map<std::string, std::string>();
        }

        const auto& raw_query = raw_query_opt.value();

        size_t i = 0;
        bool keyValueSeparatorFound = false;
        std::stringstream keyBuffer;
        std::stringstream valueBuffer;
        while (i < raw_query.length()) {
            if (raw_query[i] == kQueryItemsSeparator) {
                const auto& key = keyBuffer.str();
                const auto& value = valueBuffer.str();

                if (keyValueSeparatorFound || key.length() > 0) {
                    queries[key] = value;
                }

                keyValueSeparatorFound = false;
                keyBuffer.str("");
                valueBuffer.str("");

                i++;
                continue;
            }

            if (!keyValueSeparatorFound && raw_query[i] == kQueryKeyValueSeparator) {
                keyValueSeparatorFound = true;

                i++;
                continue;
            }

            if (!keyValueSeparatorFound) {
                keyBuffer << raw_query[i];
            } else {
                valueBuffer << raw_query[i];
            }

            i++;
        }

        const auto& key = keyBuffer.str();
        const auto& value = valueBuffer.str();

        if (keyValueSeparatorFound || key.length() > 0) {
            queries[key] = value;
        }

        return queries;
    }

    inline const optional_string_t& getFragment() const {
        return _uri.getFragment();
    }

    ~Url() = default;

private:
    Uri _uri;
};

} // namespace uri

#endif // __URIC_URL_H__
