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

bool IsGenDelims(char c) {
    return (c == ':') || (c == '/') || (c == '?') || (c == '#') ||
           (c == '[') || (c == ']') || (c == '@');
}

bool IsReserved(char c) {
    return IsGenDelims(c) || IsSubDelims(c);
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

bool ConsumeGenDelims(uri::__internal::TokenReader& reader) {
    if (IsGenDelims(reader.peek())) {
        reader.next();
        return true;
    }
    return false;
}

bool ConsumeReserved(uri::__internal::TokenReader& reader) {
    if (IsReserved(reader.peek())) {
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

bool uriReference(TokenReader& reader) {
    auto token = reader.save();

    if (uri(reader) || relativeRef(reader)) {
        if (reader.hasNext()) {
            reader.restore(token);
            return false;
        }
        return true;
    }

    reader.restore(token);
    return false;
}

bool uri(TokenReader& reader) {
    // TODO(st235): remove.
    std::optional<std::string> scheme_value;
    std::optional<std::string> query;
    std::optional<std::string> fragment;

    auto token = reader.save();

    if (scheme(reader, scheme_value) &&
        reader.consume(':') &&
        hierPart(reader)) {
        auto optional1_token = reader.save();
        if (reader.consume('?')) {
            if (!queryFragment(reader, query)) {
                reader.restore(optional1_token);
            }
        }

        auto optional2_token = reader.save();
        if (reader.consume('#')) {
            if (!queryFragment(reader, fragment)) {
                reader.restore(optional2_token);
            }
        }

        if (reader.hasNext()) {
            reader.restore(token);
            return false;
        }

        return true;
    }

    reader.restore(token);
    return false;
}

bool absoluteUri(TokenReader& reader) {
    // TODO(st235): remove.
    std::optional<std::string> scheme_value;
    std::optional<std::string> query;

    auto token = reader.save();

    if (scheme(reader, scheme_value) &&
        reader.consume(':') &&
        hierPart(reader)) {
        auto optional1_token = reader.save();
        if (reader.consume('?')) {
            if (!queryFragment(reader, query)) {
                reader.restore(optional1_token);
            }
        }

        if (reader.hasNext()) {
            reader.restore(token);
            return false;
        }

        return true;
    }

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
bool path(TokenReader& reader) {
    auto token = reader.save();

    if ((pathAbsolute(reader) && !reader.hasNext()) ||
        (pathNoscheme(reader) && !reader.hasNext()) ||
        (pathRootless(reader) && !reader.hasNext()) ||
        // Path abempty and empty equal to each other in case
        // of an empty string. Path-empty is neglected in this case.
        (pathAbempty(reader) && !reader.hasNext())) {
        return true;
    }

    reader.restore(token);
    return false;
}

// Internal tokens.

bool scheme(TokenReader& reader,
            std::optional<std::string>& value) {
    value = std::nullopt;
    auto token = reader.save();

    if (!IsAlpha(reader.peek())) {
        reader.restore(token);
        return false;
    }

    // Reading ALPHA.
    reader.next();

    while (IsAlpha(reader.peek()) || IsDigit(reader.peek()) ||
        reader.peek() == '+' || reader.peek() == '-' || reader.peek() == '.') {
        reader.next();
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

bool hierPart(TokenReader& reader) {
    auto token = reader.save();

    if (reader.consumeAll("//") && authority(reader) && pathAbempty(reader)) {
        return true;
    }

    reader.restore(token);
    if (pathAbsolute(reader)) {
        return true;
    }

    reader.restore(token);
    if (pathRootless(reader)) {
        return true;
    }

    reader.restore(token);
    if (pathEmpty(reader)) {
        return true;
    }

    reader.restore(token);
    return false;
}

bool relativeRef(TokenReader& reader) {
    // TODO(st235): remove.
    std::optional<std::string> query;
    std::optional<std::string> fragment;

    auto token = reader.save();

    if (!relativePart(reader)) {
        reader.restore(token);
        return false;
    }

    auto optional1_token = reader.save();
    if (reader.consume('?')) {
        if (!queryFragment(reader, query)) {
            reader.restore(optional1_token);
        }
    }

    auto optional2_token = reader.save();
    if (reader.consume('#')) {
        if (!queryFragment(reader, fragment)) {
            reader.restore(optional2_token);
        }
    }

    return true;
}

bool relativePart(TokenReader& reader) {
    auto token = reader.save();

    if (reader.consumeAll("//") && authority(reader) && pathAbempty(reader)) {
        return true;
    }

    reader.restore(token);
    if (pathAbsolute(reader)) {
        return true;
    }

    reader.restore(token);
    if (pathRootless(reader)) {
        return true;
    }

    reader.restore(token);
    if (pathEmpty(reader)) {
        return true;
    }

    reader.restore(token);
    return false;
}

bool authority(TokenReader& reader) {
    // TODO(st235): remove.
    std::optional<std::string> host_value;
    std::optional<std::string> port_value;

    auto token = reader.save();

    if (userInfo(reader)) {
        if (!reader.consume('@')) {
            reader.restore(token);
        }
    }

    if (!host(reader, host_value)) {
        reader.restore(token);
        return false;
    }

    auto option2_token = reader.save();
    if (reader.consume(':')) {
        if (!port(reader, port_value)) {
            reader.restore(option2_token);
        }
    }

    return true;
}

bool userInfo(TokenReader& reader) {
    auto token = reader.save();

    while (ConsumeUnreserved(reader) || pctEncoded(reader)
        || ConsumeSubDelims(reader) || reader.consume(':')) {
    }

    return true;
}

bool host(TokenReader& reader,
          std::optional<std::string>& value) {
    auto token = reader.save();

    if (IPLiteral(reader, value) ||
        IPv4address(reader, value) ||
        regName(reader, value)) {
        return true;
    }

    reader.restore(token);
    return false;
}

bool port(TokenReader& reader,
          std::optional<std::string>& value) {
    value = std::nullopt;
    auto token = reader.save();

    while (IsDigit(reader.peek())) {
        reader.next();
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
    while (IsHexDigit(reader.peek())) {
        reader.next();
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
    while (IsUnreserved(reader.peek()) || IsSubDelims(reader.peek()) ||
        reader.peek() == ':') {
        reader.next();
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

        size_t kn = repeat_counter - 1;
        if (kn < 0) {
            kn = 0;
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
    while (count < 4 && IsHexDigit(reader.peek())) {
        reader.next();
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

    if (!IsDigit(reader.peek())) {
        reader.restore(token);
        return false;
    }
    reader.next();

    return true;
}

bool decOctet_variation3(TokenReader& reader) {
    auto token = reader.save();

    if (!reader.consume('1')) {
        reader.restore(token);
        return false;
    }

    if (!IsDigit(reader.peek())) {
        reader.restore(token);
        return false;
    }
    reader.next();

    if (!IsDigit(reader.peek())) {
        reader.restore(token);
        return false;
    }
    reader.next();

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

    if (!IsDigit(reader.peek())) {
        reader.restore(token);
        return false;
    }
    reader.next();

    return true;
}

bool decOctet_variation5(TokenReader& reader) {
    auto token = reader.save();

    if (!IsDigit(reader.peek())) {
        reader.restore(token);
        return false;
    }
    reader.next();

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

bool pathOptionalSegment(TokenReader& reader) {
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

bool pathAbempty(TokenReader& reader) {
    auto token = reader.save();

    while (pathOptionalSegment(reader)) {
    }

    return true;
}

bool pathAbsolute_option1(TokenReader& reader) {
    auto token = reader.save();

    if (!segmentNz(reader)) {
        reader.restore(token);
        return false;
    }

    if (!pathAbempty(reader)) {
        reader.restore(token);
        return false;
    }

    return true;
}

bool pathAbsolute(TokenReader& reader) {
    auto token = reader.save();

    if (!reader.consume('/')) {
        reader.restore(token);
        return false;
    }

    pathAbsolute_option1(reader);
    return true;
}

bool pathNoscheme(TokenReader& reader) {
    auto token = reader.save();

    if (!segmentNzNc(reader)) {
        reader.restore(token);
        return false;
    }

    return pathAbempty(reader);
}

bool pathRootless(TokenReader& reader) {
    auto token = reader.save();

    if (!segmentNz(reader)) {
        reader.restore(token);
        return false;
    }

    return pathAbempty(reader);
}

bool pathEmpty(TokenReader& reader) {
    // Always returns true as consumes 0 elements.
    // RFC3986: zero characters.
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
