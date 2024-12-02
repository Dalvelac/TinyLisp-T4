#include "loadscript.h"
#include "../Operaciones/evaluator.h"
#include "../Tokenizer/tokenizer.h"
#include <fstream>
#include <iostream>
#include <string>

void load_script() {
    std::string filename;
    std::cout << "Ingrese el nombre del archivo: ";
    std::getline(std::cin, filename);

    if (filename.empty()) {
        std::cerr << "Error: No se proporcionó un nombre de archivo." << std::endl;
        return;
    }

    load_script(filename.c_str(), true); // Llama a la versión con argumentos.
}

void load_script(const char* filename, bool show_script) {
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Error: No se pudo abrir el archivo " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (show_script) std::cout << line << std::endl; // Muestra la línea del script si se requiere.

        try {
            Tokens tokens = tokenize(line); // Divide la línea en tokens.
            evaluate(tokens); // Evalúa los tokens. Asegúrate de incluir evaluator.h para usar esta función.
        } catch (const std::exception& e) {
            std::cerr << "Error al evaluar el script: " << e.what() << std::endl;
        }
    }

    if (file.bad()) std::cerr << "Error durante la lectura del archivo " << filename << std::endl;
    file.close();
}
