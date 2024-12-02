#include "src/calculator.h"
#include <iostream>

int main() {
    std::string input;
    bool continuar = true;

    while (continuar) {
        mostrarmenu(); // Ahora se llama a mostrarMenu() desde calculator.cpp
        std::getline(std::cin, input);

        if (input == "1") {
            try {
                std::cout << "Introduce una operación matemática para calcular: ";
                std::getline(std::cin, input);
                Tokens tokens = tokenize(input);
                double resultado = evaluate(tokens);
                std::cout <<  resultado << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        } else if (input == "2") {
            try {
                load_script();
            } catch (const std::exception& e) {
                std::cerr << "Error al cargar el script: " << e.what() << std::endl;
            }
        } else if (input == "3") {
            try {
                test_variant();
            } catch (const std::exception& e) {
                std::cerr << "Error al probar la funcionalidad de variantes: " << e.what() << std::endl;
            }
        } else if (input == "4") {
            continuar = false;
            std::cout << "Saliendo de la calculadora. ¡Hasta luego!" << std::endl;
        } else {
            std::cerr << "Opción inválida. Por favor, selecciona una opción válida." << std::endl;
        }
    }
    return 0;
}