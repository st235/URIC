#ifndef __URIC_TOKEN_READER_H__
#define __URIC_TOKEN_READER_H__

#include <cstdint>
#include <string>

namespace uri {

namespace __internal {

class TokenReader {
  public:
    using token_t = size_t;

    static inline constexpr char TOKEN_EOF = 0;

    explicit TokenReader(const std::string& raw_json):
        _index(0),
        _raw_json(raw_json) {
        // Empty on purpose.
    }

    TokenReader(const TokenReader& that) {
        this->_index = that._index;
        this->_raw_json = that._raw_json;
    }

    TokenReader& operator=(const TokenReader& that) {
        if (this != &that) {
            this->_index = that._index;
            this->_raw_json = that._raw_json;
        }

        return *this;
    }

    TokenReader(TokenReader&& that) noexcept {
        this->_index = that._index;
        this->_raw_json = std::move(that._raw_json);
    }

    TokenReader& operator=(TokenReader&& that) noexcept {
        if (this != &that) {
            this->_index = that._index;
            this->_raw_json = std::move(that._raw_json);
        }

        return *this;
    }

    inline token_t save() const {
        return _index;
    }

    void restore(token_t token) {
        _index = token;
    }

    inline bool hasNext() const {
        return _index < _raw_json.length();
    }

    char next() {
        char c = peek();
        _index = _index + 1;
        return c;
    }

    bool consume(char c) {
        if (!hasNext()) {
            return false;
        }

        if (peek() == c) {
            next();
            return true;
        }

        return false;
    }

    bool consumeAll(const std::string& match) {
        for (size_t i = 0; i < match.length(); i++) {
            if (!consume(match[i])) {
                return false;
            }
        }

        return true;
    }

    char peek() const {
        if (!hasNext()) {
            return TOKEN_EOF;
        }

        return _raw_json[_index];
    }

    ~TokenReader() = default;
  private:
    size_t _index;
    std::string _raw_json;
};

} // namespace __internal

} // namespace json

#endif // __URIC_TOKEN_READER_H__
