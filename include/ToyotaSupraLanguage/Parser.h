#pragma once

#include <list>
#include <memory>
#include <map>
#include <string>

#include <ToyotaSupraLanguage/Lexer.h>

namespace ToyotaSupraLanguage {

    enum class NodeType {
        Addition,
        Substraction,
        Multiplipication,
        Division,

        IfElse,
        While,

        ObjectDecl,
        ArrayDecl,

        FunctionDecl,
        FunctionCall,

        VariableDecl,
        VariableCall,

        NumberLiteral,
        StringLiteral,

        MemberAccess,

        Assign,
    };

    class ASTNode {
    private:
        NodeType type;
        // Binary ops / assign
        std::unique_ptr<ASTNode> left;
        std::unique_ptr<ASTNode> right;
        // IfElse / While
        std::unique_ptr<ASTNode> condition;
        std::unique_ptr<ASTNode> thenN;
        std::unique_ptr<ASTNode> elseN;
        // ArrayLiteral
        std::list<std::unique_ptr<ASTNode>> arrContent;
        // ObjectLiteral
        std::list<std::pair<std::string, std::unique_ptr<ASTNode>>> objectContent;
        // memberAccess
        std::string memberName;
        std::unique_ptr<ASTNode> parent;
    public:
        NodeType getType();
        void setType(NodeType type);
        std::list<std::unique_ptr<ASTNode>> getChildren();
    };

    class Parser {
    private:

    public:
        Parser(Lexer lexer);
        std::unique_ptr<ASTNode> parse();
    };
}
