cmake_minimum_required(VERSION 3.10)
project(C_Math C)

set(CMAKE_C_STANDARD 99)

#=======================================================================================================================
#                                                  Function Root Finders

add_executable(bisection
        "Source/Function Root Finder Algorithms/bisection.c"
        "Source/Assets/Function Root Finder Algorithms/bisectionAlgorithm.c"
        "Source/Assets/Function Root Finder Algorithms/bisectionAlgorithm.h"
        Source/Assets/Util/functions.c Source/Assets/Util/functions.h Source/Assets/Util/parser.c
        Source/Assets/Util/parser.h Source/Assets/Util/util.c Source/Assets/Util/util.h
        Source/Assets/Util/_configurations.h)

add_executable(newtonRaphson
        "Source/Function Root Finder Algorithms/newtonRaphson.c"
        "Source/Assets/Function Root Finder Algorithms/newtonRaphsonAlgorithm.c"
        "Source/Assets/Function Root Finder Algorithms/newtonRaphsonAlgorithm.h"
        Source/Assets/Util/functions.c Source/Assets/Util/functions.h Source/Assets/Util/parser.c
        Source/Assets/Util/parser.h Source/Assets/Util/util.c Source/Assets/Util/util.h
        Source/Assets/Util/_configurations.h)

add_executable(falsePosition
        "Source/Function Root Finder Algorithms/falsePosition.c"
        "Source/Assets/Function Root Finder Algorithms/falsePositionAlgorithm.c"
        "Source/Assets/Function Root Finder Algorithms/falsePositionAlgorithm.h"
        Source/Assets/Util/functions.c Source/Assets/Util/functions.h Source/Assets/Util/parser.c
        Source/Assets/Util/parser.h Source/Assets/Util/util.c Source/Assets/Util/util.h
        Source/Assets/Util/_configurations.h)

add_executable(secant
        "Source/Function Root Finder Algorithms/secant.c"
        "Source/Assets/Function Root Finder Algorithms/secantAlgorithm.c"
        "Source/Assets/Function Root Finder Algorithms/secantAlgorithm.h"
        Source/Assets/Util/functions.c Source/Assets/Util/functions.h Source/Assets/Util/parser.c
        Source/Assets/Util/parser.h Source/Assets/Util/util.c Source/Assets/Util/util.h
        Source/Assets/Util/_configurations.h)

#=======================================================================================================================
#                                               Integration Algorithms

add_executable(riemannSum
        "Source/Integration Algoritms/riemannSum.c"
        "Source/Assets/Integration Algorithms/riemannSumAlgorithm.c"
        "Source/Assets/Integration Algorithms/riemannSumAlgorithm.h"
        Source/Assets/Util/functions.c Source/Assets/Util/functions.h Source/Assets/Util/parser.c
        Source/Assets/Util/parser.h Source/Assets/Util/util.c Source/Assets/Util/util.h
        Source/Assets/Util/_configurations.h)

add_executable(trapezoidRule
        "Source/Integration Algoritms/trapezoidRule.c" "Source/Assets/Integration Algorithms/trapezoidRuleAlgorithm.c" "Source/Assets/Integration Algorithms/trapezoidRuleAlgorithm.h")

#add_executable(simpsonRule
        #"Source/Integration Algoritms/simpsonRule.c")

add_executable(monteCarlo
        "Source/Integration Algoritms/monteCarlo.c"
        "Source/Assets/Integration Algorithms/monteCarloIntegrationAlgorithm.c"
        "Source/Assets/Integration Algorithms/monteCarloIntegrationAlgorithm.h"
        "Source/Assets/Optimization Algorithms/simpleMaxMinFinderAlgorithm.c"
        "Source/Assets/Optimization Algorithms/simpleMaxMinFinderAlgorithm.h"
        Source/Assets/Util/randomGenerator.c Source/Assets/Util/randomGenerator.h
        Source/Assets/Util/functions.c Source/Assets/Util/functions.h Source/Assets/Util/parser.c
        Source/Assets/Util/parser.h Source/Assets/Util/util.c Source/Assets/Util/util.h
        Source/Assets/Util/_configurations.h)

#add_executable(romberg
        #"Source/Integration Algoritms/romberg.c")

#=======================================================================================================================
#                                              Optimization Algorithms

add_executable(gradientDescent
        "Source/Optimization Algorithms/gradientDescent.c"
        "Source/Assets/Optimization Algorithms/gradientDescentAlgorithm.c"
        "Source/Assets/Optimization Algorithms/gradientDescentAlgorithm.h"
        Source/Assets/Util/functions.c Source/Assets/Util/functions.h Source/Assets/Util/parser.c
        Source/Assets/Util/parser.h Source/Assets/Util/util.c Source/Assets/Util/util.h
        Source/Assets/Util/_configurations.h)

#add_executable(simpleMaxMinFinder
        #"Source/Assets/Optimization Algorithms/simpleMaxMinFinderAlgorithm.c"
        #"Source/Assets/Optimization Algorithms/simpleMaxMinFinderAlgorithm.h"
       # Source/Assets/Util/functions.c Source/Assets/Util/functions.h Source/Assets/Util/parser.c
       # Source/Assets/Util/parser.h Source/Assets/Util/util.c Source/Assets/Util/util.h
       # Source/Assets/Util/_configurations.h)

#=======================================================================================================================
#                                                       Series

# add_executable(fibonacci)
