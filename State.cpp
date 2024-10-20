#include "State.h"

/**
 * @brief Constructor de la clase State.
 * @param is_final Indica si el estado es final.
 */
State::State(bool is_final) : is_final(is_final) {}

/**
 * @brief Añade una transición desde este estado a otro.
 * @param input El símbolo de entrada para la transición.
 * @param next_state El estado al que se transiciona.
 */
void State::add_transition(char input, int next_state) {
    transitions[input].insert(next_state);
}

/**
 * @brief Obtiene el conjunto de estados a los que se puede transicionar con un símbolo.
 * @param input El símbolo de entrada.
 * @return Un conjunto de estados destino.
 */
std::set<int> State::get_transitions(char input) const {
    auto it = transitions.find(input);
    if (it != transitions.end()) {
        return it->second;
    }
    return {};
}

/**
 * @brief Indica si el estado es un estado final.
 * @return true si es un estado final, false en caso contrario.
 */
bool State::is_final_state() const {
    return is_final;
}
