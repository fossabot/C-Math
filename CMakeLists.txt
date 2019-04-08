cmake_minimum_required(VERSION 3.10)
project(C_Math LANGUAGES C)

set(CMAKE_C_STANDARD 99)

# shared library option [be aware that using shared library needs some changes
# to PUBLIC PRIVATE parts of linking, and you have to do it at your own.]
set(BUILD_SHARED_LIBS NO)

#^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Settings ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

# please set this variables manually if you want to build files on your system,
# simply remove the '#' before the 'set' and change the 'x' values

# building options: Release, Debug, RelWithDebInfo, MinRelSize
# set(CMAKE_BUILD_TYPE Release)

# set(CMAKE_MAKE_PROGRAM x)
# set(CMAKE_C_COMPILER x)
# set(CMAKE_CXX_COMPILER x)

#=======================================================================================================================
#                                                  Libraries
#-----------------------------------------------------------------------------------------------------------------------
#                                               Primary libraries

add_library(util
        Source/Library/Util/util.c Source/Library/Util/util.h)

add_library(parser
        Source/Library/Util/parser.c Source/Library/Util/parser.h)

add_library(functions
        Source/Library/Util/functions.c Source/Library/Util/functions.h)

add_library(dynamicArrays
        Source/Library/Util/dynamicArrays1D.c Source/Library/Util/dynamicArrays1D.c)

add_library(randomGenerator
        Source/Library/Util/randomGenerator.c Source/Library/Util/randomGenerator.h)

# link primary libraries

target_link_libraries(functions
        PRIVATE parser util)

#-----------------------------------------------------------------------------------------------------------------------
#                                              Functions Libraries
#***********************************************************************************************************************
#                                           Differentiation Algorithms

add_library(derivNumericalAlgorithm
        "Source/Library/Differentiation Algorithms/derivNumericalAlgorithm.c"
        "Source/Library/Differentiation Algorithms/derivNumericalAlgorithm.c")

target_link_libraries(derivNumericalAlgorithm
        PRIVATE functions util)

#***********************************************************************************************************************
#                                             Function Root Finders

add_library(bisectionAlgorithm
        "Source/Library/Function Root Finder Algorithms/bisectionAlgorithm.c"
        "Source/Library/Function Root Finder Algorithms/bisectionAlgorithm.h")

target_link_libraries(bisectionAlgorithm
        PRIVATE functions util)

add_library(brentAlgorithm
        "Source/Library/Function Root Finder Algorithms/brentAlgorithm.c"
        "Source/Library/Function Root Finder Algorithms/brentAlgorithm.h")

target_link_libraries(brentAlgorithm
        PRIVATE functions util)

add_library(cubicAlgorithm
        "Source/Library/Function Root Finder Algorithms/cubicAlgorithm.c"
        "Source/Library/Function Root Finder Algorithms/cubicAlgorithm.h")

target_link_libraries(cubicAlgorithm
        PRIVATE quadraticAlgorithm util)

add_library(newtonRaphsonAlgorithm
        "Source/Library/Function Root Finder Algorithms/newtonRaphsonAlgorithm.c"
        "Source/Library/Function Root Finder Algorithms/newtonRaphsonAlgorithm.h")

target_link_libraries(newtonRaphsonAlgorithm
        PRIVATE functions derivNumericalAlgorithm util)

add_library(falsePositionAlgorithm
        "Source/Library/Function Root Finder Algorithms/falsePositionAlgorithm.c"
        "Source/Library/Function Root Finder Algorithms/falsePositionAlgorithm.h")

target_link_libraries(falsePositionAlgorithm
        PRIVATE functions util)

add_library(quadraticAlgorithm
        "Source/Library/Function Root Finder Algorithms/quadraticAlgorithm.c"
        "Source/Library/Function Root Finder Algorithms/quadraticAlgorithm.h")

target_link_libraries(quadraticAlgorithm
        PRIVATE util)

add_library(secantAlgorithm
        "Source/Library/Function Root Finder Algorithms/secantAlgorithm.c"
        "Source/Library/Function Root Finder Algorithms/secantAlgorithm.h")

target_link_libraries(secantAlgorithm
        PRIVATE functions util)

add_library(steffensenAlgorithm
        "Source/Library/Function Root Finder Algorithms/steffensenAlgorithm.c"
        "Source/Library/Function Root Finder Algorithms/steffensenAlgorithm.h")

target_link_libraries(steffensenAlgorithm
        PRIVATE functions util)

#***********************************************************************************************************************
#                                            Integration Algorithms

add_library(riemannSumAlgorithm
        "Source/Library/Integration Algorithms/riemannSumAlgorithm.c"
        "Source/Library/Integration Algorithms/riemannSumAlgorithm.h")

target_link_libraries(riemannSumAlgorithm
        PRIVATE functions util)

add_library(trapezoidRuleAlgorithm
        "Source/Library/Integration Algorithms/trapezoidRuleAlgorithm.c"
        "Source/Library/Integration Algorithms/trapezoidRuleAlgorithm.h")

target_link_libraries(trapezoidRuleAlgorithm
        PRIVATE functions util)

add_library(simpsonRuleAlgorithm
        "Source/Library/Integration Algorithms/simpsonRuleAlgorithm.c"
        "Source/Library/Integration Algorithms/simpsonRuleAlgorithm.h")

target_link_libraries(simpsonRuleAlgorithm
        PRIVATE functions util)

add_library(rombergAlgorithm
        "Source/Library/Integration Algorithms/rombergAlgorithm.c"
        "Source/Library/Integration Algorithms/rombergAlgorithm.h")

target_link_libraries(rombergAlgorithm
        PRIVATE functions util dynamicArrays trapezoidRuleAlgorithm)

add_library(monteCarloIntegrationAlgorithm
        "Source/Library/Integration Algorithms/monteCarloIntegrationAlgorithm.c"
        "Source/Library/Integration Algorithms/monteCarloIntegrationAlgorithm.h")

target_link_libraries(monteCarloIntegrationAlgorithm
        PRIVATE functions util randomGenerator simpleMaxMinFinderAlgorithm)

#***********************************************************************************************************************
#                                          Optimization Algorithms

add_library(goldenSectionOptAlgorithm
        "Source/Library/Optimization Algorithms/goldenSectionOptAlgorithm.c"
        "Source/Library/Optimization Algorithms/goldenSectionOptAlgorithm.h")

target_link_libraries(goldenSectionOptAlgorithm
        PRIVATE functions util)

add_library(gradientDescentAlgorithm
        "Source/Library/Optimization Algorithms/gradientDescentAlgorithm.c"
        "Source/Library/Optimization Algorithms/gradientDescentAlgorithm.h")

target_link_libraries(gradientDescentAlgorithm
        PRIVATE functions randomGenerator util)

add_library(newtonRaphsonOptAlgorithm
        "Source/Library/Optimization Algorithms/newtonRaphsonOptAlgorithm.c"
        "Source/Library/Optimization Algorithms/newtonRaphsonOptAlgorithm.h")

target_link_libraries(newtonRaphsonOptAlgorithm
        PRIVATE functions derivNumericalAlgorithm util)

add_library(simpleMaxMinFinderAlgorithm
        "Source/Library/Optimization Algorithms/simpleMaxMinFinderAlgorithm.c"
        "Source/Library/Optimization Algorithms/simpleMaxMinFinderAlgorithm.h")

target_link_libraries(simpleMaxMinFinderAlgorithm
        PRIVATE functions util)

#-----------------------------------------------------------------------------------------------------------------------
#                                             Series Algorithms

add_library(fibonacciAlgorithm
        "Source/Library/Series Algorithms/fibonacciAlgorithm.c"
        "Source/Library/Series Algorithms/fibonacciAlgorithm.h")

#=======================================================================================================================
#                                                  Executables
#-----------------------------------------------------------------------------------------------------------------------
#                                             Function Root Finders

add_executable(bisection
        "Source/CLI Apps/Function Root Finder Algorithms/bisection.c")

target_link_libraries(bisection
        PRIVATE bisectionAlgorithm util)

add_executable(brent
        "Source/CLI Apps/Function Root Finder Algorithms/brent.c")

target_link_libraries(brent
        PRIVATE brentAlgorithm util)

add_executable(cubic
        "Source/CLI Apps/Function Root Finder Algorithms/cubic.c")

target_link_libraries(cubic
        PRIVATE cubicAlgorithm util)

add_executable(newtonRaphson
        "Source/CLI Apps/Function Root Finder Algorithms/newtonRaphson.c")

target_link_libraries(newtonRaphson
        PRIVATE newtonRaphsonAlgorithm util)

add_executable(falsePosition
        "Source/CLI Apps/Function Root Finder Algorithms/falsePosition.c")

target_link_libraries(falsePosition
        PRIVATE falsePositionAlgorithm util)

add_executable(quadratic
        "Source/CLI Apps/Function Root Finder Algorithms/quadratic.c")

target_link_libraries(quadratic
        PRIVATE quadraticAlgorithm util)

add_executable(secant
        "Source/CLI Apps/Function Root Finder Algorithms/secant.c")

target_link_libraries(secant
        PRIVATE secantAlgorithm util)

add_executable(steffensen
        "Source/CLI Apps/Function Root Finder Algorithms/steffensen.c")

target_link_libraries(steffensen
        PRIVATE steffensenAlgorithm util)

#-----------------------------------------------------------------------------------------------------------------------
#                                            Integration Algorithms

add_executable(riemannSum
        "Source/CLI Apps/Integration Algoritms/riemannSum.c")

target_link_libraries(riemannSum
        PRIVATE riemannSumAlgorithm util)

add_executable(trapezoidRule
        "Source/CLI Apps/Integration Algoritms/trapezoidRule.c")

target_link_libraries(trapezoidRule
        PRIVATE trapezoidRuleAlgorithm util)

add_executable(simpsonRule
        "Source/CLI Apps/Integration Algoritms/simpsonRule.c")

target_link_libraries(simpsonRule
        PRIVATE simpsonRuleAlgorithm util)

add_executable(romberg
        "Source/CLI Apps/Integration Algoritms/romberg.c")

target_link_libraries(romberg
        PRIVATE rombergAlgorithm trapezoidRuleAlgorithm util)

add_executable(monteCarlo
        "Source/CLI Apps/Integration Algoritms/monteCarlo.c")

target_link_libraries(monteCarlo
        PRIVATE monteCarloIntegrationAlgorithm util)

#-----------------------------------------------------------------------------------------------------------------------
#                                          Optimization Algorithms

add_executable(goldenSectionOpt
        "Source/CLI Apps/Optimization Algorithms/goldenSectionOpt.c")

target_link_libraries(goldenSectionOpt
        PRIVATE goldenSectionOptAlgorithm util)

add_executable(gradientDescent
        "Source/CLI Apps/Optimization Algorithms/gradientDescent.c")

target_link_libraries(gradientDescent
        PRIVATE gradientDescentAlgorithm derivNumericalAlgorithm util)

add_executable(newtonRaphsonOpt
        "Source/CLI Apps/Optimization Algorithms/newtonRaphsonOpt.c")

target_link_libraries(newtonRaphsonOpt
        PRIVATE newtonRaphsonOptAlgorithm util)

add_executable(maxMinFinder
        "Source/CLI Apps/Optimization Algorithms/simpleMaxMinFinder.c")

target_link_libraries(maxMinFinder
        PRIVATE simpleMaxMinFinderAlgorithm util)

#-----------------------------------------------------------------------------------------------------------------------
#                                                 Series

#-----------------------------------------------------------------------------------------------------------------------
#                                           OS specific options

if (UNIX AND NOT APPLE)
    # this linls math library for parser library to avoid "undefined refrence" error on *nix systems
    target_link_libraries(parser
            PRIVATE m)

    target_link_libraries(quadraticAlgorithm
            PRIVATE m)

endif ()