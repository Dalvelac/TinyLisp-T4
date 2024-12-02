#include "../LoadScript/loadscript.h"
#include <stack>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include "evaluator.h"

// Operaciones basicas
void suma(std::stack<double>& stack) {
    if (stack.size() < 2) throw std::runtime_error("Operandos insuficientes para la suma");
    double b = stack.top(); stack.pop();
    double a = stack.top(); stack.pop();
    stack.push(a + b);
}

void resta(std::stack<double>& stack) {
    if (stack.size() < 2) throw std::runtime_error("Operandos insuficientes para la resta");
    double b = stack.top(); stack.pop();
    double a = stack.top(); stack.pop();
    stack.push(a - b);
}

void multiplicacion(std::stack<double>& stack) {
    if (stack.size() < 2) throw std::runtime_error("Operandos insuficientes para la multiplicacion");
    double b = stack.top(); stack.pop();
    double a = stack.top(); stack.pop();
    stack.push(a * b);
}

void division(std::stack<double>& stack) {
    if (stack.size() < 2) throw std::runtime_error("Operandos insuficientes para la division");
    double b = stack.top(); stack.pop();
    double a = stack.top(); stack.pop();
    if (b == 0) throw std::runtime_error("Division por cero");
    stack.push(a / b);
}

void potencia(std::stack<double>& stack) {
    if (stack.size() < 2) throw std::runtime_error("Operandos insuficientes para la potenciacion");
    double b = stack.top(); stack.pop();
    double a = stack.top(); stack.pop();
    stack.push(std::pow(a, b));
}

void raiz_cuadrada(std::stack<double>& stack) {
    if (stack.empty()) throw std::runtime_error("Operandos insuficientes para la raiz cuadrada");
    double a = stack.top(); stack.pop();
    if (a < 0) throw std::runtime_error("Raiz cuadrada de un numero negativo no esta definida");
    stack.push(std::sqrt(a));
}

void valor_absoluto(std::stack<double>& stack) {
    if (stack.empty()) throw std::runtime_error("Operandos insuficientes para el valor absoluto");
    double a = stack.top(); stack.pop();
    stack.push(std::fabs(a));
}

void seno(std::stack<double>& stack) {
    if (stack.empty()) throw std::runtime_error("Operandos insuficientes para el seno");
    double a = stack.top(); stack.pop();
    stack.push(std::sin(a));
}

void coseno(std::stack<double>& stack) {
    if (stack.empty()) throw std::runtime_error("Operandos insuficientes para el coseno");
    double a = stack.top(); stack.pop();
    stack.push(std::cos(a));
}

void tangente(std::stack<double>& stack) {
    if (stack.empty()) throw std::runtime_error("Operandos insuficientes para la tangente");
    double a = stack.top(); stack.pop();
    stack.push(std::tan(a));
}

void arcoseno(std::stack<double>& stack) {
    if (stack.empty()) throw std::runtime_error("Operandos insuficientes para el arcoseno");
    double a = stack.top(); stack.pop();
    if (a < -1 || a > 1) throw std::runtime_error("El arcoseno esta fuera del rango valido");
    stack.push(std::asin(a));
}

void arcocoseno(std::stack<double>& stack) {
    if (stack.empty()) throw std::runtime_error("Operandos insuficientes para el arcocoseno");
    double a = stack.top(); stack.pop();
    if (a < -1 || a > 1) throw std::runtime_error("El arcocoseno esta fuera del rango valido");
    stack.push(std::acos(a));
}

void arcotangente(std::stack<double>& stack) {
    if (stack.empty()) throw std::runtime_error("Operandos insuficientes para el arcotangente");
    double a = stack.top(); stack.pop();
    stack.push(std::atan(a));
}

void arcotangente2(std::stack<double>& stack) {
    if (stack.size() < 2) throw std::runtime_error("Operandos insuficientes para atan2");
    double b = stack.top(); stack.pop();
    double a = stack.top(); stack.pop();
    stack.push(std::atan2(a, b));
}

void hipotenusa(std::stack<double>& stack) {
    if (stack.size() < 2) throw std::runtime_error("Operandos insuficientes para la hipotenusa");
    double b = stack.top(); stack.pop();
    double a = stack.top(); stack.pop();
    stack.push(std::hypot(a, b));
}

void logaritmo_base10(std::stack<double>& stack) {
    if (stack.empty()) throw std::runtime_error("Operandos insuficientes para el logaritmo base 10");
    double a = stack.top(); stack.pop();
    if (a <= 0) throw std::runtime_error("Logaritmo base 10 de un numero no positivo no esta definido");
    stack.push(std::log10(a));
}

void logaritmo_natural(std::stack<double>& stack) {
    if (stack.empty()) throw std::runtime_error("Operandos insuficientes para el logaritmo natural");
    double a = stack.top(); stack.pop();
    if (a <= 0) throw std::runtime_error("Logaritmo natural de un numero no positivo no esta definido");
    stack.push(std::log(a));
}

void exponencial(std::stack<double>& stack) {
    if (stack.empty()) throw std::runtime_error("Operandos insuficientes para la exponencial");
    double a = stack.top(); stack.pop();
    stack.push(std::exp(a));
}

void modulo(std::stack<double>& stack) {
    if (stack.size() < 2) throw std::runtime_error("Operandos insuficientes para el modulo");
    double b = stack.top(); stack.pop();
    double a = stack.top(); stack.pop();
    if (b == 0) throw std::runtime_error("Division por cero en modulo");
    stack.push(std::fmod(a, b));
}

void piso(std::stack<double>& stack) {
    if (stack.empty()) throw std::runtime_error("Operandos insuficientes para la funcion floor");
    double a = stack.top(); stack.pop();
    stack.push(std::floor(a));
}

void techo(std::stack<double>& stack) {
    if (stack.empty()) throw std::runtime_error("Operandos insuficientes para la funcion ceil");
    double a = stack.top(); stack.pop();
    stack.push(std::ceil(a));
}

void redondeo(std::stack<double>& stack) {
    if (stack.empty()) throw std::runtime_error("Operandos insuficientes para la funcion round");
    double a = stack.top(); stack.pop();
    stack.push(std::round(a));
}

void minimo(std::stack<double>& stack) {
    if (stack.size() < 2) throw std::runtime_error("Operandos insuficientes para la funcion min");
    double b = stack.top(); stack.pop();
    double a = stack.top(); stack.pop();
    stack.push(std::min(a, b));
}

void maximo(std::stack<double>& stack) {
    if (stack.size() < 2) throw std::runtime_error("Operandos insuficientes para la funcion max");
    double b = stack.top(); stack.pop();
    double a = stack.top(); stack.pop();
    stack.push(std::max(a, b));
}

// Implementacion de defun
void defun(Tokens& tokens) {
    if (tokens.size() < 3) {
        throw std::runtime_error("Sintaxis incorrecta para la definicion de funcion");
    }

    std::string funcName = tokens.front();
    tokens.erase(tokens.begin());

    int paramCount = std::stoi(tokens.front());
    tokens.erase(tokens.begin());

    // Extraer nombres de parametros
    Tokens paramNames(tokens.begin(), tokens.begin() + paramCount);
    tokens.erase(tokens.begin(), tokens.begin() + paramCount);

    // Extraer el cuerpo de la funcion
    Tokens bodyTokens = tokens;

    // Registrar la funcion en el mapa
    functions[funcName] = {paramCount, [paramNames, bodyTokens](const std::vector<double>& args) -> double {
        if (args.size() != paramNames.size()) {
            throw std::runtime_error("Numero incorrecto de argumentos para la funcion");
        }

        // Crear un mapa local para los parametros
        std::unordered_map<std::string, double> localVars;
        for (size_t i = 0; i < paramNames.size(); ++i) {
            localVars[paramNames[i]] = args[i];
        }

        // Evaluar el cuerpo de la funcion con las variables locales
        Tokens evalTokens = bodyTokens;
        return evaluate(evalTokens, localVars);
    }};

    std::cout << "Funcion '" << funcName << "' definida exitosamente con " << paramCount << " parametro(s)." << std::endl;
}

// Evaluador principal
double evaluate(Tokens& tokens, std::unordered_map<std::string, double> localVariables) {
    std::stack<double> stack;

    while (!tokens.empty()) {
        std::string token = tokens.front();
        tokens.erase(tokens.begin());

        if (token == "defun") {
            defun(tokens);
        } else if (token == "+") {
            suma(stack);
        } else if (token == "-") {
            resta(stack);
        } else if (token == "*") {
            multiplicacion(stack);
        } else if (token == "/") {
            division(stack);
        } else if (token == "^") {
            potencia(stack);
        } else if (token == "sqrt") {
            raiz_cuadrada(stack);
        } else if (token == "abs") {
            valor_absoluto(stack);
        } else if (token == "sin") {
            seno(stack);
        } else if (token == "cos") {
            coseno(stack);
        } else if (token == "tan") {
            tangente(stack);
        } else if (token == "asin") {
            arcoseno(stack);
        } else if (token == "acos") {
            arcocoseno(stack);
        } else if (token == "atan") {
            arcotangente(stack);
        } else if (token == "atan2") {
            arcotangente2(stack);
        } else if (token == "hypot") {
            hipotenusa(stack);
        } else if (token == "log10") {
            logaritmo_base10(stack);
        } else if (token == "ln") {
            logaritmo_natural(stack);
        } else if (token == "exp") {
            exponencial(stack);
        } else if (token == "%") {
            modulo(stack);
        } else if (token == "floor") {
            piso(stack);
        } else if (token == "ceil") {
            techo(stack);
        } else if (token == "round") {
            redondeo(stack);
        } else if (token == "min") {
            minimo(stack);
        } else if (token == "max") {
            maximo(stack);
        } else {
            // Manejo de numeros, variables y funciones definidas por el usuario
            try {
                stack.push(std::stod(token));
            } catch (...) {
                if (localVariables.find(token) != localVariables.end()) {
                    stack.push(localVariables[token]);
                } else if (variables.find(token) != variables.end()) {
                    stack.push(variables[token]);
                } else if (functions.find(token) != functions.end()) {
                    // Llamada a una funcion definida por el usuario
                    auto& func = functions[token];
                    int argCount = func.first;
                    std::vector<double> args;

                    // Obtener argumentos de la pila
                    for (int i = 0; i < argCount; ++i) {
                        if (stack.empty()) throw std::runtime_error("Operandos insuficientes para la funcion " + token);
                        args.push_back(stack.top());
                        stack.pop();
                    }
                    std::reverse(args.begin(), args.end());

                    // Llamar a la funcion y almacenar el resultado en la pila
                    stack.push(func.second(args));
                } else {
                    throw std::runtime_error("Variable o funcion desconocida: " + token);
                }
            }
        }
    }

    if (stack.size() != 1) throw std::runtime_error("Error: pila inconsistente al final de la evaluacion");
    return stack.top();
}
