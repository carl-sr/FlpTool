cmake_minimum_required(VERSION 3.2)

set(PROJECT_NAME "FlpTool")

project(${PROJECT_NAME} VERSION 1.0)

#--------------------------------------------------------------------------------
# command line tool
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

#--------------------------------------------------------------------------------
# tests
enable_testing()

set(TestSourceFiles
        Tests/main.cpp
)

add_subdirectory(External/googletest)
add_executable(${PROJECT_NAME}_Tests ${TestSourceFiles})
set_property(TARGET ${PROJECT_NAME}_Tests PROPERTY CXX_STANDARD 20)

target_compile_definitions(${PROJECT_NAME}_Tests INTERFACE $<TARGET_PROPERTY:${PROJECT_NAME},INTERFACE_COMPILE_DEFINITIONS>)
target_include_directories(${PROJECT_NAME}_Tests INTERFACE $<TARGET_PROPERTY:${PROJECT_NAME},INCLUDE_DIRECTORIES>)

target_link_libraries(${PROJECT_NAME}_Tests
        PRIVATE
        gtest
)
