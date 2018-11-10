#include <iostream>
#include "machine.hpp"

int main (int argc, const char** argv) {
    if (argc < 2) {
        std::cout << "Not enough arguments!\n";
        return 1;
    }
    std::string dir_name(argv[1]);
    std::string states_name = dir_name + "/in_states.txt";
    std::string input_name = dir_name + "/input_tape.txt";
    std::string snapshot_name = dir_name + "/snapshot";

    GTuring::Machine machine;
    std::cout << "\nLoading states from " << dir_name << " ...\n";
    if ( !machine.read_states(states_name) ) {
        std::cout << "Error on loading states:" + states_name << "\n";
        return 2;
    }
    std::cout << "Loaded states:" << machine.states_size() << "\n";
    std::cout << machine.present_states() << "\n";

    std::cout << "Loading input tape...\n";
    if ( !machine.read_tape(input_name) ) {
        std::cout << "Error on loading input tape:" << input_name << "\n";
        return 3;
    }
    std::cout << "Tape ready(used length:" << machine.tape_size() << ")\n\n";
    std::cout << "Executing..." << "\n";
    machine.snapshot(snapshot_name);
    while (true) {
        auto move = machine.get_current_move();
        if (!move)
            break;
        machine.execute_move(*move);
        machine.snapshot(snapshot_name);
    }
    std::cout << "Execution stopped on step:" << machine.current_step () << "\n";
    std::cout << "Tape contains possible answer:" << machine.interpret_answer() << "\n\n";


    return 0;
}
