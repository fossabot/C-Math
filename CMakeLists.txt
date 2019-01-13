cmake_minimum_required(VERSION 3.10)
project(C_Math C)

set(CMAKE_C_STANDARD 99)

add_executable(fibonacci Series/fibonacci.c Series/fibonacci.h Lib/_configurations.h)

add_executable(bisection "Root Finders/bisection.c" "Root Finders/bisection.h" Lib/functions.c Lib/functions.h
        Lib/parser.c Lib/parser.h Lib/_configurations.h)

add_executable(falsePosition "Root Finders/falsePosition.c" "Root Finders/falsePosition.h" Lib/functions.c
        Lib/functions.h Lib/parser.c Lib/parser.h Lib/_configurations.h)

add_executable(newtonRaphson "Root Finders/newtonRaphson.c" "Root Finders/newtonRaphson.h" Lib/functions.c
        Lib/functions.h Lib/parser.c Lib/parser.h Lib/_configurations.h)

add_executable(secant "Root Finders/secant.c" "Root Finders/secant.h" Lib/functions.c
        Lib/functions.h Lib/parser.c Lib/parser.h Lib/_configurations.h)

add_executable(fixedPoint "Root Finders/fixedPoint.c" "Root Finders/fixedPoint.h" Lib/functions.c
        Lib/functions.h Lib/parser.c Lib/parser.h Lib/_configurations.h)

add_executable(gradientDescent "Optimization Algorithms/gradientDescent.c" "Optimization Algorithms/gradientDescent.h"
        Lib/functions.c Lib/functions.h Lib/parser.c Lib/parser.h Lib/_configurations.h)