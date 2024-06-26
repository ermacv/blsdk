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
project(bl808_sdk LANGUAGES C ASM)
###############################################################################
add_definitions(-DCPU_M0)
add_definitions(-DARCH_RISCV)
add_definitions(-DBL808)
###############################################################################
include(${PROJECT_SOURCE_DIR}/cmake/project.cmake)
###############################################################################
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.c)
target_link_libraries(${PROJECT_NAME} PRIVATE blsdk_components_libc)
target_link_libraries(${PROJECT_NAME} PRIVATE blsdk_components_log)
target_link_libraries(${PROJECT_NAME} PRIVATE blsdk_components_mm)
target_link_libraries(${PROJECT_NAME} PRIVATE blsdk_components_os)
target_link_libraries(${PROJECT_NAME} PRIVATE blsdk_bsp_fw_header)
target_link_libraries(${PROJECT_NAME} PRIVATE blsdk_components_lwip)
target_link_libraries(${PROJECT_NAME} PRIVATE blsdk_components_mbedtls)
target_link_libraries(${PROJECT_NAME} PRIVATE blsdk_components_wifi)
target_link_options(${PROJECT_NAME} PRIVATE -T${PROJECT_SOURCE_DIR}/bl808_flash_m0.ld -static)
target_link_options(${PROJECT_NAME} PRIVATE -Wl,-Map=$<TARGET_FILE_DIR:${PROJECT_NAME}>/${PROJECT_NAME}.map)
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".elf")
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_DEPENDS ${PROJECT_SOURCE_DIR}/bl808_flash_m0.ld)
###############################################################################
add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE_DIR:${PROJECT_NAME}>/${PROJECT_NAME}.map ${PROJECT_NAME}.map
  COMMAND ${CMAKE_OBJCOPY} ARGS -Oihex $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_NAME}.hex
  COMMAND ${CMAKE_OBJCOPY} ARGS -Obinary $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_NAME}.bin
  DEPENDS ${PROJECT_NAME}
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)
###############################################################################
set(BLFlashCommand "/home/ermacv/dev/proj/mine/bl/bouffalo_sdk/tools/bflb_tools/bouffalo_flash_cube/BLFlashCommand-ubuntu")
add_custom_target(flash
  COMMAND ${BLFlashCommand} 
  --interface=uart
  --baudrate=2000000
  --port=/dev/ttyACM1
  --chipname=bl808
  --cpu_id=m0
  --config=${CMAKE_CURRENT_SOURCE_DIR}/flash_prog_cfg.ini
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  DEPENDS ${PROJECT_NAME} ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin
)
###############################################################################
