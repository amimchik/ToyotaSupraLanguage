#pragma once

#include <deque>
#include <string>

namespace org::amimchik::tsl::core {

enum class TokenType {
    EndOfFile
};

struct Token {
    TokenType type;
};

class Lexer {
private:
public:
    std::deque<Token> tokenze(std::string str);
};

}  // namespace org::amimchik::tsl::core
