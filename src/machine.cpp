#include "machine.hpp"

namespace GTuring {

    void Machine::reset() {
        *this = Machine();
    }

    bool Machine::read_states(std::string_view filename) {
        try {
            std::fstream file;
            file.open(filename.data(), std::ios::in);
            while (file) {
                std::string name;
                if ( !(file >> name) )
                    return true;
                auto it = states_.find(name);
                if (it == states_.end())
                    states_[name] = State{name};
                it = states_.find(name);

                StateMove move;
                if ( !(file >> move.onSymbol) )
                    return true;
                if ( !(file >> move.toState) )
                    return true;
                if ( !(file >> move.replaceSymbol) )
                    return true;
                if ( !(file >> move.direction) )
                    return true;

                it->second.moves[move.onSymbol] = std::move(move);

                if ( current_state_.empty() )
                    current_state_ = name;
            }
        }
        catch (...) {// naughty error handling. Is it memory overflow? Is it file error? Is it something else?
            return false;
        }
        return true;
    }

    void Machine::snapshot(std::string_view filename) const {
        std::string number = std::to_string(step_);
        number = std::string(12 - number.size(), '0') + number;
        std::string postfixed_filename = std::string(filename) + "_" + number + ".txt";
        std::fstream file;
        file.open (postfixed_filename, std::ios::out);
        file << "step:" << step_ << "\n";
        file << "current state:" << current_state_ << "\n";
        auto move = get_current_move();
        if (!move)
            file << "current move: HALT" << "\n\n";
        else
            file << "current move: (" << current_state_ << ", "
                 << move->onSymbol << ") -> (" << move->toState << ", "
                 << move->replaceSymbol << ", " << move->direction << ")\n\n";
        file << "--- --- TAPE --- ---\n";
        file << "   index  value\n\n";
        for (tape_index i = min_index; i <= max_index; i++) {
            char value = '_';
            {
                auto it = tape_.find(i);
                if ( it != tape_.end())
                    value = it->second;
            }
            bool negative = i < 0;
            tape_index index = abs(i);

            std::string index_str = std::to_string(index);
            std::size_t padding = 6 - index_str.size() - (negative ? 1 : 0);
            if (position_ == i)
                file << "x";
            else
                file << " ";
            for (std::size_t i = 0; i < padding; i++)
                file << " ";
            file << i << "   " << value << "\n";
        }
    }

    std::string Machine::present_states () const {
        std::string result;
        for (const auto& state : states_)
            result += state.second.readable_string() + "\n";
        return result;
    }

    const StateMove* Machine::get_current_move () const {
        char currentSymbol = '_';
        {
            auto it = tape_.find(position_);
            if (it != tape_.end())
                currentSymbol = it->second;
        }
        auto it = states_.find(current_state_);
        if (it == states_.end())
            return nullptr;

        const auto& moves = it->second.moves;
        const auto& move  = moves.find(currentSymbol);

        return move != moves.end() ? &move->second : nullptr;
    }

    void Machine::execute_move (const StateMove& move) {
        current_state_ = move.toState;
        tape_[position_] = move.replaceSymbol;

        if ( move.direction == 'R' )
            position_++;
        if ( move.direction == 'L' )
            position_--;

        max_index = max_index > position_? max_index : position_;
        min_index = min_index < position_? min_index : position_;

        step_++;
    }

    bool Machine::read_tape   (std::string_view filename) {
        try {
            std::fstream file;
            file.open(filename.data(), std::ios::in);
            std::size_t index = 0;
            char value = 0;
            while (file >> value) {
                if ( value == 'X' )
                    return true;
                tape_[max_index] = value;
                max_index++;
            }
        } catch (...) {
            return false;
        }
        return true;
    }

    std::size_t Machine::interpret_answer() const {
        std::size_t result = 0;
        for (tape_index i = position_; i < max_index; i++) {
            char value = '_';
            {
                auto it = tape_.find(i);
                if (it != tape_.end())
                    value = it->second;
            }
            if (value == '1')
                result++;
            else
                break;
        }
        return result ? result - 1 : 0;
    }

}
