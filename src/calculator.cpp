#include "calculator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
#include <functional>
#include <vector>
#include <variant>
#include <string>

typedef std::vector<std::string> Tokens;

// Variables globales
std::unordered_map<std::string, double> variables;
std::unordered_map<std::string, std::pair<int, std::function<double(const std::vector<double>&)>>> functions;

// Divide una entrada en tokens separados
Tokens tokenize(const std::string& input) {
    Tokens tokens;
    std::stringstream ss(input);
    std::string token;
    while (ss >> token){
        tokens.push_back(token);
    }
    return tokens;
}

// Evalúa una expresión en notación postfija
double evaluate(Tokens& tokens, std::unordered_map<std::string, double> localVariables) {
    std::stack<double> stack;

    while (!tokens.empty()) {
        std::string token = tokens.front();
        tokens.erase(tokens.begin());

        // Operaciones matemáticas básicas y funciones avanzadas
        if (token == "+") {
            if (stack.size() < 2) throw std::runtime_error("Operandos insuficientes para la suma");
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            stack.push(a + b);
        } else if (token == "-") {
            if (stack.size() < 2) throw std::runtime_error("Operandos insuficientes para la resta");
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            stack.push(a - b);
        } else if (token == "*") {
            if (stack.size() < 2) throw std::runtime_error("Operandos insuficientes para la multiplicación");
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            stack.push(a * b);
        } else if (token == "/") {
            if (stack.size() < 2) throw std::runtime_error("Operandos insuficientes para la división");
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            if (b == 0) throw std::runtime_error("División por cero");
            stack.push(a / b);
        } else if (token == "^") {
            if (stack.size() < 2) throw std::runtime_error("Operandos insuficientes para la potenciación");
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            stack.push(pow(a, b));
        } else if (token == "sqrt") {
            if (stack.empty()) throw std::runtime_error("Operandos insuficientes para la raíz cuadrada");
            double a = stack.top(); stack.pop();
            if (a < 0) throw std::runtime_error("La raíz cuadrada de un número negativo no está definida");
            stack.push(sqrt(a));
        } else if (token == "%") {
            if (stack.size() < 2) throw std::runtime_error("Operandos insuficientes para el módulo");
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            stack.push(fmod(a, b));
        } else if (token == "abs") {
            if (stack.empty()) throw std::runtime_error("Operandos insuficientes para el valor absoluto");
            double a = stack.top(); stack.pop();
            stack.push(std::abs(a));
        } else if (token == "neg") {
            if (stack.empty()) throw std::runtime_error("Operandos insuficientes para la negación");
            double a = stack.top(); stack.pop();
            stack.push(-a);
        } else if (token == "sin") {
            if (stack.empty()) throw std::runtime_error("Operandos insuficientes para el seno");
            double a = stack.top(); stack.pop();
            stack.push(std::sin(a));
        } else if (token == "cos") {
            if (stack.empty()) throw std::runtime_error("Operandos insuficientes para el coseno");
            double a = stack.top(); stack.pop();
            stack.push(std::cos(a));
        } else if (token == "tan") {
            if (stack.empty()) throw std::runtime_error("Operandos insuficientes para la tangente");
            double a = stack.top(); stack.pop();
            stack.push(std::tan(a));
        } else if (token == "log10") {
            if (stack.empty()) throw std::runtime_error("Operandos insuficientes para el logaritmo base 10");
            double a = stack.top(); stack.pop();
            if (a <= 0) throw std::runtime_error("El logaritmo base 10 de un número no positivo no está definido");
            stack.push(log10(a));
        } else if (token == "exp") {
            if (stack.empty()) throw std::runtime_error("Operandos insuficientes para la exponencial");
            double a = stack.top(); stack.pop();
            stack.push(exp(a));
        } else if (token == "floor") {
            if (stack.empty()) throw std::runtime_error("Operandos insuficientes para la función floor");
            double a = stack.top(); stack.pop();
            stack.push(floor(a));
        } else if (token == "ceil") {
            if (stack.empty()) throw std::runtime_error("Operandos insuficientes para la función ceil");
            double a = stack.top(); stack.pop();
            stack.push(ceil(a));
        } else if (token == "round") {
            if (stack.empty()) throw std::runtime_error("Operandos insuficientes para la función round");
            double a = stack.top(); stack.pop();
            stack.push(round(a));
        } else if (token == "min") {
            if (stack.size() < 2) throw std::runtime_error("Operandos insuficientes para la función min");
            double a = stack.top(); stack.pop();
            double b = stack.top(); stack.pop();
            stack.push(std::min(a, b));
        } else if (token == "max") {
            if (stack.size() < 2) throw std::runtime_error("Operandos insuficientes para la función max");
            double a = stack.top(); stack.pop();
            double b = stack.top(); stack.pop();
            stack.push(std::max(a, b));
        } else if (token == "push") {
            if (tokens.empty()) throw std::runtime_error("Falta un valor para push");
            std::string value = tokens.front(); tokens.erase(tokens.begin());
            stack.push(std::stod(value));
        } else if (token == "asin") {
            if (stack.empty()) throw std::runtime_error("Operandos insuficientes para el arcoseno");
            double a = stack.top(); stack.pop();
            if (a < -1 || a > 1) throw std::runtime_error("El arcoseno está fuera del rango válido");
            stack.push(asin(a));
        } else if (token == "=") {
            if (tokens.empty()) throw std::runtime_error("Falta el nombre de la variable para la asignación");
            std::string varName = tokens.front(); tokens.erase(tokens.begin());
            if (stack.empty()) throw std::runtime_error("Operandos insuficientes para la asignación");
            double value = stack.top(); stack.pop();
            variables[varName] = value;
            std::cout << "El valor ha sido asignado." << std::endl;
        } else if (token == "acos") {
            if (stack.empty()) throw std::runtime_error("Operandos insuficientes para el arcocoseno");
            double a = stack.top(); stack.pop();
            if (a < -1 || a > 1) throw std::runtime_error("El arcocoseno está fuera del rango válido");
            stack.push(acos(a));
        } else if (token == "atan") {
            if (stack.empty()) throw std::runtime_error("Operandos insuficientes para el arcotangente");
            double a = stack.top(); stack.pop();
            stack.push(atan(a));
        } else if (token == "atan2") {
            if (stack.size() < 2) throw std::runtime_error("Operandos insuficientes para atan2");
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            stack.push(atan2(a, b));
        } else if (token == "hypot") {
            if (stack.size() < 2) throw std::runtime_error("Operandos insuficientes para la hipotenusa");
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            stack.push(hypot(a, b));

        } else if (token == "defun") {
            if (tokens.size() < 3) throw std::runtime_error("Sintaxis incorrecta para la definición de función");
            std::string funcName = tokens.front(); tokens.erase(tokens.begin());
            int paramCount = std::stoi(tokens.front()); tokens.erase(tokens.begin());
            Tokens paramNames(tokens.begin(), tokens.begin() + paramCount);
            tokens.erase(tokens.begin(), tokens.begin() + paramCount);
            Tokens bodyTokens(tokens);
            functions[funcName] = {paramCount, [paramNames, bodyTokens](const std::vector<double>& args) -> double {
                if (args.size() != paramNames.size()) throw std::runtime_error("Número incorrecto de argumentos para la función");
                std::unordered_map<std::string, double> localVars;
                for (size_t i = 0; i < paramNames.size(); ++i) {
                    localVars[paramNames[i]] = args[i];
                }
                Tokens evalTokens = bodyTokens;
                return evaluate(evalTokens, localVars);
            }};
            std::cout << "Función " << funcName << " definida con éxito." << std::endl;
        } else {
            try {
                stack.push(std::stod(token));
            } catch (const std::invalid_argument&) {
                if (localVariables.find(token) != localVariables.end()) {
                    stack.push(localVariables[token]);
                } else if (variables.find(token) != variables.end()) {
                    stack.push(variables[token]);
                } else if (functions.find(token) != functions.end()) {
                    auto& func = functions[token];
                    int argCount = func.first;
                    std::vector<double> args;
                    for (int i = 0; i < argCount; ++i) {
                        if (stack.empty()) throw std::runtime_error("Operandos insuficientes para la función " + token);
                        args.push_back(stack.top());
                        stack.pop();
                    }
                    std::reverse(args.begin(), args.end());
                    stack.push(func.second(args));
                } else {
                    throw std::runtime_error("Variable o función desconocida: " + token);
                }
            }
        }
    }

    if (stack.empty()) throw std::runtime_error("No hay resultado disponible en la pila");
    return stack.top();
}

// Carga un script desde un archivo y lo evalúa
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
            evaluate(tokens); // Evalúa los tokens.
        } catch (const std::exception& e) {
            std::cerr << "Error al evaluar el script: " << e.what() << std::endl;
        }
    }

    if (file.bad()) std::cerr << "Error durante la lectura del archivo " << filename << std::endl;
    file.close();
}

// Ejercicio 1

// Clase Variant
class Variant {
public:
    using Simbolo = std::string;
    using Numero = double;
    using Lista = std::vector<Variant>;
    using Procedimiento = std::function<void()>;

    using TipoVariante = std::variant<Simbolo, Numero, Lista, Procedimiento>;

    Variant(Simbolo simbolo) : valor(simbolo) {}
    Variant(Numero numero) : valor(numero) {}
    Variant(Lista lista) : valor(lista) {}
    Variant(Procedimiento procedimiento) : valor(procedimiento) {}

    template<typename T>
    [[nodiscard]] T obtener() const {
        return std::get<T>(valor);
    }

    template<typename T>
    void establecer(T nuevoValor) {
        valor = nuevoValor;
    }

    // Imprimir el contenido de Variante
    void imprimir() const {
        std::visit([](const auto& val) {
            using T = std::decay_t<decltype(val)>;
            if constexpr (std::is_same_v<T, Simbolo>) {
                std::cout << "Símbolo: " << val << std::endl;
            } else if constexpr (std::is_same_v<T, Numero>) {
                std::cout << "Número: " << val << std::endl;
            } else if constexpr (std::is_same_v<T, Lista>) {
                std::cout << "Lista: [ ";
                for (const auto& item : val) {
                    item.imprimir();
                }
                std::cout << "]" << std::endl;
            } else if constexpr (std::is_same_v<T, Procedimiento>) {
                std::cout << "Procedimiento: (puntero a función)" << std::endl;
            }
        }, valor);
    }

    // Metodo to_string
    std::string to_string() const {
        std::string result;
        std::visit([&result](const auto& val) {
            using T = std::decay_t<decltype(val)>;
            if constexpr (std::is_same_v<T, Simbolo>) {
                result = val;
            } else if constexpr (std::is_same_v<T, Numero>) {
                result = std::to_string(val);
            } else if constexpr (std::is_same_v<T, Lista>) {
                result = "[ ";
                for (const auto& item : val) {
                    result += item.to_string() + " ";
                }
                result += "]";
            } else if constexpr (std::is_same_v<T, Procedimiento>) {
                result = "Procedimiento";
            }
        }, valor);
        return result;
    }

    //Metodo json_string
    std::string json_string() const {
        std::string result;
        std::visit([&result](const auto& val) {
            using T = std::decay_t<decltype(val)>;
            if constexpr (std::is_same_v<T, Simbolo>) {
                result = "\"" + val + "\"";
            } else if constexpr (std::is_same_v<T, Numero>) {
                result = std::to_string(val);
            } else if constexpr (std::is_same_v<T, Lista>) {
                result = "[ ";
                for (const auto& item : val) {
                    result += item.json_string() + ", ";
                }
                result += "]";
            } else if constexpr (std::is_same_v<T, Procedimiento>) {
                result = "\"Procedimiento\"";
            }
        }, valor);
        return result;
    }

    //Ejercicio 4 from_json_string
    std::string from_json_string() const {
        std::string result;
        std::visit([&result](const auto& val) {
            using T = std::decay_t<decltype(val)>;
            if constexpr (std::is_same_v<T, Simbolo>) {
                result = val;
            } else if constexpr (std::is_same_v<T, Numero>) {
                result = std::to_string(val);
            } else if constexpr (std::is_same_v<T, Lista>) {
                result = "[ ";
                for (const auto& item : val) {
                    result += item.from_json_string() + ", ";
                }
                result += "]";
            } else if constexpr (std::is_same_v<T, Procedimiento>) {
                result = "Procedimiento";
            }
        }, valor);
        return result;
    }

private:
    TipoVariante valor;
};

// Función de prueba
void test_variant() {
    Variant v1 = 42.0; // Almacenar un número
    v1.imprimir();

    Variant v2 = std::string("valor_simbolo"); // Almacenar un símbolo como std::string
    v2.imprimir();

    // Almacenar una lista
    Variant::Lista lista = {Variant(1.0), Variant(std::string("elemento")), Variant(3.14)};
    Variant v3 = lista;
    v3.imprimir();

    // Almacenar un procedimiento
    Variant::Procedimiento procedimiento = []() { std::cout << "Ejecutando procedimiento." << std::endl; };
    Variant v4 = procedimiento;  // Utilizar std::function<void()> para la lambda
    v4.imprimir();
    v4.obtener<Variant::Procedimiento>()(); // Llamar al procedimiento

    // Ejercicio 2
    std::cout << "v1 to_string: " << v1.to_string() << std::endl;
    std::cout << "v2 to_string: " << v2.to_string() << std::endl;
    std::cout << "v3 to_string: " << v3.to_string() << std::endl;
    std::cout << "v4 to_string: " << v4.to_string() << std::endl;


    //Ejercicio 3 json_string
    std::cout << "v1 json_string: " << v1.json_string() << std::endl;
    std::cout << "v2 json_string: " << v2.json_string() << std::endl;
    std::cout << "v3 json_string: " << v3.json_string() << std::endl;
    std::cout << "v4 json_string: " << v4.json_string() << std::endl;

    //Ejercicio 4 from_json_string
    std::cout << "v1 from_json_string: " << v1.from_json_string() << std::endl;
    std::cout << "v2 from_json_string: " << v2.from_json_string() << std::endl;
    std::cout << "v3 from_json_string: " << v3.from_json_string() << std::endl;
    std::cout << "v4 from_json_string: " << v4.from_json_string() << std::endl;

}
void mostrarguia() {
    std::string opcion;
    while (true) {
        std::cout << "\n========= GUIA DE FUNCIONALIDADES =========" << std::endl;
        std::cout << "1. Guia de operaciones matematicas" << std::endl;
        std::cout << "2. Guia de carga y ejecucion de scripts" << std::endl;
        std::cout << "3. Guia de funcionalidades avanzadas (Variant)" << std::endl;
        std::cout << "4. Regresar al menu principal" << std::endl;
        std::cout << "===========================================" << std::endl;
        std::cout << "Selecciona una opcion: ";
        std::getline(std::cin, opcion);

        if (opcion == "4") {
            break; // Salir del submenú de guía
        }

        if (opcion == "1") {
            std::cout << "\nGuia de operaciones matematicas:" << std::endl;
            std::cout << "En esta calculadora puedes realizar operaciones matematicas basicas como suma (+), resta (-), multiplicacion (*), division (/), " << std::endl;
            std::cout << "potenciacion (^), y funciones avanzadas como raiz cuadrada (sqrt), seno (sin), coseno (cos), y mas." << std::endl;
            std::cout << "Para realizar una operacion, selecciona la opcion 1 en el menu principal e ingresa la operacion en notacion infija." << std::endl;
            std::cout << "Ejemplo: '3 + 4 * 2' calculara la suma de 3 y 4 multiplicado por 2." << std::endl;
        } else if (opcion == "2") {
            std::cout << "\nGuia de carga y ejecucion de scripts:" << std::endl;
            std::cout << "Puedes cargar y ejecutar scripts que contengan operaciones matematicas. Para hacer esto, selecciona la opcion 2 en el menu principal." << std::endl;
            std::cout << "Se te pedira el nombre del archivo que contiene el script. Asegurate de que el archivo este en el mismo directorio o proporciona la ruta completa." << std::endl;
            std::cout << "El script puede contener varias lineas con operaciones, y cada linea sera evaluada y mostrada." << std::endl;
        } else if (opcion == "3") {
            std::cout << "\nGuia de funcionalidades avanzadas (Variant):" << std::endl;
            std::cout << "La clase Variant permite almacenar diferentes tipos de datos, como numeros, simbolos, listas, y procedimientos." << std::endl;
            std::cout << "1. Numeros: Puedes almacenar un numero y luego acceder a el usando el metodo obtener()." << std::endl;
            std::cout << "2. Simbolos: Puedes almacenar una cadena de texto que actue como un simbolo, por ejemplo, 'miSimbolo'." << std::endl;
            std::cout << "3. Listas: Puedes almacenar una lista de variantes, lo cual te permite tener una coleccion de valores." << std::endl;
            std::cout << "4. Procedimientos: Puedes almacenar una funcion o un procedimiento y ejecutarlo posteriormente." << std::endl;
            std::cout << "Tambien, puedes convertir cualquier instancia de Variant a una cadena de texto con el metodo to_string(), " << std::endl;
            std::cout << "o representarla en formato JSON usando json_string(). Esto es util para ver los datos almacenados de una manera clara." << std::endl;
            std::cout << "Selecciona la opcion 3 en el menu principal para probar estas funcionalidades." << std::endl;
        } else {
            std::cout << "Opcion no valida, por favor intenta de nuevo." << std::endl;
        }
    }
}

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