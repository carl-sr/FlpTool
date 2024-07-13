cmake_minimum_required(VERSION 3.2)

set(PROJECT_NAME "FlpTool")

project(${PROJECT_NAME} VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)

#--------------------------------------------------------------------------------
# lib
set(FlpSourceFiles
        Source/Flp/Flp.h
        Source/Flp/Flp.cpp
        Source/Flp/FlpEventReader.h
        Source/Flp/FlpEventReader.cpp
        Source/Flp/FlpTypes.h
        Source/Flp/FlpTypes.cpp
        Source/Flp/FlpEventDispatcher.h
        Source/Flp/FlpEventDispatcher.cpp
)

add_library(Flp STATIC ${FlpSourceFiles})
target_compile_options(Flp PUBLIC "-MTd")

#--------------------------------------------------------------------------------
# command line tool
set(SourceFiles
        Source/main.cpp
)

#--------------------------------------------------------------------------------
# tests
enable_testing()
add_subdirectory(External/googletest)

set(TestSourceFiles
        Tests/main.cpp
        Tests/FlpTests.h
)

add_executable(${PROJECT_NAME}_Tests ${TestSourceFiles})
set_property(TARGET ${PROJECT_NAME}_Tests PROPERTY CXX_STANDARD 20)
target_include_directories(${PROJECT_NAME}_Tests PUBLIC "Source")

target_link_libraries(${PROJECT_NAME}_Tests
        PUBLIC
        gtest
        Flp
)

# todo: fix mismatch
# mismatch detected for 'RuntimeLibrary'
# >>> CMakeFiles/FlpTool_Tests.dir/Tests/main.cpp.obj has value MDd_DynamicDebug
# >>> gtest.lib(gtest-all.cc.obj) has value MTd_StaticDebug
#
# this works for msvc:
target_compile_options(${PROJECT_NAME}_Tests PUBLIC "-MTd")
