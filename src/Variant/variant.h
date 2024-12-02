#ifndef VARIANT_H
#define VARIANT_H

#include <variant>
#include <string>
#include <vector>
#include <functional>
#include <json.hpp> // Incluir la biblioteca JSON

using json = nlohmann::json;

class Variant {
public:
    using Simbolo = std::string;
    using Numero = double;
    using Lista = std::vector<Variant>;
    using Procedimiento = std::function<void()>;

    Variant(Simbolo simbolo);
    Variant(Numero numero);
    Variant(Lista lista);
    Variant(Procedimiento procedimiento);

    template<typename T>
    T obtener() const;

    template<typename T>
    void establecer(T nuevoValor);

    void imprimir() const;
    std::string to_string() const;
    std::string json_string() const;
    std::string from_json_string() const;

    // Declaraciones de los métodos parse_json_string y convert_from_json
    static Variant parse_json_string(const std::string& json_str);
    static Variant convert_from_json(const json& parsed_json);

private:
    std::variant<Simbolo, Numero, Lista, Procedimiento> valor;
};

#endif // VARIANT_H
