cmake_minimum_required(VERSION 3.10)
project(C_Math C)

set(CMAKE_C_STANDARD 99)

add_executable(C_Math main.c Series/fibonacci.c Series/fibonacci.h "Root Finders/secant.c" "Root Finders/secant.h"
               "Root Finders/bisection.c" "Root Finders/bisection.h" lib/functions.c lib/functions.h
               "Root Finders/falsePosition.c" "Root Finders/falsePosition.h" "Root Finders/newtonRaphson.c"
               "Root Finders/newtonRaphson.h")

add_executable(fibonacci Series/fibonacci.c Series/fibonacci.h)

add_executable(bisection "Root Finders/bisection.c" "Root Finders/bisection.h" lib/functions.c lib/functions.h
               lib/parser.c lib/parser.h)

add_executable(falsePosition "Root Finders/falsePosition.c" "Root Finders/falsePosition.h" lib/functions.c
               lib/functions.h lib/parser.c lib/parser.h)

add_executable(newtonRaphson "Root Finders/newtonRaphson.c" "Root Finders/newtonRaphson.c" lib/functions.c
               lib/functions.h lib/parser.c lib/parser.h)