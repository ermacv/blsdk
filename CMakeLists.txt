###############################################################################
# Minimal CMake version that is needed to process current project
cmake_minimum_required(VERSION 3.20)
# To build compile_commands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
###############################################################################
# CMake specific options that should be enabled before processing the project
# Must be enabled before project()
if(NOT CMAKE_TOOLCHAIN_FILE)
  # Set cross compilation as a default target
  set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_LIST_DIR}/cmake/toolchain/riscv64-unknown-elf.cmake)
endif()
###############################################################################
# Main project name
project(bl808_sdk)
###############################################################################
# Include CPU specific biuld options
# TODO: Make configurable
include(${PROJECT_SOURCE_DIR}/cmake/cpu/e907_m0.cmake)
# Include build options for different build types (Debug, Release, etc.)
include(${PROJECT_SOURCE_DIR}/cmake/build_common/build_types.cmake)
# Include common warning
include(${PROJECT_SOURCE_DIR}/cmake/build_common/warnings.cmake)
# Include common build options that should ne used by all project modules and libraries
include(${PROJECT_SOURCE_DIR}/cmake/build_common/compiler.cmake)
# Include common linker options
include(${PROJECT_SOURCE_DIR}/cmake/build_common/linker.cmake)
###############################################################################
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.c)
target_link_options(${PROJECT_NAME} PRIVATE -T${LINKER_SCRIPT_PATH} -static)
target_link_options(${PROJECT_NAME} PRIVATE -Wl,-Map=$<TARGET_FILE_DIR:${PROJECT_NAME}>/${PROJECT_NAME}.map)
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT_PATH})
###############################################################################
