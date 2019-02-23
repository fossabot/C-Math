cmake_minimum_required(VERSION 3.10)
project(C_Math LANGUAGES C)

set(CMAKE_C_STANDARD 99)

#=======================================================================================================================
#                                                  Libraries
#-----------------------------------------------------------------------------------------------------------------------
#                                               Primary libraries

add_library(util STATIC
        Source/Assets/Util/util.c Source/Assets/Util/util.h)

add_library(parser STATIC
        Source/Assets/Util/parser.c Source/Assets/Util/parser.h)

add_library(functions STATIC
        Source/Assets/Util/functions.c Source/Assets/Util/functions.h)

# link primary libraries
target_link_libraries(functions
        PRIVATE parser util)

#-----------------------------------------------------------------------------------------------------------------------
#                                              Function Libraries

add_library(bisectionAlgorithm STATIC
        "Source/Assets/Function Root Finder Algorithms/bisectionAlgorithm.c"
        "Source/Assets/Function Root Finder Algorithms/bisectionAlgorithm.h")

target_link_libraries(bisectionAlgorithm
        PRIVATE functions util)

#=======================================================================================================================
#                                                  Executables
#-----------------------------------------------------------------------------------------------------------------------
#                                             Function Root Finders

add_executable(bisection
        "Source/Function Root Finder Algorithms/bisection.c"
        Source/Assets/Util/_configurations.h)

target_link_libraries(bisection
        PRIVATE util bisectionAlgorithm)

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

#-----------------------------------------------------------------------------------------------------------------------
#                                            Integration Algorithms

add_executable(riemannSum
        "Source/Integration Algoritms/riemannSum.c"
        "Source/Assets/Integration Algorithms/riemannSumAlgorithm.c"
        "Source/Assets/Integration Algorithms/riemannSumAlgorithm.h"
        Source/Assets/Util/functions.c Source/Assets/Util/functions.h Source/Assets/Util/parser.c
        Source/Assets/Util/parser.h Source/Assets/Util/util.c Source/Assets/Util/util.h
        Source/Assets/Util/_configurations.h)

add_executable(trapezoidRule
        "Source/Integration Algoritms/trapezoidRule.c"
        "Source/Assets/Integration Algorithms/trapezoidRuleAlgorithm.c"
        "Source/Assets/Integration Algorithms/trapezoidRuleAlgorithm.h"
        Source/Assets/Util/functions.c Source/Assets/Util/functions.h Source/Assets/Util/parser.c
        Source/Assets/Util/parser.h Source/Assets/Util/util.c Source/Assets/Util/util.h
        Source/Assets/Util/_configurations.h)


add_executable(simpsonRule
        "Source/Integration Algoritms/simpsonRule.c"
        "Source/Assets/Integration Algorithms/simpsonRuleAlgorithm.c"
        "Source/Assets/Integration Algorithms/simpsonRuleAlgorithm.h"
        Source/Assets/Util/functions.c Source/Assets/Util/functions.h Source/Assets/Util/parser.c
        Source/Assets/Util/parser.h Source/Assets/Util/util.c Source/Assets/Util/util.h
        Source/Assets/Util/_configurations.h)

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

#-----------------------------------------------------------------------------------------------------------------------
#                                          Optimization Algorithms

add_executable(gradientDescent
        "Source/Optimization Algorithms/gradientDescent.c"
        "Source/Assets/Optimization Algorithms/gradientDescentAlgorithm.c"
        "Source/Assets/Optimization Algorithms/gradientDescentAlgorithm.h"
        Source/Assets/Util/randomGenerator.c Source/Assets/Util/randomGenerator.h
        Source/Assets/Util/functions.c Source/Assets/Util/functions.h Source/Assets/Util/parser.c
        Source/Assets/Util/parser.h Source/Assets/Util/util.c Source/Assets/Util/util.h
        Source/Assets/Util/_configurations.h)

add_executable(gradientAscent
        "Source/Optimization Algorithms/gradientAscent.c"
        "Source/Assets/Optimization Algorithms/gradientAscentAlgorithm.c"
        "Source/Assets/Optimization Algorithms/gradientAscentAlgorithm.h"
        Source/Assets/Util/randomGenerator.c Source/Assets/Util/randomGenerator.h
        Source/Assets/Util/functions.c Source/Assets/Util/functions.h Source/Assets/Util/parser.c
        Source/Assets/Util/parser.h Source/Assets/Util/util.c Source/Assets/Util/util.h
        Source/Assets/Util/_configurations.h)

add_executable(simpleMaxMinFinder
        "Source/Optimization Algorithms/simpleMaxMinFinder.c"
        "Source/Assets/Optimization Algorithms/simpleMaxMinFinderAlgorithm.c"
        "Source/Assets/Optimization Algorithms/simpleMaxMinFinderAlgorithm.h"
        Source/Assets/Util/functions.c Source/Assets/Util/functions.h Source/Assets/Util/parser.c
        Source/Assets/Util/parser.h Source/Assets/Util/util.c Source/Assets/Util/util.h
        Source/Assets/Util/_configurations.h)

#-----------------------------------------------------------------------------------------------------------------------
#                                                 Series

# add_executable(fibonacci)
