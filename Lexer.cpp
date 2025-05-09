#include "Lexer.h"

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
            throw std::exception("operator error");
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
    int Lexer::strIndexOf(const std::string& const str, char c) {
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
            return "id:" + stringValue;
        }
        return tokenTypeToString(type);
    }

    std::string tokenTypeToString(TokenType t) {
        switch (t) {
        case TokenType::Let:
            return "let";
            break;
        case TokenType::NumberLiteral:
            return "numberLiteral";
        case TokenType::StringLiteral:
            return "stringLiteral";
        case TokenType::Print:
            return "print";
        case TokenType::PrintL:
            return "printl";
        case TokenType::ReadL:
            return "readl";
        case TokenType::ReadC:
            return "readc";
        case TokenType::If:
            return "if";
        case TokenType::Else:
            return "else";
        case TokenType::While:
            return "while";
        case TokenType::Function:
            return "function";
        case TokenType::Plus:
            return "+";
        case TokenType::Minus:
            return "-";
        case TokenType::Star:
            return "*";
        case TokenType::Slash:
            return "/";
        case TokenType::Assign:
            return "=";
        case TokenType::Identifier:
            return "id";
        case TokenType::EndOfFile:
            return "EOF";
        case TokenType::Colon:
            return ":";
        case TokenType::Dot:
            return ".";
        case TokenType::Comma:
            return ",";
        case TokenType::LParen:
            return "(";
        case TokenType::RParen:
            return ")";
        default:
            return "unknown";
        }
    }
}  // namespace ToyotaSupraLanguage