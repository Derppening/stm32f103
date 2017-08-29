cmake_minimum_required(VERSION 3.9)
project(stm32f103 C CXX ASM)

# Include an error in case the user forgets to specify ARM as a toolchain
if (NOT CMAKE_TOOLCHAIN_FILE)
    message(FATAL_ERROR "Cross compiling only. Please use -DCMAKE_TOOLCHAIN_FILE=rtlib/cmake/arm-toolchain.cmake or use your own toolchain file")
endif ()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

add_definitions(-DSTM32F10X_HD)
add_definitions(-DUSE_STDPERIPH_DRIVER)

set(COMMON_FLAGS "-DSTM32F103VCT6 -DSTM32F1 -mcpu=cortex-m3 -mthumb -msoft-float")
set(CMAKE_C_FLAGS "${COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS}")
set(LINKER_FLAGS "-T${CMAKE_CURRENT_SOURCE_DIR}/STM32.ld -D_ROM=256K -D_RAM=48K -DSTM32F1 -D_ROM_OFF=0x08000000 -D_RAM_OFF=0x20000000 -lc -lnosys --specs=rdimon.specs -Wl,--gc-sections")

file(GLOB_RECURSE SOURCE_FILES "src/*.c" "src/*.cpp" "lib/*.c" "lib/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/gcc_ride7/startup_stm32f10x_hd.s")
file(GLOB_RECURSE INC_FILES "src/*.h" "src/*.tpp" "lib/*.h")
include_directories(
        src/config
        src/core
        src/lib
        src/user
        lib/
        lib/STM32F10x_StdPeriph_Driver/inc
        lib/CMSIS/CM3/CoreSupport
        lib/CMSIS/CM3/DeviceSupport/ST/STM32F10x
)

add_executable(${PROJECT_NAME}.elf ${SOURCE_FILES} ${INC_FILES})
set_target_properties(${PROJECT_NAME}.elf PROPERTIES LINK_FLAGS ${LINKER_FLAGS})
add_custom_target(
        ${PROJECT_NAME}.bin ALL
        COMMAND ${ARM_OBJCOPY} -Obinary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        DEPENDS ${PROJECT_NAME}.elf
)
