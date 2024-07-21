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

bool uri(TokenReader& reader);

bool hierPart(TokenReader& reader);

bool uriReference(TokenReader& reader);

bool absoluteUri(TokenReader& reader);

bool relativeRef(TokenReader& reader);

bool relativePart(TokenReader& reader);

bool scheme(TokenReader& reader);

bool authority(TokenReader& reader);

bool userInfo(TokenReader& reader);

bool host(TokenReader& reader);

bool port(TokenReader& reader);

bool IPLiteral(TokenReader& reader);

bool IPvFuture(TokenReader& reader);

bool IPv6Address(TokenReader& reader);

bool h16(TokenReader& reader);

bool ls32(TokenReader& reader);

bool IPv4address(TokenReader& reader);

bool decOctet(TokenReader& reader);

bool regName(TokenReader& reader);

bool path(TokenReader& reader);

bool pathAbempty(TokenReader& reader);

bool pathAbsolute(TokenReader& reader);

bool pathNoscheme(TokenReader& reader);

bool pathRootless(TokenReader& reader);

bool pathEmpty(TokenReader& reader);

bool segment(TokenReader& reader);

bool segmentNz(TokenReader& reader);

bool segmentNzNc(TokenReader& reader);

bool pchar(TokenReader& reader);

bool queryFragment(TokenReader& reader);

bool pctEncoded(TokenReader& reader);

} // namespace internal

} // namespace uri

#endif // __URIC_URI_PARSER_H__
