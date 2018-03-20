#include "rulesystem.hpp"


std::string RuleSystem::iterate(const std::string &axiom, int iterations)
{
    std::string result = axiom;

    for (int i=0; i<iterations; ++i) {
        std::string word;  // intermediate result

        for (auto& c : result) {
            auto search = rules.find(c);
            if (search != rules.end()) {  // apply rule
                word += search->second;
            } else {  // copy terminal
                word += c;
            }
        }

        result = word;
    }

    return result;
}
