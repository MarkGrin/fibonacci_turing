#ifndef H_4A4D474B40BF47809BB569DAB84BA554

#define H_4A4D474B40BF47809BB569DAB84BA554

#include "state.hpp"

#include <map>
#include <string_view>

namespace GTuring {

    using tape_index = long;

    class Machine {
        using move_condition = std::pair<char, std::string>;
        using states_container = std::map<std::string, State>;
        using tape_container = std::map<tape_index, char>;

        states_container states_;
        std::string current_state_;

        tape_container tape_;
        tape_index position_ = 0;
        tape_index min_index = 0;
        tape_index max_index = 0;

        std::size_t step_ = 0u;

    public:

        void reset();

        bool read_states (std::string_view filename);
        bool read_tape   (std::string_view filename);

        void snapshot    (std::string_view filename) const;

        const StateMove* get_current_move () const;

        void execute_move (const StateMove& move);

        std::string present_states () const;

        std::size_t states_size () const { return states_.size(); }
        std::size_t current_step () const { return step_; }
        std::size_t tape_size() const { return max_index - min_index; }

        std::size_t interpret_answer() const;

    };
}


#endif // H_4A4D474B40BF47809BB569DAB84BA554
