cmake_minimum_required(VERSION 3.26)
project(Project-DA-2)

set(CMAKE_CXX_STANDARD 14)
set( CMAKE_BUILD_TYPE_TMP "${CMAKE_BUILD_TYPE}" )
set( CMAKE_BUILD_TYPE "Release" )

set( CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE_TMP} )

add_executable(Projeto-DA
        CustomGraph.h
        CustomGraph.cpp
        main.cpp
        Location.h
        Location.cpp
        Node.h
        Node.cpp
        TSPAlgorithms.h
        TSPAlgorithms.cpp
        Menu.h
        Menu.cpp
)

file(COPY Datasets/ToyGraphs/tourism.csv Datasets/ToyGraphs/stadiums.csv Datasets/ToyGraphs/shipping.csv  DESTINATION ${CMAKE_BINARY_DIR})
file(COPY DataSets/MediumGraphs/nodes.csv Datasets/MediumGraphs/edges_25.csv Datasets/MediumGraphs/edges_50.csv Datasets/MediumGraphs/edges_75.csv Datasets/MediumGraphs/edges_100.csv Datasets/MediumGraphs/edges_200.csv Datasets/MediumGraphs/edges_300.csv Datasets/MediumGraphs/edges_400.csv Datasets/MediumGraphs/edges_500.csv Datasets/MediumGraphs/edges_600.csv Datasets/MediumGraphs/edges_700.csv Datasets/MediumGraphs/edges_800.csv Datasets/MediumGraphs/edges_900.csv DESTINATION ${CMAKE_BINARY_DIR})
file(COPY Datasets/RealWorldGraphs/Graph1 Datasets/RealWorldGraphs/Graph2 Datasets/RealWorldGraphs/Graph3  DESTINATION ${CMAKE_BINARY_DIR})