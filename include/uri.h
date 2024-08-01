#ifndef __URIC_URI_H__
#define __URIC_URI_H__

#include <optional>
#include <string>

#include "authority.h"

namespace {

using optional_string_t = std::optional<std::string>;

} // namespace

namespace uri {

class Uri {
public:
    static std::optional<Uri> parse(const std::string& input);
    static std::optional<Uri> fromParts(const std::string& raw_path,
                                        const optional_string_t& raw_scheme,
                                        const optional_string_t& raw_authority,
                                        const optional_string_t& raw_query,
                                        const optional_string_t& raw_fragment);
    static std::string normalisePath(const std::string& path);

    explicit Uri(const std::string& path,
                 const optional_string_t& query = std::nullopt,
                 const optional_string_t& fragment = std::nullopt) noexcept:
        _scheme(),
        _authority(),
        _path(path),
        _query(query),
        _fragment(fragment) {
        // Empty on purpose.
    }

    Uri(const optional_string_t& scheme,
        const std::optional<Authority>& authority,
        const std::string& path,
        const optional_string_t& query = std::nullopt,
        const optional_string_t& fragment = std::nullopt) noexcept:
        _scheme(scheme),
        _authority(authority),
        _path(path),
        _query(query),
        _fragment(fragment) {
        // Empty on purpose.
    }

    Uri(const Uri& that) = default;
    Uri& operator=(const Uri& that) = default;
    Uri(Uri&& that) = default;
    Uri& operator=(Uri&& that) = default;

    bool operator==(const Uri& that) const {
        return (_scheme == that._scheme)
        && (_authority == that._authority)
        && (_path == that._path)
        && (_query == that._query)
        && (_fragment == that._fragment);
    }

    bool operator!=(const Uri& that) const {
        return !operator==(that);
    }

    inline const optional_string_t& getScheme() const {
        return _scheme;
    }

    inline const std::optional<Authority>& getAuthority() const {
        return _authority;
    }

    inline const std::string& getPath() const {
        return _path;
    }

    inline const optional_string_t& getQuery() const {
        return _query;
    }

    inline const optional_string_t& getFragment() const {
        return _fragment;
    }

    ~Uri() = default;

private:
    optional_string_t _scheme;
    std::optional<Authority> _authority;
    std::string _path;
    optional_string_t _query;
    optional_string_t _fragment;
};

} // namespace uri

#endif // __URIC_URI_H__
