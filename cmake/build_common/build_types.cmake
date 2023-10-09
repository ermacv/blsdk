###############################################################################
set(CMAKE_BUILD_TYPE_INIT Debug)

# Set specific check for multi config applications (Visual Studio e.g.)
if (NOT CMAKE_CONFIGURATION_TYPES AND 
    NOT CMAKE_NO_BUILD_TYPE AND
    NOT CMAKE_BUILD_TYPE AND
    CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(CMAKE_BUILD_TYPE Debug)
endif()

message("Current build type is ${CMAKE_BUILD_TYPE}")

###############################################################################
if(CMAKE_C_COMPILER_ID MATCHES "GNU")
    set(CMAKE_C_FLAGS_DEBUG "-Og -g3" CACHE INTERNAL "C Compiler options for debug build" FORCE)
    set(CMAKE_CXX_FLAGS_DEBUG "-Og -g3" CACHE INTERNAL "C++ Compiler options for debug build" FORCE)
    set(CMAKE_ASM_FLAGS_DEBUG "-g3" CACHE INTERNAL "ASM Compiler options for debug build" FORCE)
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "-g -g3" CACHE INTERNAL "Linker options for debug build" FORCE)
    ###############################################################################
    set(CMAKE_C_FLAGS_RELEASE "-O3" CACHE INTERNAL "C Compiler options for release build" FORCE)
    set(CMAKE_CXX_FLAGS_RELEASE "-O3" CACHE INTERNAL "C++ Compiler options for release build" FORCE)
    set(CMAKE_ASM_FLAGS_RELEASE "" CACHE INTERNAL "ASM Compiler options for release build" FORCE)
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "" CACHE INTERNAL "Linker options for release build" FORCE)
    ###############################################################################
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "-Og -g3" CACHE INTERNAL "C Compiler options for release with debug info build")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Og -g3" CACHE INTERNAL "C++ Compiler options for release with debug info build")
    set(CMAKE_ASM_FLAGS_RELWITHDEBINFO "-g3" CACHE INTERNAL "ASM Compiler options for release with debug info build")
    set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "" CACHE INTERNAL "Linker options for release with debug info build")
    ###############################################################################
    set(CMAKE_C_FLAGS_MINSIZEREL "-Os" CACHE INTERNAL "C Compiler options for min size release build")
    set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os" CACHE INTERNAL "C++ Compiler options for min size release build")
    set(CMAKE_ASM_FLAGS_MINSIZEREL "" CACHE INTERNAL "ASM Compiler options for min size release build")
    set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "" CACHE INTERNAL "Linker options for min size release build")
endif()
###############################################################################