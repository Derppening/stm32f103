# Use ARM-GCC for crosscompiling
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

find_program(ARM_CC arm-none-eabi-gcc)
find_program(ARM_CXX arm-none-eabi-g++)
find_program(ARM_OBJCOPY arm-none-eabi-objcopy)
find_program(ARM_SIZE arm-none-eabi-size)

if (${CMAKE_VERSION} VERSION_LESS 3.6.0)
    include(CMakeForceCompiler)
    cmake_force_c_compiler(${ARM_CC} GNU)
    cmake_force_cxx_compiler(${ARM_CXX} GNU)
else ()
    set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
    set(CMAKE_C_COMPILER ${ARM_CC})
    set(CMAKE_CXX_COMPILER ${ARM_CXX})
endif ()
