#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <stack>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional> // Para std::function

// Alias para los tokens
using Tokens = std::vector<std::string>;

// Declaración de variables globales
extern std::unordered_map<std::string, double> variables;
extern std::unordered_map<std::string, std::pair<int, std::function<double(const std::vector<double>&)>>> functions; // Declaración de functions

// Prototipos de operaciones básicas
void suma(std::stack<double>& stack);
void resta(std::stack<double>& stack);
void multiplicacion(std::stack<double>& stack);
void division(std::stack<double>& stack);

// Prototipos de operaciones avanzadas
void potencia(std::stack<double>& stack);
void raiz_cuadrada(std::stack<double>& stack);
void valor_absoluto(std::stack<double>& stack);
void seno(std::stack<double>& stack);
void coseno(std::stack<double>& stack);
void tangente(std::stack<double>& stack);
void arcoseno(std::stack<double>& stack);
void arcocoseno(std::stack<double>& stack);
void arcotangente(std::stack<double>& stack);
void arcotangente2(std::stack<double>& stack);
void hipotenusa(std::stack<double>& stack);
void logaritmo_base10(std::stack<double>& stack);
void logaritmo_natural(std::stack<double>& stack);
void exponencial(std::stack<double>& stack);
void modulo(std::stack<double>& stack);
void piso(std::stack<double>& stack);
void techo(std::stack<double>& stack);
void redondeo(std::stack<double>& stack);
void minimo(std::stack<double>& stack);
void maximo(std::stack<double>& stack);
double evaluate(Tokens& tokens, std::unordered_map<std::string, double> localVariables);
void defun(Tokens& tokens);

extern std::unordered_map<std::string, double> variables;
extern std::unordered_map<std::string, std::pair<int, std::function<double(const std::vector<double>&)>>> functions;

double evaluate(std::vector<std::string>& tokens, std::unordered_map<std::string, double> localVariables = {});


#endif
