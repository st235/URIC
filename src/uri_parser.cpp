#include "uri_parser.h"

#include "token_reader.h"

namespace {

bool IsAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool IsDigit(char c) {
    return c >= '0' && c <= '9';
}

// The uppercase hexadecimal digits 'A' through 'F' are equivalent to
// the lowercase digits 'a' through 'f', respectively.
bool IsHexDigit(char c) {
    return IsDigit(c) ||
           (c >= 'a' && c <= 'f') ||
           (c >= 'A' && c <= 'F');
}

bool IsSubDelims(char c) {
    return (c == '!') || (c == '$') || (c == '&') || (c == '\'') ||
           (c == '(') || (c == ')') || (c == '*') || (c == '+') ||
           (c == ',') || (c == ';') || (c == '=');
}

bool IsUnreserved(char c) {
    return IsAlpha(c) || IsDigit(c) ||
           (c == '-') || (c == '.') ||
           (c == '_') || (c == '~');
}

bool ConsumeAlpha(uri::__internal::TokenReader& reader) {
    if (IsAlpha(reader.peek())) {
        reader.next();
        return true;
    }
    return false;
}

bool ConsumeDigit(uri::__internal::TokenReader& reader) {
    if (IsDigit(reader.peek())) {
        reader.next();
        return true;
    }
    return false;
}

bool ConsumeHexDigit(uri::__internal::TokenReader& reader) {
    if (IsHexDigit(reader.peek())) {
        reader.next();
        return true;
    }
    return false;
}

bool ConsumeSubDelims(uri::__internal::TokenReader& reader) {
    if (IsSubDelims(reader.peek())) {
        reader.next();
        return true;
    }
    return false;
}

bool ConsumeUnreserved(uri::__internal::TokenReader& reader) {
    if (IsUnreserved(reader.peek())) {
        reader.next();
        return true;
    }
    return false;
}

} // namespace


namespace uri {

namespace __internal {

bool UriReference(TokenReader& reader,
                  std::optional<std::string>& outScheme,
                  std::optional<std::string>& outUserInfo,
                  std::optional<std::string>& outHost,
                  std::optional<HostType>& outHostType,
                  std::optional<std::string>& outPort,
                  std::optional<std::string>& outPath,
                  std::optional<std::string>& outQuery,
                  std::optional<std::string>& outFragment) {
    auto token = reader.save();

    if (Uri(reader, outScheme,
            outUserInfo, outHost, outHostType, outPort,
            outPath, outQuery, outFragment) ||
        relativeRef(reader,
                    outUserInfo, outHost, outHostType, outPort,
                    outPath, outQuery, outFragment)) {

        // Math only the entire input.
        if (!reader.hasNext()) {
            return true;
        }
    }

    outScheme = std::nullopt;
    outUserInfo = std::nullopt;
    outHost = std::nullopt;
    outHostType = std::nullopt;
    outPort = std::nullopt;
    outPath = std::nullopt;
    outQuery = std::nullopt;
    outFragment = std::nullopt;
    reader.restore(token);
    return false;
}

bool Uri(TokenReader& reader,
         std::optional<std::string>& outScheme,
         std::optional<std::string>& outUserInfo,
         std::optional<std::string>& outHost,
         std::optional<HostType>& outHostType,
         std::optional<std::string>& outPort,
         std::optional<std::string>& outPath,
         std::optional<std::string>& outQuery,
         std::optional<std::string>& outFragment) {
    auto token = reader.save();

    if (scheme(reader, outScheme) &&
        reader.consume(':') &&
        hierPart(reader,
                 outUserInfo, outHost, outHostType, outPort,
                 outPath)) {
        auto optional1_token = reader.save();
        if (reader.consume('?')) {
            if (!queryFragment(reader, outQuery)) {
                reader.restore(optional1_token);
            }
        }

        auto optional2_token = reader.save();
        if (reader.consume('#')) {
            if (!queryFragment(reader, outFragment)) {
                reader.restore(optional2_token);
            }
        }

        // Math only the entire input.
        if (!reader.hasNext()) {
            return true;
        }
    }

    outScheme = std::nullopt;
    outUserInfo = std::nullopt;
    outHost = std::nullopt;
    outHostType = std::nullopt;
    outPort = std::nullopt;
    outPath = std::nullopt;
    outQuery = std::nullopt;
    outFragment = std::nullopt;
    reader.restore(token);
    return false;
}

bool AbsoluteUri(TokenReader& reader,
                 std::optional<std::string>& outScheme,
                 std::optional<std::string>& outUserInfo,
                 std::optional<std::string>& outHost,
                 std::optional<HostType>& outHostType,
                 std::optional<std::string>& outPort,
                 std::optional<std::string>& outPath,
                 std::optional<std::string>& outQuery) {
    auto token = reader.save();

    if (scheme(reader, outScheme) &&
        reader.consume(':') &&
        hierPart(reader, outUserInfo, outHost, outHostType, outPort, outPath)) {

        auto optional1_token = reader.save();
        if (reader.consume('?')) {
            if (!queryFragment(reader, outQuery)) {
                reader.restore(optional1_token);
            }
        }

        // Return only if we read the entire input.
        if (!reader.hasNext()) {
            return true;
        }
    }

    outScheme = std::nullopt;
    outUserInfo = std::nullopt;
    outHost = std::nullopt;
    outHostType = std::nullopt;
    outPort = std::nullopt;
    outPath = std::nullopt;
    outQuery = std::nullopt;
    reader.restore(token);
    return false;
}

// Path is not used in RFC3986 directly,
// therefore this is a high level defition.
// It is possible to rewrite the rule to
// match the entire string.
// Original rule is:
// path = path-abempty    ; begins with "/" or is empty
//      / path-absolute   ; begins with "/" but not "//"
//      / path-noscheme   ; begins with a non-colon segment
//      / path-rootless   ; begins with a segment
//      / path-empty      ; zero characters
bool Path(TokenReader& reader,
          std::optional<std::string>& value) {
    auto token = reader.save();

    if (pathAbsolute(reader, value) && !reader.hasNext()) {
        return true;
    }

    reader.restore(token);
    if (pathNoscheme(reader, value) && !reader.hasNext()) {
    return true;
    }

    reader.restore(token);
    if (pathRootless(reader, value) && !reader.hasNext()) {
    return true;
    }

    // Path abempty and empty equal to each other in case
    // of an empty string. Path-empty is neglected in this case.
    reader.restore(token);
    if (pathAbempty(reader, value) && !reader.hasNext()) {
    return true;
    }

    value = std::nullopt;
    reader.restore(token);
    return false;
}

// Internal tokens.

bool scheme(TokenReader& reader,
            std::optional<std::string>& value) {
    value = std::nullopt;
    auto token = reader.save();

    if (!ConsumeAlpha(reader)) {
        reader.restore(token);
        return false;
    }

    while (ConsumeAlpha(reader) || ConsumeDigit(reader) ||
        reader.consume('+') || reader.consume('-') || reader.consume('.')) {
    }

    value = reader.extract(token);
    return true;
}

bool queryFragment(TokenReader& reader,
                   std::optional<std::string>& value) {
    value = std::nullopt;
    auto token = reader.save();

    while (pchar(reader) ||
        reader.consume('/') ||
        reader.consume('?')) {
    }

    value = reader.extract(token);
    return true;
}

bool hierPart(TokenReader& reader,
              std::optional<std::string>& outUserInfo,
              std::optional<std::string>& outHost,
              std::optional<HostType>& outHostType,
              std::optional<std::string>& outPort,
              std::optional<std::string>& outPath) {
    auto token = reader.save();

    if (reader.consumeAll("//") &&
        authority(reader, outUserInfo, outHost, outHostType, outPort) &&
        pathAbempty(reader, outPath)) {
        return true;
    }

    reader.restore(token);
    if (pathAbsolute(reader, outPath)) {
        return true;
    }

    reader.restore(token);
    if (pathRootless(reader, outPath)) {
        return true;
    }

    reader.restore(token);
    if (pathEmpty(reader, outPath)) {
        return true;
    }

    reader.restore(token);
    return false;
}

bool relativeRef(TokenReader& reader,
                 std::optional<std::string>& outUserInfo,
                 std::optional<std::string>& outHost,
                 std::optional<HostType>& outHostType,
                 std::optional<std::string>& outPort,
                 std::optional<std::string>& outPath,
                 std::optional<std::string>& outQuery,
                 std::optional<std::string>& outFragment) {
    auto token = reader.save();

    if (!relativePart(reader,
                      outUserInfo, outHost, outHostType, outPort,
                      outPath)) {
        reader.restore(token);
        return false;
    }

    auto optional1_token = reader.save();
    if (reader.consume('?')) {
        if (!queryFragment(reader, outQuery)) {
            reader.restore(optional1_token);
        }
    }

    auto optional2_token = reader.save();
    if (reader.consume('#')) {
        if (!queryFragment(reader, outFragment)) {
            reader.restore(optional2_token);
        }
    }

    return true;
}

bool relativePart(TokenReader& reader,
                  std::optional<std::string>& outUserInfo,
                  std::optional<std::string>& outHost,
                  std::optional<HostType>& outHostType,
                  std::optional<std::string>& outPort,
                  std::optional<std::string>& outPath) {
    auto token = reader.save();

    if (reader.consumeAll("//") &&
        authority(reader, outUserInfo, outHost, outHostType, outPort) &&
        pathAbempty(reader, outPath)) {
        return true;
    }

    reader.restore(token);
    if (pathAbsolute(reader, outPath)) {
        return true;
    }

    reader.restore(token);
    if (pathNoscheme(reader, outPath)) {
        return true;
    }

    reader.restore(token);
    if (pathEmpty(reader, outPath)) {
        return true;
    }

    reader.restore(token);
    return false;
}

bool authority(TokenReader& reader,
               std::optional<std::string>& outUserInfo,
               std::optional<std::string>& outHost,
               std::optional<HostType>& outHostType,
               std::optional<std::string>& outPort) {
    auto token = reader.save();

    if (userInfo(reader, outUserInfo)) {
        if (!reader.consume('@')) {
            // If no @ matched, no
            // user info should be returned.
            outUserInfo = std::nullopt;
            reader.restore(token);
        }
    }

    if (!host(reader, outHost, outHostType)) {
        reader.restore(token);
        return false;
    }

    auto option2_token = reader.save();
    if (reader.consume(':')) {
        if (!port(reader, outPort)) {
            reader.restore(option2_token);
        }
    }

    return true;
}

bool userInfo(TokenReader& reader,
              std::optional<std::string>& value) {
    value = std::nullopt;
    auto token = reader.save();

    while (ConsumeUnreserved(reader) || pctEncoded(reader)
        || ConsumeSubDelims(reader) || reader.consume(':')) {
    }

    value = reader.extract(token);
    return true;
}

bool host(TokenReader& reader,
          std::optional<std::string>& outHost,
          std::optional<HostType>& outHostType) {
    outHostType = std::nullopt;
    auto token = reader.save();

    if (IPLiteral(reader, outHost)) {
        outHostType = std::make_optional(HostType::kIPLiteral);
        return true;
    }

    if (IPv4address(reader, outHost)) {
        outHostType = std::make_optional(HostType::kIPv4);
        return true;
    }

    if (regName(reader, outHost)) {
        outHostType = std::make_optional(HostType::kRegName);
        return true;
    }

    reader.restore(token);
    return false;
}

bool port(TokenReader& reader,
          std::optional<std::string>& value) {
    value = std::nullopt;
    auto token = reader.save();

    while (ConsumeDigit(reader)) {
    }

    value = reader.extract(token);
    return true;
}

bool IPLiteral(TokenReader& reader,
               std::optional<std::string>& value) {
    value = std::nullopt;
    auto token = reader.save();

    if (!reader.consume('[')) {
        reader.restore(token);
        return false;
    }

    auto value_start_token = reader.save();

    if (!IPv6address(reader) && !IPvFuture(reader)) {
        reader.restore(token);
        return false;
    }

    auto value_end_token = reader.save();

    if (!reader.consume(']')) {
        reader.restore(token);
        return false;
    }

    value = reader.extract(value_start_token, value_end_token);
    return true;
}

bool IPv4address(TokenReader& reader,
                 std::optional<std::string>& value) {
    value = std::nullopt;
    auto token = reader.save();

    if (decOctet(reader) && reader.consume('.') &&
        decOctet(reader) && reader.consume('.') &&
        decOctet(reader) && reader.consume('.') &&
        decOctet(reader)) {
        value = reader.extract(token);
        return true;
    }

    reader.restore(token);
    return false;
}

bool regName(TokenReader& reader,
             std::optional<std::string>& value) {
    value = std::nullopt;
    auto token = reader.save();

    while (ConsumeUnreserved(reader) ||
           pctEncoded(reader) ||
           ConsumeSubDelims(reader)) {
    }

    value = reader.extract(token);
    return true;
}

bool IPvFuture(TokenReader& reader) {
    auto token = reader.save();

    if (!reader.consume('v')) {
        reader.restore(token);
        return false;
    }

    size_t repeat_counter = 0;
    while (ConsumeHexDigit(reader)) {
        repeat_counter += 1;
    }

    if (repeat_counter < 1) {
        reader.restore(token);
        return false;
    }

    if (!reader.consume('.')) {
        reader.restore(token);
        return false;
    }

    repeat_counter = 0;
    while (ConsumeUnreserved(reader) || ConsumeSubDelims(reader) ||
        reader.consume(':')) {
        repeat_counter += 1;
    }

    if (repeat_counter < 1) {
        reader.restore(token);
        return false;
    }

    return true;
}

bool IPv6H16Part(TokenReader& reader) {
    auto token = reader.save();

    if (h16(reader) && reader.consume(':')) {
        return true;
    }

    reader.restore(token);
    return false;
}

bool IPv6H16PartRepeatExactly(TokenReader& reader, size_t k) {
    auto token = reader.save();

    size_t repeat_counter = 0;
    while (repeat_counter < k && IPv6H16Part(reader)) {
        repeat_counter += 1;
    }

    // Cannot be bigger as we broke the loop.
    if (repeat_counter < k) {
        reader.restore(token);
        return false;
    }

    return true;
}

bool IPv6address_optional(TokenReader& reader, size_t k) {
    auto token = reader.save();

    size_t repeat_counter = 0;
    while (repeat_counter < k && IPv6H16Part(reader)) {
        repeat_counter += 1;
    }

    if (!h16(reader)) {
        reader.restore(token);

        size_t kn = 0;
        if (repeat_counter > 0) {
            kn = repeat_counter - 1;
        }
        repeat_counter = 0;

        while (repeat_counter < kn && IPv6H16Part(reader)) {
            repeat_counter += 1;
        }

        if (!h16(reader)) {
            reader.restore(token);
            return false;
        }
    }

    return true;
}

bool IPv6addressVariation1(TokenReader& reader) {
    auto token = reader.save();
    
    if (!IPv6H16PartRepeatExactly(reader, 6)) {
        reader.restore(token);
        return false;
    }

    if (!ls32(reader)) {
        reader.restore(token);
        return false;
    }

    return true;
}

bool IPv6addressVariation2(TokenReader& reader) {
    auto token = reader.save();

    if (!reader.consumeAll("::")) {
        reader.restore(token);
        return false;
    }
    
    if (!IPv6H16PartRepeatExactly(reader, 5)) {
        reader.restore(token);
        return false;
    }

    if (!ls32(reader)) {
        reader.restore(token);
        return false;
    }

    return true;
}

bool IPv6addressVariation3(TokenReader& reader) {
    auto token = reader.save();

    // Optional.
    h16(reader);

    if (!reader.consumeAll("::")) {
        reader.restore(token);
        return false;
    }
    
    if (!IPv6H16PartRepeatExactly(reader, 4)) {
        reader.restore(token);
        return false;
    }

    if (!ls32(reader)) {
        reader.restore(token);
        return false;
    }

    return true;
}

bool IPv6addressVariation4(TokenReader& reader) {
    auto token = reader.save();

    IPv6address_optional(reader, 1);

    if (!reader.consumeAll("::")) {
        reader.restore(token);
        return false;
    }
    
    if (!IPv6H16PartRepeatExactly(reader, 3)) {
        reader.restore(token);
        return false;
    }

    if (!ls32(reader)) {
        reader.restore(token);
        return false;
    }

    return true;
}

bool IPv6addressVariation5(TokenReader& reader) {
    auto token = reader.save();

    IPv6address_optional(reader, 2);

    if (!reader.consumeAll("::")) {
        reader.restore(token);
        return false;
    }
    
    if (!IPv6H16PartRepeatExactly(reader, 2)) {
        reader.restore(token);
        return false;
    }

    if (!ls32(reader)) {
        reader.restore(token);
        return false;
    }

    return true;
}

bool IPv6addressVariation6(TokenReader& reader) {
    auto token = reader.save();

    IPv6address_optional(reader, 3);

    if (!reader.consumeAll("::")) {
        reader.restore(token);
        return false;
    }
    
    if (!IPv6H16Part(reader)) {
        reader.restore(token);
        return false;
    }

    if (!ls32(reader)) {
        reader.restore(token);
        return false;
    }

    return true;
}

bool IPv6addressVariation7(TokenReader& reader) {
    auto token = reader.save();

    IPv6address_optional(reader, 4);

    if (!reader.consumeAll("::")) {
        reader.restore(token);
        return false;
    }

    if (!ls32(reader)) {
        reader.restore(token);
        return false;
    }

    return true;
}

bool IPv6addressVariation8(TokenReader& reader) {
    auto token = reader.save();

    IPv6address_optional(reader, 5);

    if (!reader.consumeAll("::")) {
        reader.restore(token);
        return false;
    }

    if (!h16(reader)) {
        reader.restore(token);
        return false;
    }

    return true;
}

bool IPv6addressVariation9(TokenReader& reader) {
    auto token = reader.save();

    IPv6address_optional(reader, 6);

    if (!reader.consumeAll("::")) {
        reader.restore(token);
        return false;
    }

    return true;
}

bool IPv6address(TokenReader& reader) {
    auto token = reader.save();

    if (IPv6addressVariation1(reader) ||
        IPv6addressVariation2(reader) ||
        IPv6addressVariation3(reader) ||
        IPv6addressVariation4(reader) ||
        IPv6addressVariation5(reader) ||
        IPv6addressVariation6(reader) ||
        IPv6addressVariation7(reader) ||
        IPv6addressVariation8(reader) ||
        IPv6addressVariation9(reader)) {
        return true;
    }

    reader.restore(token);
    return false;
}

bool h16(TokenReader& reader) {
    auto token = reader.save();

    size_t count = 0;
    while (count < 4 && ConsumeHexDigit(reader)) {
        count += 1;
    }

    if (count < 1) {
        reader.restore(token);
        return false;
    }

    return true;
}

bool ls32_Alteration1(TokenReader& reader) {
    auto token = reader.save();

    if (!h16(reader)) {
        reader.restore(token);
        return false;
    }

    if (!reader.consume(':')) {
        reader.restore(token);
        return false;
    }

    if (!h16(reader)) {
        reader.restore(token);
        return false;
    }

    return true;
}

bool ls32(TokenReader& reader) {
    auto token = reader.save();

    // TODO(st235): think about better API to improve the parsing?
    std::optional<std::string> discarded_value;
    if (ls32_Alteration1(reader) ||
        IPv4address(reader, discarded_value)) {
        return true;
    }

    reader.restore(token);
    return false;
}

bool decOctet_variation1(TokenReader& reader) {
    auto token = reader.save();

    if (!reader.consumeAll("25")) {
        reader.restore(token);
        return false;
    }

    auto c = reader.peek();
    if (c < '0' || c > '5') {
        reader.restore(token);
        return false;
    }

    reader.next();
    return true;
}

bool decOctet_variation2(TokenReader& reader) {
    auto token = reader.save();

    if (!reader.consume('2')) {
        reader.restore(token);
        return false;
    }

    auto c = reader.peek();
    if (c < '0' || c > '4') {
        reader.restore(token);
        return false;
    }
    reader.next();

    if (!ConsumeDigit(reader)) {
        reader.restore(token);
        return false;
    }

    return true;
}

bool decOctet_variation3(TokenReader& reader) {
    auto token = reader.save();

    if (!reader.consume('1')) {
        reader.restore(token);
        return false;
    }

    if (!ConsumeDigit(reader)) {
        reader.restore(token);
        return false;
    }

    if (!ConsumeDigit(reader)) {
        reader.restore(token);
        return false;
    }

    return true;
}

bool decOctet_variation4(TokenReader& reader) {
    auto token = reader.save();

    auto c = reader.peek();
    if (c < '1' || c > '9') {
        reader.restore(token);
        return false;
    }
    reader.next();

    if (!ConsumeDigit(reader)) {
        reader.restore(token);
        return false;
    }

    return true;
}

bool decOctet_variation5(TokenReader& reader) {
    auto token = reader.save();

    if (!ConsumeDigit(reader)) {
        reader.restore(token);
        return false;
    }

    return true;
}

bool decOctet(TokenReader& reader) {
    auto token = reader.save();

    if (decOctet_variation1(reader) ||
        decOctet_variation2(reader) ||
        decOctet_variation3(reader) ||
        decOctet_variation4(reader) ||
        decOctet_variation5(reader)) {
        return true;
    }

    reader.restore(token);
    return false;
}

bool path_optional_segment(TokenReader& reader) {
    auto token = reader.save();

    if (!reader.consume('/')) {
        reader.restore(token);
        return false;
    }

    if (!segment(reader)) {
        reader.restore(token);
        return false;
    }

    return true;
}

bool path_kleene_slash_segment(TokenReader& reader) {
    while (path_optional_segment(reader)) {
    }
    return true;
}

bool pathAbempty(TokenReader& reader,
                 std::optional<std::string>& value) {
    value = std::nullopt;
    auto token = reader.save();

    path_kleene_slash_segment(reader);

    value = reader.extract(token);
    return true;
}

bool pathAbsolute_option1(TokenReader& reader) {
    auto token = reader.save();

    if (!segmentNz(reader)) {
        reader.restore(token);
        return false;
    }

    if (!path_kleene_slash_segment(reader)) {
        reader.restore(token);
        return false;
    }

    return true;
}

bool pathAbsolute(TokenReader& reader,
                  std::optional<std::string>& value) {
    value = std::nullopt;
    auto token = reader.save();

    if (!reader.consume('/')) {
        reader.restore(token);
        return false;
    }

    pathAbsolute_option1(reader);
    value = reader.extract(token);
    return true;
}

bool pathNoscheme(TokenReader& reader,
                  std::optional<std::string>& value) {
    value = std::nullopt;
    auto token = reader.save();

    if (!segmentNzNc(reader)) {
        reader.restore(token);
        return false;
    }

    path_kleene_slash_segment(reader);
    value = reader.extract(token);
    return true;
}

bool pathRootless(TokenReader& reader,
                  std::optional<std::string>& value) {
    value = std::nullopt;
    auto token = reader.save();

    if (!segmentNz(reader)) {
        reader.restore(token);
        return false;
    }

    path_kleene_slash_segment(reader);
    value = reader.extract(token);
    return true;
}

// Always returns true as consumes 0 elements.
// RFC3986: zero characters.
bool pathEmpty(TokenReader&,
               std::optional<std::string>& value) {
    value = "";
    return true;
}

bool segment(TokenReader& reader) {
    while(pchar(reader)) {
    }
    return true;
}

bool segmentNz(TokenReader& reader) {
    auto token = reader.save();

    size_t counter = 0;
    while(pchar(reader)) {
        counter += 1;
    }

    if (counter < 1) {
        reader.restore(token);
        return false;
    }

    return true;
}

bool segmentNzNc(TokenReader& reader) {
    auto token = reader.save();

    size_t counter = 0;
    while(ConsumeUnreserved(reader) ||
          pctEncoded(reader) ||
          ConsumeSubDelims(reader) ||
          reader.consume('@')) {
        counter += 1;
    }

    if (counter < 1) {
        reader.restore(token);
        return false;
    }

    return true;
}

bool pchar(TokenReader& reader) {
    auto token = reader.save();

    if (ConsumeUnreserved(reader) ||
        pctEncoded(reader) ||
        ConsumeSubDelims(reader) ||
        reader.consume(':') ||
        reader.consume('@')) {
        return true;
    }

    reader.restore(token);
    return false;
}

bool pctEncoded(TokenReader& reader) {
    auto token = reader.save();

    if (reader.consume('%') && ConsumeHexDigit(reader) && ConsumeHexDigit(reader)) {
        return true;
    }

    reader.restore(token);
    return false;
}

} // namespace __internal

} // namespace uri
