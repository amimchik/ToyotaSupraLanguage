#pragma once

#include <list>
#include <memory>

#include "Lexer.h"

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
        // Binary ops
        ASTNode* left;
        ASTNode* right;
        // 
        std::list<ASTNode> nodes;
    public:
        NodeType getType();
        void setType(NodeType type);
        std::list<ASTNode> getChildren();
    };

    class Parser {
    private:

    public:
        Parser(Lexer lexer);
        std::unique_ptr<ASTNode> parse();
    };
}