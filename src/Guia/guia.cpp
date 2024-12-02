#include "guia.h"
#include <iostream>
#include <string>

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