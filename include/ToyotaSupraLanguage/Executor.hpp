#pragma once

#include <deque>
#include <string>
#include <unordered_map>

namespace org::amimchik::tsl::core {

enum class ExecutionContextType {
    IfElse,
    While,
    Scope,
    DoWhile,
    Function,
};

class TSLValue {};

class ExecutionContext {
private:
    ExecutionContextType type;
    std::unordered_map<std::string, TSLValue> variables;
    std::string name;

public:
    ExecutionContextType getType();
    bool variableExist(const std::string &name);
    TSLValue getVariable(const std::string &name);
    void setVariable(const std::string &name, TSLValue val);
};

class ExecutionContextStack {
private:
    std::deque<ExecutionContext> ecs;

public:
    void push(ExecutionContext executionContext);
    ExecutionContext pop();
    ExecutionContext &operator[](size_t i);
    size_t size();
};

class Executor {
private:
    ExecutionContextStack ecs;

public:
    Executor();
    void executeLine(std::string line);
};

}  // namespace org::amimchik::tsl::core
