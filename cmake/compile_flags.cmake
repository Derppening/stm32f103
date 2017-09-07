set(CMAKE_C_STANDARD_REQUIRED YES)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CXX_WARN_FLAGS "-pedantic -Wall -Wextra\
    -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Winvalid-pch\
    -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wmissing-format-attribute -Wnoexcept -Wno-unused -Wodr\
    -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo\
    -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wswitch-enum -Wundef -Wuseless-cast\
    -Wzero-as-null-pointer-constant")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_WARN_FLAGS}")