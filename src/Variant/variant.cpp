#include "variant.h"
#include <string>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <json.hpp> // Incluir la biblioteca JSON

using json = nlohmann::json;

// Constructor de la clase Variant para inicializar con diferentes tipos de datos
Variant::Variant(Simbolo simbolo) : valor(simbolo) {}
Variant::Variant(Numero numero) : valor(numero) {}
Variant::Variant(Lista lista) : valor(lista) {}
Variant::Variant(Procedimiento procedimiento) : valor(procedimiento) {}

// Metodo obtener: devuelve el valor almacenado como el tipo solicitado
template<typename T>
T Variant::obtener() const {
    return std::get<T>(valor);
}

// Metodo establecer: cambia el valor almacenado por un nuevo valor
template<typename T>
void Variant::establecer(T nuevoValor) {
    valor = nuevoValor;
}

// Metodo imprimir: imprime el contenido del objeto Variant de acuerdo al tipo almacenado
void Variant::imprimir() const {
    std::visit([](const auto& val) {
        using T = std::decay_t<decltype(val)>;
        if constexpr (std::is_same_v<T, Simbolo>) {
            std::cout << "Simbolo: " << val << std::endl;
        } else if constexpr (std::is_same_v<T, Numero>) {
            std::cout << "Numero: " << val << std::endl;
        } else if constexpr (std::is_same_v<T, Lista>) {
            std::cout << "Lista: [ ";
            for (const auto& item : val) {
                item.imprimir();
            }
            std::cout << "]" << std::endl;
        } else if constexpr (std::is_same_v<T, Procedimiento>) {
            std::cout << "Procedimiento: (puntero a funcion)" << std::endl;
        }
    }, valor);
}

// Metodo to_string: convierte el valor almacenado a su representación en cadena de texto
std::string Variant::to_string() const {
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

// Metodo json_string: convierte el valor almacenado a una cadena de texto en formato JSON
std::string Variant::json_string() const {
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

// Metodo from_json_string: convierte el valor almacenado desde una cadena en formato JSON
std::string Variant::from_json_string() const {
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

// Metodo parse_json_string: convierte una cadena en formato JSON a un objeto Variant
Variant Variant::parse_json_string(const std::string& json_str) {
    // Parsear la cadena JSON usando nlohmann/json
    json parsed_json = json::parse(json_str);

    // Convertir el JSON parseado a una instancia de Variant
    return convert_from_json(parsed_json);
}

// Metodo auxiliar para convertir un objeto JSON a Variant
Variant Variant::convert_from_json(const json& parsed_json) {
    if (parsed_json.is_number()) {
        return Variant(parsed_json.get<Numero>());
    } else if (parsed_json.is_string()) {
        return Variant(parsed_json.get<Simbolo>());
    } else if (parsed_json.is_array()) {
        Lista lista;
        for (const auto& item : parsed_json) {
            lista.push_back(convert_from_json(item));
        }
        return Variant(lista);
    } else if (parsed_json.is_object()) {
        // Manejo de objetos no implementado
        throw std::runtime_error("Objetos JSON no soportados en esta implementación.");
    } else {
        throw std::runtime_error("Tipo de JSON no soportado.");
    }
}

// Prueba del funcionamiento de la clase Variant
void test_variant() {
    // Crear un Variant que almacena un numero
    Variant v1 = 42.0;
    v1.imprimir();

    // Crear un Variant que almacena un simbolo
    Variant v2 = std::string("valor_simbolo");
    v2.imprimir();

    // Crear un Variant que almacena una lista
    Variant::Lista lista = {Variant(1.0), Variant(std::string("elemento")), Variant(3.14)};
    Variant v3 = lista;
    v3.imprimir();

    // Crear un Variant que almacena un procedimiento
    Variant::Procedimiento procedimiento = []() { std::cout << "Ejecutando procedimiento." << std::endl; };
    Variant v4 = procedimiento;
    v4.imprimir();
    v4.obtener<Variant::Procedimiento>()(); // Llamar al procedimiento almacenado

    // Convertir a cadena de texto con to_string
    std::cout << "v1 to_string: " << v1.to_string() << std::endl;
    std::cout << "v2 to_string: " << v2.to_string() << std::endl;
    std::cout << "v3 to_string: " << v3.to_string() << std::endl;
    std::cout << "v4 to_string: " << v4.to_string() << std::endl;

    // Convertir a formato JSON con json_string
    std::cout << "v1 json_string: " << v1.json_string() << std::endl;
    std::cout << "v2 json_string: " << v2.json_string() << std::endl;
    std::cout << "v3 json_string: " << v3.json_string() << std::endl;
    std::cout << "v4 json_string: " << v4.json_string() << std::endl;

    // Convertir desde formato JSON (simulado) con from_json_string
    std::cout << "v1 from_json_string: " << v1.from_json_string() << std::endl;
    std::cout << "v2 from_json_string: " << v2.from_json_string() << std::endl;
    std::cout << "v3 from_json_string: " << v3.from_json_string() << std::endl;
    std::cout << "v4 from_json_string: " << v4.from_json_string() << std::endl;
}
