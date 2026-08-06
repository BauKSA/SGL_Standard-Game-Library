cmake_minimum_required(VERSION 3.15)
project(SGL_Standard-Game-Library LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Creamos una opción que por defecto está en OFF
option(USE_LIMITED_MEMORY "Activar modo de memoria reducida" OFF)
option(USE_LOWEST_MEMORY "Activar modo de memoria mínima" OFF)

if(USE_LIMITED_MEMORY)
    add_definitions(-DUSE_LIMITED_MEMORY)
    message(STATUS ">>> Compilando en modo LIMITED_MEMORY_SYS")
endif()

if(USE_LOWEST_MEMORY)
    add_definitions(-DLOWEST_MEMORY_SYS)
    message(STATUS ">>> Compilando en modo LOWEST_MEMORY_SYS")
endif()

add_definitions(-DMAX_ENTITIES=8)

# Buscamos los archivos
file(GLOB_RECURSE SOURCES "src/*.c")
file(GLOB_RECURSE HEADERS "include/*.h")

# 1. CREAMOS el ejecutable primero
add_executable(SGL_Standard-Game-Library ${SOURCES} ${HEADERS} "include/systems/active/ActiveEntities.h" "src/systems/active/activeEntities.c" "src/pools.c" "include/types/Memory.h"  "include/systems/movement/MovementSystem.h" "include/components/Position.h" "src/systems/movement/movementSystem.c" "include/systems/physics/PhysicsSystem.h" "src/systems/physics/physicsSystem.c")

# 2. AHORA definimos los directorios de inclusión para ese target
target_include_directories(SGL_Standard-Game-Library PRIVATE include)

# Si estás en Windows con Visual Studio (MSVC), esto ayuda:
if(MSVC)
    target_compile_options(SGL_Standard-Game-Library PRIVATE /TC /W4)
endif()