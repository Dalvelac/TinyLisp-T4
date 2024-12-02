#include "menu.h"
#include "../Guia/guia.h"
#include "../tokenizer/tokenizer.h" // Necesario para tokenize
#include "../Operaciones/evaluator.h" // Necesario para evaluate
#include "../LoadScript/loadscript.h" // Necesario para load_script
#include "../Variant/variant.h" // Necesario para test_variant
#include <iostream>
#include <string>

void mostrarmenu() {
    std::string opcion;

    while (true) {
        std::cout << "\n========= MENU DE LA CALCULADORA =========" << std::endl;
        std::cout << "1. Realizar una operacion matematica" << std::endl;
        std::cout << "2. Cargar y ejecutar un script de operaciones" << std::endl;
        std::cout << "3. Probar funcionalidades avanzadas (Variant)" << std::endl;
        std::cout << "4. Salir" << std::endl;
        std::cout << "5. Guia de usuario" << std::endl;
        std::cout << "==========================================" << std::endl;
        std::cout << "Selecciona una opcion: ";
        std::getline(std::cin, opcion);

        if (opcion == "4") {
            break; // Salir del menu
        }

        if (opcion == "1") {
            std::string input;
            while (true) {
                std::cout << "Introduce una operacion matematica para calcular (o escribe 'end' para regresar al menu): ";
                std::getline(std::cin, input);
                if (input == "end") {
                    break; // Salir de la opcion 1
                }

                try {
                    Tokens tokens = tokenize(input);
                    double resultado = evaluate(tokens);
                    std::cout << resultado << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
            }
        } else if (opcion == "2") {
            std::string filename;
            while (true) {
                std::cout << "Introduce el nombre del archivo de script (o escribe 'end' para regresar al menu): ";
                std::getline(std::cin, filename);
                if (filename == "end") {
                    break; // Salir de la opcion 2
                }

                load_script(filename.c_str(), true);
            }
        } else if (opcion == "3") {
            while (true) {
                std::string input;
                std::cout << "Probar funcionalidades avanzadas (escribe 'end' para regresar al menu): ";
                std::getline(std::cin, input);
                if (input == "end") {
                    break; // Salir de la opcion 3
                }

                // Llamar a la funcion `test_variant`
                test_variant();
            }
        } else if (opcion == "5") {
            mostrarguia(); // Llamar a la funcion de la guia detallada
        } else {
            std::cout << "Opcion no valida, por favor intenta de nuevo." << std::endl;
        }
    }
}