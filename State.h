#ifndef STATE_H
#define STATE_H

#include <set>
#include <map>
#include <utility>

class State {
public:
    // Constructor por defecto
    State() : is_final(false) {}
    
    // Constructor que recibe si el estado es final o no
    State(bool is_final);

    void add_transition(char input, int next_state);
    std::set<int> get_transitions(char input) const;
    bool is_final_state() const;

private:
    bool is_final;
    std::map<char, std::set<int>> transitions;
};

#endif // STATE_H
