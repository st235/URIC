#ifndef __URIC_URI_H__
#define __URIC_URI_H__

#include <optional>
#include <string>

namespace uri {

class Uri {
public:
    static std::optional<Uri> parse(const std::string& text);
    static std::optional<Uri> fromParts(const std::string& text);
};

} // namespace uri

#endif // __URIC_URI_H__
