cmake_minimum_required(VERSION 3.26)
project(da2324_p03_student)

set(CMAKE_CXX_STANDARD 14)
set( CMAKE_BUILD_TYPE_TMP "${CMAKE_BUILD_TYPE}" )
set( CMAKE_BUILD_TYPE "Release" )

set( CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE_TMP} )

add_executable(Projeto-DA
        Graph.h
        main.cpp
        Location.h
        Location.cpp
        Node.h
        Node.cpp
        TSPAlgorithms.h
        TSPAlgorithms.cpp
)