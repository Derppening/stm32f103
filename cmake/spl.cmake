if (NOT SOURCE_FILES)
    message(FATAL_ERROR "Variable SOURCE_FILES must be defined before including spl.cmake")
endif ()
if (NOT INC_FILES)
    message(FATAL_ERROR "Variable INC_FILES must be defined before including spl.cmake")
endif ()

add_definitions(-DUSE_STDPERIPH_DRIVER)

file(GLOB_RECURSE SPL_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/lib/*.c")
file(GLOB_RECURSE SPL_INC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/lib/*.h")

list(APPEND SOURCE_FILES ${SPL_SOURCE_FILES})
list(APPEND INC_FILES ${SPL_INC_FILES})

include_directories(SYSTEM
        lib/
        lib/STM32F10x_StdPeriph_Driver/inc
        lib/CMSIS/CM3/CoreSupport
        lib/CMSIS/CM3/DeviceSupport/ST/STM32F10x
)
