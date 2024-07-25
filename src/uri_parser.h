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

// Entry-point tokens.
// These tokens expect to match the
// entire string: from the begging till the end.

bool uriReference(TokenReader& reader,
                  std::optional<std::string>& outScheme,
                  std::optional<std::string>& outUserInfo,
                  std::optional<std::string>& outHost,
                  std::optional<std::string>& outPort,
                  std::optional<std::string>& outPath,
                  std::optional<std::string>& outQuery,
                  std::optional<std::string>& outFragment);

bool uri(TokenReader& reader,
         std::optional<std::string>& outScheme,
         std::optional<std::string>& outUserInfo,
         std::optional<std::string>& outHost,
         std::optional<std::string>& outPort,
         std::optional<std::string>& outPath,
         std::optional<std::string>& outQuery,
         std::optional<std::string>& outFragment);

bool absoluteUri(TokenReader& reader,
                 std::optional<std::string>& outScheme,
                 std::optional<std::string>& outUserInfo,
                 std::optional<std::string>& outHost,
                 std::optional<std::string>& outPort,
                 std::optional<std::string>& outPath,
                 std::optional<std::string>& outQuery);

bool path(TokenReader& reader,
          std::optional<std::string>& outValue);

// Internal tokens (sorted by importance).

bool scheme(TokenReader& reader,
            std::optional<std::string>& outValue);

bool host(TokenReader& reader,
          std::optional<std::string>& outValue);

bool queryFragment(TokenReader& reader,
                   std::optional<std::string>& outValue);

bool hierPart(TokenReader& reader,
              std::optional<std::string>& outUserInfo,
              std::optional<std::string>& outHost,
              std::optional<std::string>& outPort,
              std::optional<std::string>& outPath);

bool relativeRef(TokenReader& reader,
                 std::optional<std::string>& outUserInfo,
                 std::optional<std::string>& outHost,
                 std::optional<std::string>& outPort,
                 std::optional<std::string>& outPath,
                 std::optional<std::string>& outQuery,
                 std::optional<std::string>& outFragment);

bool relativePart(TokenReader& reader,
                  std::optional<std::string>& outUserInfo,
                  std::optional<std::string>& outHost,
                  std::optional<std::string>& outPort,
                  std::optional<std::string>& outPath);

bool authority(TokenReader& reader,
               std::optional<std::string>& outUserInfo,
               std::optional<std::string>& outHost,
               std::optional<std::string>& outPort);

bool userInfo(TokenReader& reader,
              std::optional<std::string>& outValue);

bool port(TokenReader& reader,
          std::optional<std::string>& outValue);

bool IPLiteral(TokenReader& reader,
               std::optional<std::string>& outValue);

bool IPv4address(TokenReader& reader,
                 std::optional<std::string>& outValue);

bool regName(TokenReader& reader,
             std::optional<std::string>& outValue);

bool IPvFuture(TokenReader& reader);

bool IPv6address(TokenReader& reader);

bool h16(TokenReader& reader);

bool ls32(TokenReader& reader);

bool decOctet(TokenReader& reader);

bool pathAbempty(TokenReader& reader,
                 std::optional<std::string>& outValue);

bool pathAbsolute(TokenReader& reader,
                  std::optional<std::string>& outValue);

bool pathNoscheme(TokenReader& reader,
                  std::optional<std::string>& outValue);

bool pathRootless(TokenReader& reader,
                  std::optional<std::string>& outValue);

bool pathEmpty(TokenReader& reader,
               std::optional<std::string>& outValue);

bool segment(TokenReader& reader);

bool segmentNz(TokenReader& reader);

bool segmentNzNc(TokenReader& reader);

bool pchar(TokenReader& reader);

bool pctEncoded(TokenReader& reader);

} // namespace internal

} // namespace uri

#endif // __URIC_URI_PARSER_H__
