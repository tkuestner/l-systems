#pragma once

#ifndef RULESYSTEM_HPP
#define RULESYSTEM_HPP

#include <string>
#include <unordered_map>


class RuleSystem
{
public:
    using Rules = std::unordered_map<std::string::value_type, std::string>;
    Rules rules;

    RuleSystem(const Rules& rules = {}) : rules(rules) {}

    std::string iterate(const std::string& axiom, int iterations);
};

#endif // RULESYSTEM_HPP
