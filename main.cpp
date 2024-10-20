#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Automaton.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {  // Ahora esperamos dos argumentos (automata y cadenas)
        std::cerr << "Uso: " << argv[0] << " <archivo_automata.fa> <archivo_cadenas.txt>" << std::endl;
        return 1;
    }

    // Cargar el archivo del autómata
    std::ifstream automaton_file(argv[1]);
    if (!automaton_file) {
        std::cerr << "Error al abrir el archivo de autómata." << std::endl;
        return 1;
    }

    std::string line;
    std::vector<char> alphabet;
    
    // Leer el alfabeto
    std::getline(automaton_file, line);
    std::istringstream alpha_stream(line);
    char symbol;
    while (alpha_stream >> symbol) {
        alphabet.push_back(symbol);
    }

    int num_states;
    automaton_file >> num_states;
    if (num_states <= 0) {
        std::cerr << "Error: Número de estados no válido." << std::endl;
        return 1;
    }

    int start_state;
    automaton_file >> start_state;

    // Comprobar estado inicial
    if (start_state < 0 || start_state >= num_states) {
        std::cerr << "Error: Estado inicial fuera de rango." << std::endl;
        return 1;
    }

    Automaton automaton(alphabet, num_states, start_state);
    
    // Leer estados
    for (int i = 0; i < num_states; ++i) {
        int id, is_final, num_transitions;
        automaton_file >> id >> is_final >> num_transitions;

        // Comprobar si el estado está correctamente definido
        if (id < 0 || id >= num_states) {
            std::cerr << "Error: Identificador de estado fuera de rango." << std::endl;
            return 1;
        }

        std::vector<std::pair<char, int>> transitions;
        for (int j = 0; j < num_transitions; ++j) {
            char input;
            int next_state;
            automaton_file >> input >> next_state;

            // Comprobar transiciones
            if (std::find(alphabet.begin(), alphabet.end(), input) == alphabet.end() && input != '&') {
                std::cerr << "Error: Símbolo de transición no válido." << std::endl;
                return 1;
            }
            if (next_state < 0 || next_state >= num_states) {
                std::cerr << "Error: Estado destino fuera de rango." << std::endl;
                return 1;
            }
            transitions.emplace_back(input, next_state);
        }
        
        automaton.add_state(id, is_final == 1, transitions);
    }

    automaton.display_info();

    // Cargar el archivo de cadenas
    std::ifstream cadenas_file(argv[2]);
    if (!cadenas_file) {
        std::cerr << "Error al abrir el archivo de cadenas." << std::endl;
        return 1;
    }

    // Redirigir la salida a output.txt
    std::ofstream output_file("output.txt"); // Se sobrescribe el archivo si ya existe
    if (!output_file) {
        std::cerr << "Error al abrir el archivo de salida." << std::endl;
        return 1;
    }

    // Leer cada cadena del archivo de cadenas
    std::string cadena;
    while (std::getline(cadenas_file, cadena)) {
        bool resultado = automaton.accepts(cadena);
        if (resultado) {
            output_file << "La cadena \"" << cadena << "\" es aceptada." << std::endl;
        } else {
            output_file << "La cadena \"" << cadena << "\" es rechazada." << std::endl;
        }
    }

    output_file.close();  // Cerrar el archivo de salida
    cadenas_file.close();  // Cerrar el archivo de cadenas
    automaton_file.close();  // Cerrar el archivo del autómata

    std::cout << "Resultados guardados en output.txt." << std::endl;

    return 0;
}
