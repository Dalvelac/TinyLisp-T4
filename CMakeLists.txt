cmake_minimum_required(VERSION 3.29)
project(Tinylisp_2)

set(CMAKE_CXX_STANDARD 17)

# Add the executable
add_executable(Tinylisp_2
        main.cpp
        src/LoadScript/loadscript.cpp
        src/LoadScript/loadscript.h
        src/Tokenizer/tokenizer.cpp
        src/Tokenizer/tokenizer.h
        src/Operaciones/evaluator.cpp
        src/Operaciones/evaluator.h
        src/Funciones/funciones.cpp
        src/Funciones/funciones.h
        src/Variant/variant.cpp
        src/Variant/variant.h
        src/Guia/guia.cpp
        src/Guia/guia.h
        src/Menu/menu.cpp
        src/Menu/menu.h
)

# Include nlohmann JSON library
target_include_directories(Tinylisp_2 PRIVATE "TUDIRECTORIO")
