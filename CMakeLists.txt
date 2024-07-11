cmake_minimum_required(VERSION 3.2)

set(PROJECT_NAME "FlpTool")

project(${PROJECT_NAME} VERSION 1.0)
#set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

set(SourceFiles
        Source/main.cpp
)

add_executable(${PROJECT_NAME} ${SourceFiles})

