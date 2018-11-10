#ifndef H_D6664E3798CF4D8EB8DE56DB52B659F8

#define H_D6664E3798CF4D8EB8DE56DB52B659F8

#include <string>
#include <fstream>
#include <map>

namespace GTuring
{
    struct StateMove {
        char onSymbol;
        std::string toState;
        char replaceSymbol;
        char direction;
    };
    struct State {
        std::string name;
        std::map<char, StateMove> moves;

        std::string readable_string() const;
    };
}

#endif // H_D6664E3798CF4D8EB8DE56DB52B659F8
