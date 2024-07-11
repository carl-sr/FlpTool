cmake_minimum_required(VERSION 3.2)

set(PROJECT_NAME "FlpTool")

project(${PROJECT_NAME} VERSION 1.0)
#set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)



# ---------------------------------------------------------------------------------
# add kaitai struct
# ---------------------------------------------------------------------------------

set(BUILD_TESTS OFF CACHE BOOL "no test >:(")
add_subdirectory(KaitaiStructRuntime)

#target_include_directories(kaitai_struct_cpp_stl_runtime PUBLIC "C:/Program Files (x86)/GnuWin32/include/")
#target_link_libraries(kaitai_struct_cpp_stl_runtime PUBLIC "C:/Program Files (x86)/GnuWin32/lib/libiconv.a")


# ---------------------------------------------------------------------------------
# create main program
# ---------------------------------------------------------------------------------

set(SourceFiles
        Source/main.cpp
)

add_executable(${PROJECT_NAME} ${SourceFiles})
#target_include_directories(${PROJECT_NAME} PUBLIC "C:/Program Files (x86)/GnuWin32/include/")


# ---------------------------------------------------------------------------------
# set up parser
# ---------------------------------------------------------------------------------

set(KsyFiles
        ${PROJECT_SOURCE_DIR}/Ksy/flp.ksy
        ${PROJECT_SOURCE_DIR}/Ksy/flp_byte_event.ksy
        ${PROJECT_SOURCE_DIR}/Ksy/flp_word_event.ksy
        ${PROJECT_SOURCE_DIR}/Ksy/flp_dword_event.ksy
        ${PROJECT_SOURCE_DIR}/Ksy/flp_text_event.ksy
)

set(KsySourceFiles
        ${PROJECT_SOURCE_DIR}/Ksy/Build/flp.cpp
        ${PROJECT_SOURCE_DIR}/Ksy/Build/flp_byte_event.cpp
        ${PROJECT_SOURCE_DIR}/Ksy/Build/flp_word_event.cpp
        ${PROJECT_SOURCE_DIR}/Ksy/Build/flp_dword_event.cpp
        ${PROJECT_SOURCE_DIR}/Ksy/Build/flp_text_event.cpp
)

add_custom_command(
        OUTPUT ${KsySourceFiles}
        PRE_BUILD
        COMMAND echo "Generating Kaitai parser code" && ksc -t cpp_stl -d ${PROJECT_SOURCE_DIR}/Ksy/Build/ --cpp-standard 11 ${PROJECT_SOURCE_DIR}/Ksy/flp.ksy
        VERBATIM
        DEPENDS "${KsyFiles}"
)

add_library(flp_ksy STATIC ${KsySourceFiles})
#target_include_directories(flp_ksy PUBLIC "C:/Program Files (x86)/GnuWin32/include/")

target_include_directories(flp_ksy PUBLIC ${PROJECT_SOURCE_DIR}/KaitaiStructRuntime)
target_include_directories(flp_ksy PUBLIC ${PROJECT_SOURCE_DIR}/Ksy/Build)


# ---------------------------------------------------------------------------------
# link
# ---------------------------------------------------------------------------------

target_link_libraries(${PROJECT_NAME}
        flp_ksy
        kaitai_struct_cpp_stl_runtime
)
