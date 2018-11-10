#include "state.hpp"

namespace GTuring
{
    std::string State::readable_string() const {
        std::string result;
        for (const auto& move : moves) {
            if (!result.empty())
                result += "\n";
            result += "(";
            result += name;
            result += ", ";
            result += move.second.onSymbol;
            result += ") -> (";
            result += move.second.toState;
            result += ", ";
            result += move.second.replaceSymbol;
            result += ", ";
            result += move.second.direction;
            result += ")";
        }

        return result;
    }
}