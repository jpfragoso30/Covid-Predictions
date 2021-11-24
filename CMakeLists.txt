cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

message(STATUS "Bulding the awesome covid predictor...")

project(COVID_PREDICTIONS C)
include_directories(./libs/)

add_executable(COVID_PREDICTIONS main.c)

target_link_directories(COVID_PREDICTIONS PUBLIC  
    ${CMAKE_CURRENT_LIST_DIR}/src/build/)

target_link_libraries(COVID_PREDICTIONS predictors pf)

target_include_directories(COVID_PREDICTIONS PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/libs/ )