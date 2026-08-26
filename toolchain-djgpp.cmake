set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR x86)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

if(NOT DJGPP_ROOT)
    if(WIN32)
        set(DJGPP_ROOT "C:/djgpp" CACHE PATH "Ruta de instalación de DJGPP")
    else()
        set(DJGPP_ROOT "/usr/local/djgpp" CACHE PATH "Ruta de instalación de DJGPP")
    endif()
endif()

find_program(DJGPP_C_COMPILER
    NAMES i586-pc-msdosdjgpp-gcc gcc.exe gcc
    PATHS ${DJGPP_ROOT}/bin
    NO_DEFAULT_PATH
)
find_program(DJGPP_CXX_COMPILER
    NAMES i586-pc-msdosdjgpp-g++ g++.exe g++
    PATHS ${DJGPP_ROOT}/bin
    NO_DEFAULT_PATH
)

# NUEVO: detecta make solo, sin necesitar -DCMAKE_MAKE_PROGRAM en la línea de comandos.
find_program(CMAKE_MAKE_PROGRAM
    NAMES make.exe make mingw32-make.exe
    PATHS ${DJGPP_ROOT}/bin
)

if(NOT DJGPP_C_COMPILER)
    message(FATAL_ERROR "No se encontró el compilador DJGPP en ${DJGPP_ROOT}/bin. Definí DJGPP_ROOT correctamente.")
endif()

set(CMAKE_C_COMPILER   ${DJGPP_C_COMPILER})
set(CMAKE_CXX_COMPILER ${DJGPP_CXX_COMPILER})
set(CMAKE_EXECUTABLE_SUFFIX ".exe")

set(CMAKE_FIND_ROOT_PATH ${DJGPP_ROOT}/i586-pc-msdosdjgpp)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)