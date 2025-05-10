#include <ToyotaSupraLanguage/Lexer.h>

namespace ToyotaSupraLanguage {

    Lexer::Lexer(std::string& input) {
        this->input = input;
        pos = 0;
    }
    std::list<Token> Lexer::tokenize_all() {
        std::list<Token> tokens = std::list<Token>();

        Token current;

        do {
            current = get_next_token();

            tokens.push_back(current);
        } while (current.type != TokenType::EndOfFile);

        return tokens;
    }
    Token Lexer::get_next_token() {
        char c = current();

        while (true) {
            if (!current()) {
                return Token::createSimple(TokenType::EndOfFile);
            }
            if (isalpha(c)) {
                return tokenize_word();
            }
            if (isdigit(c)) {
                return tokenize_number();
            }
            if (strIndexOf(specChars, c) != -1) {
                return tokenize_special();
            }
            if (c == '\'' || c == '\"') {
                return tokenize_str_lit();
            }
            c = next();
        }
    }
    Token Lexer::tokenize_word() {
        std::string buffer;

        char c = current();
        while (isalnum(c)) {
            buffer += c;
            c = next();
        }

        if (keywords.find(buffer) != keywords.end()) {
            return keywords.at(buffer);
        }

        return Token::createIdentifier(buffer);
    }
    Token Lexer::tokenize_number() {
        uint64_t val = 0;

        char c = current();

        while (isdigit(c)) {
            val *= 10;
            val += c - '0';
            c = next();
        }

        return Token::createNumber(val);
    }
    Token Lexer::tokenize_special() {
        std::string buffer;

        while (specs.find(buffer + current()) != specs.end()) {
            buffer += current();
            next();
        }

        if (buffer.length() == 0) {
            throw std::runtime_error("operator error");
        }

        return specs.at(buffer);
    }
    Token Lexer::tokenize_str_lit() {
        std::string buffer;

        char endSymbol = current();

        char c = next();

        while (c != endSymbol) {
            if (c == '\\') {
                c = next();
                switch (c) {
                case 'n':
                    buffer += '\n';
                    break;
                case 't':
                    buffer += '\t';
                    break;
                case 'r':
                    buffer += '\t';
                    break;
                default:
                    buffer += c;
                    break;
                }
            } else {
                buffer += c;
            }

            c = next();
        }

        buffer += c;

        return Token::createStringLiteral(buffer);
    }
    bool Lexer::inRange(size_t i) {
        return i < input.length();
    }
    char Lexer::peek(int offset) {
        if (inRange(pos + offset)) {
            return input[pos + offset];
        } else {
            return '\0';
        }
    }
    char Lexer::current() {
        return peek(0);
    }
    char Lexer::next() {
        if (inRange(pos)) {
            pos++;
        }
        if (inRange(pos)) {
            return input[pos];
        }
        return '\0';
    }
    int Lexer::strIndexOf(const std::string& str, char c) {
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == c) {
                return i;
            }
        }
        return -1;
    }

    Token Token::createSimple(TokenType type) {
        Token t;
        t.type = type;
        return t;
    }
    Token Token::createIdentifier(std::string idV) {
        Token t;
        t.type = TokenType::Identifier;
        t.stringValue = idV;
        return t;
    }
    Token Token::createNumber(uint64_t v) {
        Token t;
        t.type = TokenType::NumberLiteral;
        return t;
    }
    Token Token::createStringLiteral(std::string v) {
        Token t;
        t.type = TokenType::StringLiteral;
        t.stringValue = v;
        return t;
    }
    Token::Token() {
        type = TokenType::EndOfFile;
    }
    std::string Token::toString() const {
        if (type == TokenType::Identifier) {
            return "[ID:" + stringValue + "]";
        }
        return "[" + tokenTypeToString(type) + "]";
    }
    std::string tokenTypeToString(TokenType type) {
        switch (type) {
        case TokenType::Let: return "Let";
        case TokenType::Identifier: return "Identifier";
        case TokenType::NumberLiteral: return "NumberLiteral";
        case TokenType::StringLiteral: return "StringLiteral";

        case TokenType::Print: return "Print";
        case TokenType::PrintL: return "PrintL";
        case TokenType::ReadL: return "ReadL";
        case TokenType::ReadC: return "ReadC";

        case TokenType::If: return "If";
        case TokenType::Else: return "Else";
        case TokenType::While: return "While";

        case TokenType::Function: return "Function";

        case TokenType::Plus: return "Plus";
        case TokenType::Minus: return "Minus";
        case TokenType::Star: return "Star";
        case TokenType::Slash: return "Slash";

        case TokenType::Assign: return "Assign";

        case TokenType::Equals: return "Equals";
        case TokenType::NotEquals: return "NotEquals";
        case TokenType::LessThan: return "LessThan";
        case TokenType::GreatherThan: return "GreatherThan";
        case TokenType::LessEqualThan: return "LessEqualThan";
        case TokenType::GreatherEqualThen: return "GreatherEqualThen";

        case TokenType::Colon: return "Colon";
        case TokenType::Comma: return "Comma";
        case TokenType::Dot: return "Dot";

        case TokenType::LBracket: return "LBracket";
        case TokenType::RBracket: return "RBracket";
        case TokenType::LBrace: return "LBrace";
        case TokenType::RBrace: return "RBrace";
        case TokenType::LParen: return "LParen";
        case TokenType::RParen: return "RParen";

        case TokenType::EndOfFile: return "EOF";
        }

        throw std::invalid_argument("Unknown TokenType");
    }
}  // namespace ToyotaSupraLanguage
