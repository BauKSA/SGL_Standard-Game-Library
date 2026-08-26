cmake_minimum_required(VERSION 3.15)
project(SGL_Standard-Game-Library LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(LIBS_ROOT "C:/libs")

# Creamos una opción que por defecto está en OFF
option(USE_LIMITED_MEMORY "Activar modo de memoria reducida" OFF)
option(USE_LOWEST_MEMORY "Activar modo de memoria mínima" OFF)

# Opciones de plataforma
option(USE_PLATFORM_PC "Activar PC como plataforma" OFF)
option(USE_PLATFORM_DOS "Activar DOS como plataforma" ON)
option(USE_PLATFORM_GB "Activar Game Boy como plataforma" OFF)

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
file(GLOB_RECURSE HEADERS "include/examples/*.h")

# 1. CREAMOS el ejecutable primero
add_executable(SGL_Standard-Game-Library ${SOURCES} ${HEADERS})

# 2. AHORA definimos los directorios de inclusión para ese target
target_include_directories(SGL_Standard-Game-Library PRIVATE include include/examples)

if(USE_PLATFORM_PC)
    # Definimos laplataforma. Por ahora, PC
    add_definitions(-DPLATFORM_PC)
    # 3. Si estamos en PC, añadimos las librerías necesarias
    add_subdirectory(${LIBS_ROOT}/SDL3-3.4.14 ${CMAKE_BINARY_DIR}/_deps/SDL3 EXCLUDE_FROM_ALL)
    add_subdirectory(${LIBS_ROOT}/SDL3_image-3.4.4 ${CMAKE_BINARY_DIR}/_deps/SDL3_image EXCLUDE_FROM_ALL)
    add_subdirectory(${LIBS_ROOT}/SDL3_mixer-3.2.4 ${CMAKE_BINARY_DIR}/_deps/SDL3_mixer EXCLUDE_FROM_ALL)
    add_subdirectory(${LIBS_ROOT}/SDL3_ttf-3.2.2 ${CMAKE_BINARY_DIR}/_deps/SDL3_ttf EXCLUDE_FROM_ALL)

    target_link_libraries(SGL_Standard-Game-Library PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
        SDL3_mixer::SDL3_mixer
        SDL3_ttf::SDL3_ttf
    )
endif()

if(USE_PLATFORM_DOS)
    add_definitions(-DPLATFORM_DOS)
    target_compile_options(SGL_Standard-Game-Library PRIVATE -fgnu89-inline)
    # Antes: hardcodeado a "C:/libs/allegro". Ahora es una cache var,
    # así cada dev puede pisarla con -DALLEGRO4_ROOT=... sin tocar el archivo.
    set(ALLEGRO4_ROOT "${LIBS_ROOT}/allegro" CACHE PATH "Carpeta con el código fuente de Allegro 4 ya compilado")

    target_include_directories(SGL_Standard-Game-Library PRIVATE
        ${ALLEGRO4_ROOT}/include
    )

    target_link_directories(SGL_Standard-Game-Library PRIVATE
        ${ALLEGRO4_ROOT}/lib/djgpp
    )

    target_link_libraries(SGL_Standard-Game-Library PRIVATE
        alleg
    )
endif()

# Si estás en Windows con Visual Studio (MSVC), esto ayuda:
if(MSVC)
    target_compile_options(SGL_Standard-Game-Library PRIVATE /TC /W4)
endif()