#include "Automaton.h"

/**
 * @brief Constructor de la clase Automaton.
 * @param alphabet Alfabeto del autómata.
 * @param num_states Número total de estados del autómata.
 * @param start_state Estado de arranque del autómata.
 */
Automaton::Automaton(const std::vector<char>& alphabet, int num_states, int start_state)
    : alphabet(alphabet), start_state(start_state) {
    states.resize(num_states);  // Ahora funciona con el constructor por defecto de State
}

/**
 * @brief Añade un estado al autómata.
 * @param id Identificador del estado.
 * @param is_final Indica si es un estado de aceptación.
 * @param transitions Transiciones del estado.
 */
void Automaton::add_state(int id, bool is_final, const std::vector<std::pair<char, int>>& transitions) {
    states[id] = State(is_final);
    for (const auto& transition : transitions) {
        states[id].add_transition(transition.first, transition.second);
    }
}

/**
 * @brief Verifica si el autómata acepta una cadena dada.
 * @param input La cadena de entrada.
 * @return true si la cadena es aceptada, false en caso contrario.
 */
bool Automaton::accepts(const std::string& input) const {
    std::set<int> current_states = {start_state};

    for (char c : input) {
        std::set<int> next_states;

        for (int state : current_states) {
            std::set<int> transitions = states[state].get_transitions(c);
            next_states.insert(transitions.begin(), transitions.end());
        }

        current_states = next_states;
    }

    for (int state : current_states) {
        if (states[state].is_final_state()) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Muestra la información del autómata.
 */
void Automaton::display_info() const {
    std::cout << "Automaton with " << states.size() << " states, start state: " << start_state << std::endl;
}
