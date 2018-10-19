cmake_minimum_required(VERSION 3.10)
project(C_Math C)

set(CMAKE_C_STANDARD 99)

add_executable(C_Math main.c fibonacci.c fibonacci.h secant.c secant.h bisection.c bisection.h functions.c functions.h)
add_executable(fibonacci fibonacci.c fibonacci.h)
add_executable(bisection bisection.c bisection.h functions.c functions.h tinyexpr.c tinyexpr.h)