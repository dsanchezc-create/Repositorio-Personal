cmake_minimum_required(VERSION 3.10)
project(CookieSelection)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

# 1. Programa principal a enviar a Kattis
add_executable(cookieselection src/main.cpp)

# 2. Archivo demo para el video sin cortes
add_executable(demo_cookieselection demos/demo_cookieselection.cpp)

# 3. Tests locales para validación
enable_testing()
add_executable(test_cookieselection tests/test_cookieselection.cpp)
add_test(NAME test_cookieselection COMMAND test_cookieselection)