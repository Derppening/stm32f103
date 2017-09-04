cmake_minimum_required(VERSION 3.9)
project(stm32f103 C CXX ASM)

# Include an error in case the user forgets to specify ARM as a toolchain
if (NOT CMAKE_TOOLCHAIN_FILE)
    message(FATAL_ERROR "Cross compiling only. Please use -DCMAKE_TOOLCHAIN_FILE=rtlib/cmake/arm-toolchain.cmake or use your own toolchain file")
endif ()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

file(GLOB_RECURSE SOURCE_FILES "src/*.c" "src/*.cpp")
file(GLOB_RECURSE INC_FILES "inc/*.h" "inc/*.tpp")

include_directories(
        inc/config
        inc/core
        inc/lib
        inc/user
)

include("cmake/spl.cmake")
include("cmake/stm32103rbt6.cmake")

add_executable(${PROJECT_NAME}.elf ${SOURCE_FILES} ${INC_FILES})
set_target_properties(${PROJECT_NAME}.elf PROPERTIES LINK_FLAGS ${LINKER_FLAGS})
add_custom_target(
        ${PROJECT_NAME}.bin ALL
        COMMAND ${ARM_OBJCOPY} -Obinary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        DEPENDS ${PROJECT_NAME}.elf
)
