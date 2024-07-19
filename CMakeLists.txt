cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME "FlpTool")
project(${PROJECT_NAME} VERSION 1.0)

#--------------------------------------------------------------------------------
# lib
set(FlpSourceFiles
        Source/Flp/Flp.h
        Source/Flp/Flp.cpp
        Source/Flp/EventReader.h
        Source/Flp/EventReader.cpp
        Source/Flp/FlpTypes.h
        Source/Flp/FlpTypes.cpp
        Source/Flp/EventDispatcher.h
        Source/Flp/EventDispatcher.cpp
        Source/Flp/EventHandler.cpp
        Source/Flp/EventHandler.h
)

add_library(Flp STATIC ${FlpSourceFiles})

#--------------------------------------------------------------------------------
# command line tool
set(FlpToolSourceFiles
        Source/FlpTool/FlpToolCommand.h
        Source/FlpTool/FlpToolCommand.cpp
)
add_library(FlpToolLib STATIC ${FlpToolSourceFiles})
target_include_directories(FlpToolLib PUBLIC "Source")

set(SourceFiles
        Source/main.cpp
)
add_executable(${PROJECT_NAME} ${SourceFiles})
target_include_directories(${PROJECT_NAME} PUBLIC "Source")
target_link_libraries(${PROJECT_NAME}
        PUBLIC
        Flp
        FlpToolLib
)

#--------------------------------------------------------------------------------
# tests
enable_testing()

# todo: fix mismatch
# mismatch detected for 'RuntimeLibrary'
# >>> CMakeFiles/FlpTool_Tests.dir/Tests/main.cpp.obj has value MDd_DynamicDebug
# >>> gtest.lib(gtest-all.cc.obj) has value MTd_StaticDebug
#
# this works for msvc:
# target_compile_options(${PROJECT_NAME}_Tests PUBLIC "-MTd")
# this seems to work for both, but seems weird
option(gtest_force_shared_crt
        "Use shared (DLL) run-time lib even when Google Test is built as static lib."
        ON)

add_subdirectory(External/googletest)

set(TestSourceFiles
        Tests/main.cpp
        Tests/FlpTests.h
)

add_executable(${PROJECT_NAME}_Tests ${TestSourceFiles})
target_include_directories(${PROJECT_NAME}_Tests PUBLIC "Source")

target_link_libraries(${PROJECT_NAME}_Tests
        PUBLIC
        gtest
        Flp
        FlpToolLib
)
