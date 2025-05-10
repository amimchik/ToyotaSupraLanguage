#include <iostream>
#include <list>

#include <ToyotaSupraLanguage/Lexer.h>

using namespace ToyotaSupraLanguage;

int main() {
    std::string code = "let a = 2\nlet b = a - 2\nfunction fn(a, b)";

    std::list<Token> tokens = Lexer(code).tokenize_all();
    
    for (Token t : tokens) {
        std::cout << t.toString() << std::endl;
    }
}
