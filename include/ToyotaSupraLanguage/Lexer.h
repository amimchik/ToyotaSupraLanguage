#include <string>
#include <list>
#include <map>
#include <cctype>
#include <stdexcept>
#include <cstdint>

#pragma once

namespace ToyotaSupraLanguage {

	enum class TokenType {
		Let,

		Identifier,

		NumberLiteral,
		StringLiteral,

		Print,
		PrintL,
		ReadL,
		ReadC,

		If,
		Else,
		While,

		Function,

		Plus,
		Minus,
		Star,
		Slash,

		Assign,

		Equals,
		NotEquals,
		LessThan,
		GreatherThan,
		LessEqualThan,
		GreatherEqualThen,

		Colon,
		Comma,
		Dot,

		LBracket,
		RBracket,
		LBrace,
		RBrace,
		LParen,
		RParen,

		EndOfFile,
	};

	std::string tokenTypeToString(TokenType t);


	struct Token {
		TokenType type;
		std::string stringValue;

		static Token createSimple(TokenType type);
		static Token createIdentifier(std::string idV);
		static Token createNumber(uint64_t v);
		static Token createStringLiteral(std::string strV);
		Token();

		std::string toString() const;
	};

	class Lexer {
	private:
		size_t pos;
		std::string input;
		const std::string specChars = "+-*/<>=!{}[]():.,";
		const std::map<std::string, Token> specs = {
			{ "+", Token::createSimple(TokenType::Plus) },
			{ "-", Token::createSimple(TokenType::Minus) },
			{ "*", Token::createSimple(TokenType::Star) },
			{ "/", Token::createSimple(TokenType::Slash) },
			{ "=", Token::createSimple(TokenType::Assign) },
			{ "==", Token::createSimple(TokenType::Equals) },
			{ "!=", Token::createSimple(TokenType::NotEquals) },
			{ ">", Token::createSimple(TokenType::GreatherThan) },
			{ "<", Token::createSimple(TokenType::LessThan) },
			{ ">=", Token::createSimple(TokenType::GreatherEqualThen) },
			{ "<=", Token::createSimple(TokenType::LessEqualThan) },
			{ "(", Token::createSimple(TokenType::LParen) },
			{ ")", Token::createSimple(TokenType::RParen) },
			{ "{", Token::createSimple(TokenType::LBrace) },
			{ "}", Token::createSimple(TokenType::RBrace) },
			{ "[", Token::createSimple(TokenType::LBracket) },
			{ "]", Token::createSimple(TokenType::RBracket) },
			{ ".", Token::createSimple(TokenType::Dot) },
			{ ",", Token::createSimple(TokenType::Comma) },
		};
		const std::map<std::string, Token> keywords = {
			{ "let", Token::createSimple(TokenType::Let) },
			{ "print", Token::createSimple(TokenType::Print) },
			{ "printl", Token::createSimple(TokenType::PrintL) },
			{ "readl", Token::createSimple(TokenType::ReadL) },
			{ "readc", Token::createSimple(TokenType::ReadC) },
			{ "if", Token::createSimple(TokenType::If) },
			{ "else", Token::createSimple(TokenType::Else) },
			{ "while", Token::createSimple(TokenType::While) },
			{ "function", Token::createSimple(TokenType::Function) }
		};
		int strIndexOf(const std::string& str, char c);
		bool inRange(size_t i);
		char next();
		char peek(int offset);
		char current();
		Token tokenize_word();
		Token tokenize_number();
		Token tokenize_special();
		Token tokenize_str_lit();
	public:
		Lexer(std::string& input);
		std::list<Token> tokenize_all();
		Token get_next_token();
	};

}
