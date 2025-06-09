#include <ToyotaSupraLanguage/Lexer.hpp>

namespace org::amimchik::tsl::core {

class ASTNode {
};

struct ParseInfo {
    bool completed;
    bool correct;
};

class Parser {
private:
    std::deque<Token> tokens;

public:
    void load(std::deque<Token> tokens);
    ParseInfo check();
    ASTNode parse();
};

}  // namespace org::amimchik::tsl::core
