#include "path_utils.h"

#include <cstdint>
#include <sstream>
#include <stack>

namespace {

constexpr char kPathSeparator = '/';
const std::string kPathThisSegment = ".";
const std::string kPathRemoveSegment = "..";

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

// Methods that verify whether
// symbols should be decoded or encoded.
bool ShouldDecode(uint16_t pct_encoded) {
        // A-Z.
    if ((pct_encoded >= 0x41 && pct_encoded <= 0x5A) ||
        // a-z.
        (pct_encoded >= 0x61 && pct_encoded <= 0x7A) ||
        // 0-9.
        (pct_encoded >= 0x30 && pct_encoded <= 0x39) ||
        // Hyphen.
        (pct_encoded == 0x2D) ||
        // Period.
        (pct_encoded == 0x2E) ||
        // Underscore.
        (pct_encoded == 0x5F) ||
        // Tilde.
        (pct_encoded == 0x7E)) {
        return true;
    }

    return false;
}

bool ShouldEncode(char symbol) {
    if (IsAlpha(symbol) ||
        IsHexDigit(symbol) ||
        IsReserved(symbol)) {
        return false;
    }

    return true;
}

uint8_t ConvertCharHexToDecim(char d) {
    if (d >= '0' && d <= '9') {
        return static_cast<uint8_t>(d - '0');
    } else if (d == 'a' || d == 'A') {
        return 10U;
    } else if (d == 'b' || d == 'B') {
        return 11U;
    } else if (d == 'c' || d == 'C') {
        return 12U;
    } else if (d == 'd' || d == 'D') {
        return 13U;
    } else if (d == 'e' || d == 'E') {
        return 14U;
    } else if (d == 'f' || d == 'F') {
        return 15U;
    } else {
        return 0U;
    }
}

char ConvertHexToChar(uint16_t d) {
    // d <= 0 has been implicity assumed.
    if (d <= 9) {
        return static_cast<char>(d + '0');
    } else if (d == 10) {
        return 'A';
    } else if (d == 11) {
        return 'B';
    } else if (d == 12) {
        return 'C';
    } else if (d == 13) {
        return 'D';
    } else if (d == 14) {
        return 'E';
    } else if (d == 15) {
        return 'F';
    } else {
        return '\0';
    }
}

void DecodePct(uint16_t pct_encoded,
            std::stringstream& out) {
    out << static_cast<char>(pct_encoded);
}

void EncodePct(char c,
               std::stringstream& out) {
    uint16_t code = static_cast<uint16_t>(c);
    out << '%' << ConvertHexToChar(code / 16) << ConvertHexToChar(code % 16);
}

std::string Code(const std::string& path) {
    std::stringstream out;

    size_t i = 0;
    while (i < path.length()) {
        if (path[i] == '%' &&
            i < path.length() - 2 &&
            IsHexDigit(path[i + 1]) &&
            IsHexDigit(path[i + 2])) {
            // PCT Encoded.
            uint16_t pct_encoded = ConvertCharHexToDecim(path[i + 1]) * 16 + ConvertCharHexToDecim(path[i + 2]);
            if (ShouldDecode(pct_encoded)) {
                DecodePct(pct_encoded, out);
            } else {
                out << '%' << ConvertHexToChar(pct_encoded / 16) << ConvertHexToChar(pct_encoded % 16);
            }
            i += 3;
        } else {
            char c = path[i];
            if (ShouldEncode(c)) {
                EncodePct(c, out);
            } else {
                out << c;
            }
            i += 1;
        }
    }

    return out.str();
}

} // namespace

namespace uri {

namespace path {

std::vector<std::string> SplitHierarchicalSegments(const std::string& path) {
    std::vector<std::string> segments;

    int32_t last_known_path_separator = -1;
    for (size_t i = 0; i < path.length(); i++) {
        if (path[i] == kPathSeparator) {
            size_t segment_start = static_cast<size_t>(last_known_path_separator + 1);
            size_t segment_end = i;
            size_t segment_length = segment_end - segment_start;

            segments.emplace_back(path.substr(segment_start, segment_length));

            last_known_path_separator = i;
        }
    }

    size_t segment_start = static_cast<size_t>(last_known_path_separator + 1);
    size_t segment_end = path.length();
    size_t segment_length = segment_end - segment_start;

    if (segments.size() == 0 || segment_length > 0) {
        segments.emplace_back(path.substr(segment_start, segment_length));
    }

    return segments;
}

std::vector<std::string> RemoveDotSegments(const std::vector<std::string>& segments) {
    std::stack<std::string> segments_stack;
    std::vector<std::string> normalised_segments;

    for (const auto& segment: segments) {
        if (segment == kPathThisSegment) {
            continue;
        } else if (segment == kPathRemoveSegment) {
            if (!segments_stack.empty()) {
                segments_stack.pop();
            }
        } else {
            segments_stack.push(segment);
        }
    }

    std::stack<std::string> reversed_segments_stack;
    while (!segments_stack.empty()) {
        reversed_segments_stack.push(segments_stack.top());
        segments_stack.pop();
    }

    while (!reversed_segments_stack.empty()) {
        normalised_segments.emplace_back(reversed_segments_stack.top());
        reversed_segments_stack.pop();
    }

    if (segments.size() > 0 && normalised_segments.empty()) {
        normalised_segments.emplace_back("");
    }

    return normalised_segments;
}

std::string CodeIfNecessary(const std::string& path) {
    return Code(path);
}

std::string Normalise(const std::string& path) {
    std::string coded_path = CodeIfNecessary(path);
    std::vector<std::string> segments = SplitHierarchicalSegments(coded_path);
    std::vector<std::string> normalised_segments = RemoveDotSegments(segments);

    std::stringstream out;
    for (size_t i = 0; i < normalised_segments.size(); i++) {
        out << normalised_segments[i];

        if (i < normalised_segments.size() - 1) {
            out << kPathSeparator;
        }
    }

    return out.str();
}

} // namespace path

} // namespace uri
