#pragma once

#include <ToyotaSupraLanguage/Lexer.hpp>
#include <ToyotaSupraLanguage/Parser.hpp>
#include <deque>
#include <memory>
#include <string>
#include <unordered_map>

namespace org::amimchik::tsl::core {

class Reader {
public:
    virtual std::string readLine();
    virtual ~Reader() = default;
};

class StringReader : public Reader {
private:
    std::string str;

public:
    std::string readLine() override;
    StringReader(std::string str);
};

enum class ExecutionContextType {
    IfElse,
    While,
    Scope,
    DoWhile,
    Function,
};

class Value {};

class ExecutionContextNode {
private:
    ExecutionContextType type;
    std::unordered_map<std::string, Value> variables;
    std::string name;
    std::shared_ptr<ExecutionContextNode> parent;
    std::deque<std::shared_ptr<ExecutionContextNode>> children;

public:
    ExecutionContextType getType();
    bool variableExist(const std::string &name);
    Value getVariable(const std::string &name);
    void setVariable(const std::string &name, Value val);
    std::shared_ptr<ExecutionContextNode> operator[](size_t i);
};

class ExecutionContextStack {
private:
    std::shared_ptr<ExecutionContextNode> top;

public:
    void push(std::shared_ptr<ExecutionContextNode> n);
    std::shared_ptr<ExecutionContextNode> pop();
    std::shared_ptr<ExecutionContextNode> operator[](size_t i);
};

class Thread {
private:
    ExecutionContextStack ecs;
    std::deque<std::shared_ptr<Thread>> dependencies;
    std::shared_ptr<Thread> waitingNow;

public:
    bool completed();
    Reader reader;
};

class Executor {
private:
    ExecutionContextNode ecsBottom;
    Parser parser;
    Lexer lexer;
    std::deque<Thread> threads;
    size_t currentThreadIndex;

public:
    Executor();
    void eventLoopIteration();
};

}  // namespace org::amimchik::tsl::core
