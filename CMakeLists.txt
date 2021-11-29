cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
message(STATUS "Bulding the awesome covid predictor...")

project(COVID_PREDICTIONS C)

set(SRC /src/)
set(LIBS /libs/)

include_directories(.${LIBS})

add_executable(COVID_PREDICTIONS main.c)

target_link_directories(COVID_PREDICTIONS PUBLIC  
    ${CMAKE_CURRENT_LIST_DIR}${SRC}build/)

target_link_libraries(COVID_PREDICTIONS predictors pf)

target_include_directories(COVID_PREDICTIONS PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}${LIBS})