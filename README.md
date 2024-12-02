https://github.com/Dalvelac/TinyLisp-T4

# Tiny Lisp Tema 4


## Características

- Implementación de operaciones matemáticas básicas (suma, resta, multiplicación, división, potencias, etc.).

- Definición y evaluación de funciones personalizadas utilizando defun.

- Soporte para almacenar valores en variables y trabajar con expresiones.

- Capacidad para imprimir, convertir a cadena, y representar valores en formato JSON.

- Uso de la librería nlohmann/json para manipular objetos JSON.


## Estructura del Proyecto

El proyecto está organizado en diferentes archivos, cada uno con una responsabilidad específica:

### Directorios y Archivos

`main.cpp`: Archivo principal que contiene la lógica para iniciar el programa y gestionar el flujo de ejecución principal.

`src/LoadScript/loadscript.cpp`, `loadscript.h`: Encargado de cargar scripts y realizar la lectura de código fuente desde archivos o entradas. Se ocupa de la interpretación básica de scripts.

`src/Tokenizer/tokenizer.cpp`, `tokenizer.h`: Implementa un tokenizador que convierte el código fuente en una lista de tokens para ser interpretados por el evaluador.

`src/Operaciones/evaluator.cpp`, `evaluator.h`: Contiene la lógica principal del evaluador, que se encarga de interpretar y ejecutar los tokens obtenidos del código fuente. También contiene la implementación de las funciones básicas y de usuario.

`src/Funciones/funciones.cpp`, `funciones.h`: Contiene funciones matemáticas predefinidas y el manejo de defun para definir nuevas funciones. Almacena las funciones en un mapa global para su uso posterior.

`src/Variant/variant.cpp`, `variant.h`: Implementa la clase Variant, que es capaz de almacenar diferentes tipos de datos, incluyendo números, listas, símbolos y procedimientos. También incluye funcionalidades para trabajar con JSON mediante la librería nlohmann/json.

`src/Guia/guia.cpp`, `guia.h`: Proporciona ayuda y documentación interna para el uso del programa, mostrando cómo se puede interactuar con el mismo.

`src/Menu/menu.cpp`, `menu.h`: Implementa la lógica para la interacción con el usuario a través de menús, permitiendo al usuario elegir opciones de ejecución.

## Requisitos

- Un compilador compatible con C++17 o superior.

- CMake para construir el proyecto.

- nlohmann/json: Biblioteca de C++ para manejar JSON. Asegúrate de incluirla en tu proyecto.

### Instalación de la Librería JSON

Puedes descargar la librería JSON desde su repositorio de [Github](https://github.com/nlohmann/json). Simplemente descargate esta libreria, extraela a tu escritorio y cambia el target_include_directories a el path donde se encuentra.

## Compilación del Proyecto

A continuación se detallan los pasos para compilar el proyecto utilizando CMake:

Clona el repositorio del proyecto y asegúrate de que todas las dependencias estén disponibles.

Asegúrate de tener la librería JSON disponible (puedes copiar el archivo json.hpp al directorio include de tu proyecto).

Crea un directorio de compilación:
```
mkdir build
cd build
```
Ejecuta CMake para generar los archivos de construcción:

`cmake ..`

Compila el proyecto con Make:

`make`

Esto generará el ejecutable Tinylisp_2 en el directorio build.

## Uso

Al ejecutar el programa, se mostrará un menú interactivo donde podrás ingresar expresiones matemáticas, definir nuevas funciones con defun, evaluar scripts, y convertir valores a formato JSON.
