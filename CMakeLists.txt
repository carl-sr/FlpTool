cmake_minimum_required(VERSION 3.2)

set(PROJECT_NAME "FlpTool")

project(${PROJECT_NAME} VERSION 1.0)

set(SourceFiles
        Source/main.cpp
        Source/Flp.h
        Source/Flp.cpp
        Source/FlpEventReader.h
        Source/FlpEventReader.cpp
        Source/FlpTypes.h
        Source/FlpTypes.cpp
)

add_executable(${PROJECT_NAME} ${SourceFiles})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
