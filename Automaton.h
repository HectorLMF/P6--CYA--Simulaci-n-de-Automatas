#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <vector>
#include <string>
#include <set>
#include <iostream>
#include <algorithm>  // Para std::find
#include "State.h"

class Automaton {
public:
    Automaton(const std::vector<char>& alphabet, int num_states, int start_state);
    void add_state(int id, bool is_final, const std::vector<std::pair<char, int>>& transitions);
    bool accepts(const std::string& input) const;
    void display_info() const;

private:
    std::vector<State> states;
    std::vector<char> alphabet;
    int start_state;
};

#endif // AUTOMATON_H
