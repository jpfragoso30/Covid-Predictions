cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(COVID_PREDICTIONS C)

set(SRC ../src)
set(LIBS ../libs)

include_directories(${LIBS})

AUX_SOURCE_DIRECTORY(${SRC}/ TARGETS_SRC) 
AUX_SOURCE_DIRECTORY(${LIBS}/ TARGETS_LIBS)


add_library(predictors STATIC ${TARGETS_SRC})

add_library(pf STATIC PF.c ${TARGETS_LIBS})

target_link_directories(predictors PUBLIC ${CMAKE_CURRENT_LIST_DIR}/${LIBS}/)

target_link_directories(pf PUBLIC ${CMAKE_CURRENT_LIST_DIR}/${LIBS}/)

target_include_directories(predictors PUBLIC ${CMAKE_CURRENT_LIST_DIR}/${LIBS}/)
