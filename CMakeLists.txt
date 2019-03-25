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
        Source/Assets/Util/util.c Source/Assets/Util/util.h)

add_library(parser
        Source/Assets/Util/parser.c Source/Assets/Util/parser.h)

add_library(functions
        Source/Assets/Util/functions.c Source/Assets/Util/functions.h)

add_library(dynamicArrays
        Source/Assets/Util/dynamicArrays1D.c Source/Assets/Util/dynamicArrays1D.c)

add_library(randomGenerator
        Source/Assets/Util/randomGenerator.c Source/Assets/Util/randomGenerator.h)

# link primary libraries

target_link_libraries(functions
        PRIVATE parser util)

# OS specified options
if (UNIX AND NOT APPLE)
    # this linls math library for parser library to avoid "undefined refrence" error on *nix systems
    target_link_libraries(parser
            m)
endif ()

#-----------------------------------------------------------------------------------------------------------------------
#                                              Functions Libraries
#***********************************************************************************************************************
#                                             Function Root Finders

add_library(bisectionAlgorithm
        "Source/Assets/Function Root Finder Algorithms/bisectionAlgorithm.c"
        "Source/Assets/Function Root Finder Algorithms/bisectionAlgorithm.h")

target_link_libraries(bisectionAlgorithm
        PRIVATE functions util)

add_library(newtonRaphsonAlgorithm
        "Source/Assets/Function Root Finder Algorithms/newtonRaphsonAlgorithm.c"
        "Source/Assets/Function Root Finder Algorithms/newtonRaphsonAlgorithm.h")

target_link_libraries(newtonRaphsonAlgorithm
        PRIVATE functions util)

add_library(falsePositionAlgorithm
        "Source/Assets/Function Root Finder Algorithms/falsePositionAlgorithm.c"
        "Source/Assets/Function Root Finder Algorithms/falsePositionAlgorithm.h")

target_link_libraries(falsePositionAlgorithm
        PRIVATE functions util)

add_library(secantAlgorithm
        "Source/Assets/Function Root Finder Algorithms/secantAlgorithm.c"
        "Source/Assets/Function Root Finder Algorithms/secantAlgorithm.h")

target_link_libraries(secantAlgorithm
        PRIVATE functions util)

#***********************************************************************************************************************
#                                            Integration Algorithms

add_library(riemannSumAlgorithm
        "Source/Assets/Integration Algorithms/riemannSumAlgorithm.c"
        "Source/Assets/Integration Algorithms/riemannSumAlgorithm.h")

target_link_libraries(riemannSumAlgorithm
        PRIVATE functions util)

add_library(trapezoidRuleAlgorithm
        "Source/Assets/Integration Algorithms/trapezoidRuleAlgorithm.c"
        "Source/Assets/Integration Algorithms/trapezoidRuleAlgorithm.h")

target_link_libraries(trapezoidRuleAlgorithm
        PRIVATE functions util)

add_library(simpsonRuleAlgorithm
        "Source/Assets/Integration Algorithms/simpsonRuleAlgorithm.c"
        "Source/Assets/Integration Algorithms/simpsonRuleAlgorithm.h")

target_link_libraries(simpsonRuleAlgorithm
        PRIVATE functions util)

add_library(rombergAlgorithm
        "Source/Assets/Integration Algorithms/rombergAlgorithm.c"
        "Source/Assets/Integration Algorithms/rombergAlgorithm.h")

target_link_libraries(rombergAlgorithm
        PRIVATE functions util dynamicArrays trapezoidRuleAlgorithm)

add_library(monteCarloIntegrationAlgorithm
        "Source/Assets/Integration Algorithms/monteCarloIntegrationAlgorithm.c"
        "Source/Assets/Integration Algorithms/monteCarloIntegrationAlgorithm.h")

target_link_libraries(monteCarloIntegrationAlgorithm
        PRIVATE functions util randomGenerator simpleMaxMinFinderAlgorithm)

#***********************************************************************************************************************
#                                          Optimization Algorithms

add_library(gradientDescentAlgorithm
        "Source/Assets/Optimization Algorithms/gradientDescentAlgorithm.c"
        "Source/Assets/Optimization Algorithms/gradientDescentAlgorithm.h")

target_link_libraries(gradientDescentAlgorithm
        PRIVATE functions util randomGenerator)

add_library(simpleMaxMinFinderAlgorithm
        "Source/Assets/Optimization Algorithms/simpleMaxMinFinderAlgorithm.c"
        "Source/Assets/Optimization Algorithms/simpleMaxMinFinderAlgorithm.h")

target_link_libraries(simpleMaxMinFinderAlgorithm
        PRIVATE functions util)

#=======================================================================================================================
#                                                  Executables
#-----------------------------------------------------------------------------------------------------------------------
#                                             Function Root Finders

add_executable(bisection
        "Source/Function Root Finder Algorithms/bisection.c"
        Source/Assets/Util/_configurations.h)

target_link_libraries(bisection
        PRIVATE bisectionAlgorithm util)

add_executable(newtonRaphson
        "Source/Function Root Finder Algorithms/newtonRaphson.c"
        Source/Assets/Util/_configurations.h)

target_link_libraries(newtonRaphson
        PRIVATE newtonRaphsonAlgorithm util)

add_executable(falsePosition
        "Source/Function Root Finder Algorithms/falsePosition.c"
        Source/Assets/Util/_configurations.h)

target_link_libraries(falsePosition
        PRIVATE falsePositionAlgorithm util)

add_executable(secant
        "Source/Function Root Finder Algorithms/secant.c"
        Source/Assets/Util/_configurations.h)

target_link_libraries(secant
        PRIVATE secantAlgorithm util)

#-----------------------------------------------------------------------------------------------------------------------
#                                            Integration Algorithms

add_executable(riemannSum
        "Source/Integration Algoritms/riemannSum.c"
        Source/Assets/Util/_configurations.h)

target_link_libraries(riemannSum
        PRIVATE riemannSumAlgorithm util)

add_executable(trapezoidRule
        "Source/Integration Algoritms/trapezoidRule.c"
        Source/Assets/Util/_configurations.h)

target_link_libraries(trapezoidRule
        PRIVATE trapezoidRuleAlgorithm util)

add_executable(simpsonRule
        "Source/Integration Algoritms/simpsonRule.c"
        Source/Assets/Util/_configurations.h)

target_link_libraries(simpsonRule
        PRIVATE simpsonRuleAlgorithm util)

add_executable(romberg
        "Source/Integration Algoritms/romberg.c"
        Source/Assets/Util/_configurations.h)

target_link_libraries(romberg
        PRIVATE rombergAlgorithm trapezoidRuleAlgorithm util)

add_executable(monteCarlo
        "Source/Integration Algoritms/monteCarlo.c"
        Source/Assets/Util/_configurations.h)

target_link_libraries(monteCarlo
        PRIVATE monteCarloIntegrationAlgorithm util)

#-----------------------------------------------------------------------------------------------------------------------
#                                          Optimization Algorithms

add_executable(gradientDescent
        "Source/Optimization Algorithms/gradientDescent.c"
        Source/Assets/Util/_configurations.h)

target_link_libraries(gradientDescent
        PRIVATE gradientDescentAlgorithm util)

add_executable(maxMinFinder
        "Source/Optimization Algorithms/simpleMaxMinFinder.c"
        Source/Assets/Util/_configurations.h)

target_link_libraries(maxMinFinder
        PRIVATE simpleMaxMinFinderAlgorithm util)

#-----------------------------------------------------------------------------------------------------------------------
#                                                 Series

# add_executable(fibonacci)
