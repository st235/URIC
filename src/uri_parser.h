#ifndef __URIC_URI_PARSER_H__
#define __URIC_URI_PARSER_H__

#include <cstdint>
#include <optional>
#include <string>
#include <limits>

namespace uri {

namespace __internal {

class TokenReader;

// TODO(st235): leave only public API in header.
// TODO(st235): collapse similar rules.

// Entry-point tokens.
// These tokens expect to match the
// entire string: from the begging till the end.

bool uriReference(TokenReader& reader);

bool uri(TokenReader& reader);

bool absoluteUri(TokenReader& reader);

bool path(TokenReader& reader);

// Internal tokens (sorted by importance).

bool scheme(TokenReader& reader,
            std::optional<std::string>& value);

bool host(TokenReader& reader,
          std::optional<std::string>& value);

bool queryFragment(TokenReader& reader,
                   std::optional<std::string>& value);

bool hierPart(TokenReader& reader);

bool relativeRef(TokenReader& reader);

bool relativePart(TokenReader& reader);

bool authority(TokenReader& reader);

bool userInfo(TokenReader& reader,
              std::optional<std::string>& value);

bool port(TokenReader& reader,
          std::optional<std::string>& value);

bool IPLiteral(TokenReader& reader,
               std::optional<std::string>& value);

bool IPv4address(TokenReader& reader,
                 std::optional<std::string>& value);

bool regName(TokenReader& reader,
             std::optional<std::string>& value);

bool IPvFuture(TokenReader& reader);

bool IPv6address(TokenReader& reader);

bool h16(TokenReader& reader);

bool ls32(TokenReader& reader);

bool decOctet(TokenReader& reader);

bool pathAbempty(TokenReader& reader);

bool pathAbsolute(TokenReader& reader);

bool pathNoscheme(TokenReader& reader);

bool pathRootless(TokenReader& reader);

bool pathEmpty(TokenReader& reader);

bool segment(TokenReader& reader);

bool segmentNz(TokenReader& reader);

bool segmentNzNc(TokenReader& reader);

bool pchar(TokenReader& reader);

bool pctEncoded(TokenReader& reader);

} // namespace internal

} // namespace uri

#endif // __URIC_URI_PARSER_H__
