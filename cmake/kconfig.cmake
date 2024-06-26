add_custom_target(config-dir ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory config)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/config/sdkconfig.h
  COMMAND ${PROJECT_SOURCE_DIR}/tools/kconfig/gensdkconfig.py 
  --sdkpath ${PROJECT_SOURCE_DIR} 
  --header ${CMAKE_CURRENT_BINARY_DIR}/config/ 
  --projectdir ${CMAKE_CURRENT_SOURCE_DIR} 
  --env BFLB_BOARD_DIR=${BOARD_DIR} 
  --env BFLB_BOARD=${BOARD} 
  --env BFLB_CHIP=${CHIP} 
  --env BFLB_CPU_ID=${CPU_ID}
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/sdkconfig
  COMMENT "Generating config/sdkconfig.h"
  VERBATIM
)

add_library(sdk_intf_lib INTERFACE)
target_sources(sdk_intf_lib INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/config/sdkconfig.h)

add_custom_target(config 
  COMMAND ${PROJECT_SOURCE_DIR}/tools/kconfig/gensdkconfig.py
  --sdkpath ${PROJECT_SOURCE_DIR}
  --menuconfig 1
  --cmake 1
  --projectdir ${CMAKE_CURRENT_SOURCE_DIR}
  --env BFLB_BOARD_DIR=${BOARD_DIR}
  --env BFLB_BOARD=${BOARD}
  --env BFLB_CHIP=${CHIP}
  --env BFLB_CPU_ID=${CPU_ID}
)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/sdkconfig
  COMMAND ${PROJECT_SOURCE_DIR}/tools/kconfig/gensdkconfig.py 
  --sdkpath ${PROJECT_SOURCE_DIR} 
  --projectdir ${CMAKE_CURRENT_SOURCE_DIR} 
  --env BFLB_BOARD_DIR=${BOARD_DIR} 
  --env BFLB_BOARD=${BOARD} 
  --env BFLB_CHIP=${CHIP} 
  --env BFLB_CPU_ID=${CPU_ID}
  COMMENT "Generating sdkconfig"
  VERBATIM
)

add_custom_target(proj.conf
  COMMAND ${PROJECT_SOURCE_DIR}/tools/kconfig/gensdkconfig.py
  --sdkpath ${PROJECT_SOURCE_DIR}
  --cmake 1
  --projectdir
  ${CMAKE_CURRENT_SOURCE_DIR}
  --env BFLB_BOARD_DIR=${BOARD_DIR}
  --env BFLB_BOARD=${BOARD}
  --env BFLB_CHIP=${CHIP}
  --env BFLB_CPU_ID=${CPU_ID}
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/sdkconfig
  COMMENT "Generating proj.conf"
  VERBATIM
)

set_property(
  DIRECTORY
  APPEND
  PROPERTY CMAKE_CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/proj.conf   
)

message(STATUS "SDK: proj.conf file: ${proj_conf_file}")                   