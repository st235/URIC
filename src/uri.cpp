#include "uri.h"

#include "uri_parser.h"
#include "token_reader.h"

namespace uri {

std::optional<Uri> Uri::parse(const std::string& input) {
    __internal::TokenReader reader(input);

    optional_string_t outScheme;
    optional_string_t outUserInfo;
    optional_string_t outHost;
    optional_string_t outPort;
    optional_string_t outPath;
    optional_string_t outQuery;
    optional_string_t outFragment;
    uriReference(reader, outScheme, 
                 outUserInfo, outHost, outPort,
                 outPath,
                 outQuery, outFragment);

    if (reader.hasNext() || !outPath) {
        return std::nullopt;
    }

    std::optional<Authority> authority;
    if (outHost) {
        authority = std::make_optional(Authority(outUserInfo, outHost.value(), outPort));
    }

    return Uri(outScheme, authority, outPath.value(), outQuery, outFragment);
}

std::optional<Uri> Uri::fromParts(const std::string& raw_path,
                                  const optional_string_t& raw_scheme,
                                  const optional_string_t& raw_authority,
                                  const optional_string_t& raw_query,
                                  const optional_string_t& raw_fragment) {
    optional_string_t outScheme;
    std::optional<Authority> outAuthority;
    optional_string_t outPath;
    optional_string_t outQuery;
    optional_string_t outFragment;

    __internal::TokenReader pathReader(raw_path);
    if (!path(pathReader, outPath) || pathReader.hasNext()) {
        return std::nullopt;
    }

    if (raw_scheme) {
        __internal::TokenReader schemeReader(raw_scheme.value());
        if (!scheme(schemeReader, outScheme) || schemeReader.hasNext()) {
            return std::nullopt;
        }
    }

    if (raw_authority) {
        outAuthority = Authority::parse(raw_authority.value());
        if (!outAuthority) {
            return std::nullopt;
        }
    }

    if (raw_query) {
        __internal::TokenReader queryReader(raw_query.value());
        if (!queryFragment(queryReader, outScheme) || queryReader.hasNext()) {
            return std::nullopt;
        }
    }

    if (raw_fragment) {
        __internal::TokenReader fragmentReader(raw_fragment.value());
        if (!queryFragment(fragmentReader, outScheme) || fragmentReader.hasNext()) {
            return std::nullopt;
        }
    }

    return Uri(outScheme, outAuthority, outPath.value(), outQuery, outFragment);
}

} // namepsace uri
