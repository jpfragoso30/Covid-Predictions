cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

include_directories(../libs/)

add_library(predictors 
        STATIC  PF.c Config.c CsvProcessing.c
        Euler.c FilesAndDirs.c fort.c ini.c
        Memory.c Menu.c Ploter.c)

add_library(pf STATIC PF.c ../libs/PF.h ../libs/Config.h ../libs/CsvProcessing.h
        ../libs/Errors.h ../libs/Euler.h ../libs/FilesAndDirs.h
        ../libs/fort.h ../libs/ini.h ../libs/Memory.h ../libs/Menu.h
        ../libs/Ploter.h)

target_link_directories(predictors PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR}/../libs/)

target_link_directories(pf PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR}/../libs/)

target_include_directories(predictors 
        PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR}/../libs/)
