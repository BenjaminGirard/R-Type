cmake_minimum_required(VERSION 3.8)
project(DynamicLibraryAPI)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../SolidEngine/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../Common/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../server/include/Component)


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../../DynamicLibrary)

#add_library(TetardMonster SHARED TetardMonster.cpp)
#add_library(MatteusMonster SHARED MatteusMonster.cpp)
#add_library(BibMonster SHARED BibMonster.cpp)
#add_library(StitchMonster SHARED StitchMonster.cpp)
#add_library(SmartieMonster SHARED SmartieMonster.cpp)
#add_library(FlakyxMonster SHARED FlakyxMonster.cpp)
#add_library(TekMonster SHARED TekMonster.cpp)
#add_library(SolidMonster SHARED SolidMonster.cpp)
#add_library(YougoMonster SHARED YougoMonster.cpp)
