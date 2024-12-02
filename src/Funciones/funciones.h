#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
#include "../Operaciones/evaluator.h"

// Declaracion de variables globales usando extern
extern std::unordered_map<std::string, std::pair<int, std::function<double(const std::vector<double>&)>>> functions;
extern std::unordered_map<std::string, double> variables;

// Declaracion de funciones
void define_function(const Tokens& tokens);

#endif // FUNCIONES_H
