###############################################################################
if(NOT BOUFFALO_SDK_PATH AND DEFINED ENV{BOUFFALO_SDK_PATH})
  set(BOUFFALO_SDK_PATH $ENV{BOUFFALO_SDK_PATH})
  # Use shorter path variable:
  set(SDK_PATH ${BOUFFALO_SDK_PATH})
else()
  message(FATAL_ERROR "BOUFFALO_SDK_PATH environment variable is not defined")
endif()
###############################################################################
include(${CMAKE_CURRENT_LIST_DIR}/cpu/e907_m0.cmake)
# Include common warning
include(${CMAKE_CURRENT_LIST_DIR}/build_common/warnings.cmake)
# Include common build options that should ne used by all project modules and libraries
include(${CMAKE_CURRENT_LIST_DIR}/build_common/compiler.cmake)
# Include common linker options
include(${CMAKE_CURRENT_LIST_DIR}/build_common/linker.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/kconfig.cmake)
###############################################################################
add_compile_options(-Os) # TODO: Temporary
###############################################################################
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/sdk)
###############################################################################

