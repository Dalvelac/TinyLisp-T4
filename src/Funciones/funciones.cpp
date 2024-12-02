#include "funciones.h"
#include "../Operaciones/evaluator.h"
#include <iostream>
#include <unordered_map>
#include <functional>

// Definicion de variables globales (sin extern)
std::unordered_map<std::string, std::pair<int, std::function<double(const std::vector<double>&)>>> functions;
std::unordered_map<std::string, double> variables;

// Implementacion de la funcion define_function
void define_function(const Tokens& tokens) {
    if (tokens.size() < 3) throw std::runtime_error("Sintaxis incorrecta para la definicion de funcion");

    std::string funcName = tokens[0];
    int paramCount = std::stoi(tokens[1]);
    Tokens paramNames(tokens.begin() + 2, tokens.begin() + 2 + paramCount);
    Tokens bodyTokens(tokens.begin() + 2 + paramCount, tokens.end());

    functions[funcName] = {paramCount, [paramNames, bodyTokens](const std::vector<double>& args) -> double {
        if (args.size() != paramNames.size()) throw std::runtime_error("Numero incorrecto de argumentos para la funcion");

        std::unordered_map<std::string, double> localVars;
        for (size_t i = 0; i < paramNames.size(); ++i) {
            localVars[paramNames[i]] = args[i];
        }

        Tokens evalTokens = bodyTokens;
        return evaluate(evalTokens, localVars);
    }};

    std::cout << "Funcion '" << funcName << "' definida exitosamente con " << paramCount << " parametro(s)." << std::endl;
}
