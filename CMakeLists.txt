cmake_minimum_required(VERSION 3.7)
project(stm32f103 C CXX ASM)

# Include an error in case the user forgets to specify ARM as a toolchain
if (NOT CMAKE_TOOLCHAIN_FILE)
    message(FATAL_ERROR "Cross compiling only. Please use -DCMAKE_TOOLCHAIN_FILE=cmake/arm-toolchain.cmake or use your own toolchain file")
endif ()

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

add_definitions(-DTEST_CONFIG)

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Os")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Os")

file(GLOB_RECURSE SOURCE_FILES "src/*.c" "src/*.cpp")
file(GLOB_RECURSE INC_FILES "inc/*.h" "inc/*.tpp")

include_directories(
        inc/config
        inc/core
        inc/lib
        inc/user
)

include("cmake/spl.cmake")
include("cmake/stm32f103vct6.cmake")
include("cmake/compile_flags.cmake")

set(ELF_OUT "${PROJECT_NAME}_${CMAKE_BUILD_TYPE}.elf")
set(BIN_OUT "${PROJECT_NAME}_${CMAKE_BUILD_TYPE}.bin")

add_executable(${ELF_OUT} ${SOURCE_FILES} ${INC_FILES})
target_link_libraries(${ELF_OUT} SPL_LIB)
set_target_properties(${ELF_OUT} PROPERTIES LINK_FLAGS ${LINKER_FLAGS})
add_custom_target(
        ${BIN_OUT} ALL
        COMMAND ${ARM_OBJCOPY} -Obinary ${ELF_OUT} ${BIN_OUT}
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        DEPENDS ${ELF_OUT}
)

add_custom_command(
        TARGET ${ELF_OUT}
        POST_BUILD
        COMMAND ${ARM_SIZE} ${ELF_OUT}
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

# ------------- DOCS ---------------

find_package(Doxygen)

set(DOXYGEN_WARNINGS YES)
set(DOXYGEN_WARN_NO_PARAMDOC YES)
set(DOXYGEN_WARN_IF_DOC_ERROR YES)
set(DOXYGEN_WARN_IF_UNDOCUMENTED YES)
set(DOXYGEN_GENERATE_TREEVIEW YES)
set(DOXYGEN_GENERATE_HTML YES)
set(DOXYGEN_GENERATE_MAN NO)
set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_HAVE_DOT YES)
set(DOXYGEN_CALL_GRAPH YES)
set(DOXYGEN_CALLER_GRAPH YES)

set(DOXYGEN_FULL_PATH_NAMES YES)
set(DOXYGEN_STRIP_FROM_PATH "${CMAKE_SOURCE_DIR}")
set(DOXYGEN_EXCLUDE_PATTERNS "*/lib/*" "README.md")
set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/doxygen")

doxygen_add_docs(
        doxygen
        ${PROJECT_SOURCE_DIR}
)
