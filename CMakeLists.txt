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
# Include CPU specific biuld options
# TODO: Make configurable
include(${PROJECT_SOURCE_DIR}/cmake/cpu/e907_m0.cmake)
# Include common warning
include(${PROJECT_SOURCE_DIR}/cmake/build_common/warnings.cmake)
# Include common build options that should ne used by all project modules and libraries
include(${PROJECT_SOURCE_DIR}/cmake/build_common/compiler.cmake)
# Include common linker options
include(${PROJECT_SOURCE_DIR}/cmake/build_common/linker.cmake)
###############################################################################
add_compile_options(-Os)
# blsdk_lhal
set(lhal_path "/home/ermacv/dev/proj/bl/bouffalo_sdk/drivers/lhal")
add_library(blsdk_lhal INTERFACE)
target_sources(blsdk_lhal INTERFACE ${lhal_path}/src/bflb_common.c)
target_sources(blsdk_lhal INTERFACE
  ${lhal_path}/src/bflb_adc.c
  ${lhal_path}/src/bflb_acomp.c
  ${lhal_path}/src/bflb_cks.c
  ${lhal_path}/src/bflb_ef_ctrl.c
  ${lhal_path}/src/bflb_gpio.c
  ${lhal_path}/src/bflb_i2c.c
  ${lhal_path}/src/bflb_dma.c
  ${lhal_path}/src/bflb_rtc.c
  ${lhal_path}/src/bflb_sec_aes.c
  ${lhal_path}/src/bflb_sec_sha.c
  ${lhal_path}/src/bflb_sec_trng.c
  ${lhal_path}/src/bflb_spi.c
  ${lhal_path}/src/bflb_timer.c
  ${lhal_path}/src/bflb_uart.c
  ${lhal_path}/src/bflb_wdg.c
  ${lhal_path}/src/bflb_flash.c
  ${lhal_path}/src/flash/bflb_sf_cfg.c
  ${lhal_path}/src/flash/bflb_xip_sflash.c
  ${lhal_path}/src/flash/bflb_sflash.c
  ${lhal_path}/src/flash/bflb_sf_ctrl.c
)

target_sources(blsdk_lhal INTERFACE 
  ${lhal_path}/src/bflb_dac.c
  ${lhal_path}/src/bflb_emac.c
  ${lhal_path}/src/bflb_ir.c
  ${lhal_path}/src/bflb_mjpeg.c
  ${lhal_path}/src/bflb_pwm_v2.c
  ${lhal_path}/src/bflb_cam.c
  ${lhal_path}/src/bflb_csi.c
  ${lhal_path}/src/bflb_i2s.c
  ${lhal_path}/src/bflb_wo.c
)

# optional
target_sources(blsdk_lhal INTERFACE ${lhal_path}/src/bflb_irq.c)
target_sources(blsdk_lhal INTERFACE ${lhal_path}/src/bflb_l1c.c)
target_sources(blsdk_lhal INTERFACE ${lhal_path}/src/bflb_mtimer.c)

target_include_directories(blsdk_lhal INTERFACE ${lhal_path}/include)
target_include_directories(blsdk_lhal INTERFACE ${lhal_path}/include/arch)
target_include_directories(blsdk_lhal INTERFACE ${lhal_path}/include/arch/risc-v/t-head)
target_include_directories(blsdk_lhal INTERFACE ${lhal_path}/include/arch/risc-v/t-head/Core/Include)
target_include_directories(blsdk_lhal INTERFACE ${lhal_path}/include/arch/risc-v/t-head/csi_dsp/include)
target_include_directories(blsdk_lhal INTERFACE ${lhal_path}/config/bl808)
target_include_directories(blsdk_lhal INTERFACE ${lhal_path}/src/flash)

target_sources(blsdk_lhal INTERFACE ${lhal_path}/include/arch/risc-v/t-head/rv_hart.c)
target_sources(blsdk_lhal INTERFACE ${lhal_path}/include/arch/risc-v/t-head/rv_pmp.c)
target_link_libraries(blsdk_lhal INTERFACE ${lhal_path}/include/arch/risc-v/t-head/csi_dsp/lib/libcsi_xt900p32f_dsp.a)

target_sources(blsdk_lhal INTERFACE ${lhal_path}/config/bl808/device_table.c)

target_compile_definitions(blsdk_lhal INTERFACE BL808)
target_compile_definitions(blsdk_lhal INTERFACE CPU_M0)

target_link_libraries(blsdk_lhal INTERFACE ${lhal_path}/src/pka/libpka.a)

###############################################################################
set(std_path "/home/ermacv/dev/proj/bl/bouffalo_sdk/drivers/soc/bl808/std")
# add_library(blsdk_lhal INTERFACE)
target_sources(blsdk_lhal INTERFACE ${std_path}/startup/m0/start.S)
target_sources(blsdk_lhal INTERFACE ${std_path}/startup/m0/vector.S)
target_sources(blsdk_lhal INTERFACE ${std_path}/startup/m0/riscv_fpu.S)
target_sources(blsdk_lhal INTERFACE ${std_path}/startup/m0/start_load.c)
target_sources(blsdk_lhal INTERFACE ${std_path}/startup/m0/system_bl808.c)
target_sources(blsdk_lhal INTERFACE ${std_path}/startup/m0/interrupt.c)

target_sources(blsdk_lhal INTERFACE ${std_path}/src/bl808_aon.c)
target_sources(blsdk_lhal INTERFACE ${std_path}/src/bl808_clock.c)
target_sources(blsdk_lhal INTERFACE ${std_path}/src/bl808_common.c)
target_sources(blsdk_lhal INTERFACE ${std_path}/src/bl808_ef_cfg.c)
target_sources(blsdk_lhal INTERFACE ${std_path}/src/bl808_glb.c)
target_sources(blsdk_lhal INTERFACE ${std_path}/src/bl808_glb_gpio.c)
target_sources(blsdk_lhal INTERFACE ${std_path}/src/bl808_hbn.c)
target_sources(blsdk_lhal INTERFACE ${std_path}/src/bl808_l1c.c)
target_sources(blsdk_lhal INTERFACE ${std_path}/src/bl808_pds.c)
target_sources(blsdk_lhal INTERFACE ${std_path}/src/bl808_sdh.c)

target_sources(blsdk_lhal INTERFACE ${std_path}/src/bl808_tzc_sec.c)
target_sources(blsdk_lhal INTERFACE ${std_path}/src/bl808_psram_uhs.c)
target_sources(blsdk_lhal INTERFACE ${std_path}/src/bl808_uhs_phy.c)

target_sources(blsdk_lhal INTERFACE ${std_path}/src/bl808_ipc.c)

target_sources(blsdk_lhal INTERFACE ${std_path}/port/bl808_clock.c)

target_include_directories(blsdk_lhal INTERFACE ${std_path}/include)
target_include_directories(blsdk_lhal INTERFACE ${std_path}/include/hardware)

# if("${CPU_ID}" STREQUAL "m0")
# SET(MCPU "e907")
# SET(MARCH "rv32imafcpzpsfoperand_xtheade")
# SET(MABI "ilp32f")
# elseif("${CPU_ID}" STREQUAL "d0")
# SET(MCPU "c906")
# SET(MARCH "rv64imafdcv0p7_zfh_xtheadc")
# SET(MABI "lp64d")
# elseif("${CPU_ID}" STREQUAL "lp")
# SET(MCPU "e902")
# SET(MARCH "rv32emcxtheadse")
# SET(MABI "ilp32e")
# endif()
target_compile_definitions(blsdk_lhal INTERFACE CPU_M0)
target_compile_definitions(blsdk_lhal INTERFACE ARCH_RISCV)
target_compile_definitions(blsdk_lhal INTERFACE CONFIG_IRQ_NUM=80)
target_link_libraries(blsdk_lhal INTERFACE blsdk_components_os)
target_link_libraries(blsdk_lhal INTERFACE blsdk_components_libc)

# sdk_add_compile_definitions(-DARCH_RISCV -DBFLB_USE_HAL_DRIVER)
# sdk_add_compile_options(-march=${MARCH} -mabi=${MABI} -mtune=${MCPU})
# sdk_add_link_options(-march=${MARCH} -mabi=${MABI} -mtune=${MCPU})
set(bsp_path "/home/ermacv/dev/proj/bl/bouffalo_sdk/bsp/board/bl808dk")

###############################################################################
# Components
set(components_path "/home/ermacv/dev/proj/bl/bouffalo_sdk/components")
add_library(blsdk_components_mm INTERFACE)
target_sources(blsdk_components_mm INTERFACE ${components_path}/mm/mem.c)
target_sources(blsdk_components_mm INTERFACE ${components_path}/mm/tlsf/tlsf.c )
target_sources(blsdk_components_mm INTERFACE ${components_path}/mm/tlsf/bflb_tlsf.c)
target_include_directories(blsdk_components_mm INTERFACE ${components_path}/mm)
target_include_directories(blsdk_components_mm INTERFACE ${components_path}/mm/tlsf)
target_link_libraries(blsdk_components_mm INTERFACE blsdk_lhal)
target_compile_definitions(blsdk_components_mm INTERFACE configSTACK_ALLOCATION_FROM_SEPARATE_HEAP=1)
target_link_libraries(blsdk_components_mm INTERFACE blsdk_components_libc)
###############################################################################
# FreeRTOS
add_library(blsdk_components_os INTERFACE)

target_sources(blsdk_components_os INTERFACE ${components_path}/os/freertos/croutine.c)
target_sources(blsdk_components_os INTERFACE ${components_path}/os/freertos/event_groups.c)
target_sources(blsdk_components_os INTERFACE ${components_path}/os/freertos/list.c)
target_sources(blsdk_components_os INTERFACE ${components_path}/os/freertos/queue.c)
target_sources(blsdk_components_os INTERFACE ${components_path}/os/freertos/tasks.c)
target_sources(blsdk_components_os INTERFACE ${components_path}/os/freertos/timers.c)
target_sources(blsdk_components_os INTERFACE ${components_path}/os/freertos/timers.c)
target_sources(blsdk_components_os INTERFACE ${components_path}/os/freertos/freertos_port.c)
target_sources(blsdk_components_os INTERFACE ${components_path}/os/freertos/portable/MemMang/heap_3.c)
# target_sources(blsdk_components_os INTERFACE ${components_path}/mm/mem.c)
target_sources(blsdk_components_os INTERFACE ${components_path}/os/freertos/portable/GCC/RISC-V/portStatTrap.c)
target_sources(blsdk_components_os INTERFACE ${components_path}/os/freertos/portable/GCC/RISC-V/common/port.c)
target_sources(blsdk_components_os INTERFACE ${components_path}/os/freertos/portable/GCC/RISC-V/common/portASM.S)
# target_sources(blsdk_components_os INTERFACE ${components_path}/mm/tlsf/tlsf.c )
# target_sources(blsdk_components_os INTERFACE ${components_path}/mm/tlsf/bflb_tlsf.c)
target_include_directories(blsdk_components_os INTERFACE ${components_path}/os/freertos/include)
target_include_directories(blsdk_components_os INTERFACE ${components_path}/os/freertos/portable/GCC/RISC-V/common)
target_include_directories(blsdk_components_os INTERFACE ${components_path}/os/freertos/portable/GCC/RISC-V/common/chip_specific_extensions/RV32I_CLINT_no_extensions)
target_include_directories(blsdk_components_os INTERFACE ${PROJECT_SOURCE_DIR}) # FreeRTOSConfig.h
# target_include_directories(blsdk_components_os INTERFACE ${components_path}/mm/tlsf)
target_compile_definitions(blsdk_components_os INTERFACE CONFIG_FREERTOS)
target_compile_definitions(blsdk_components_os INTERFACE portasmHANDLE_INTERRUPT=interrupt_entry)
target_compile_definitions(blsdk_components_os INTERFACE default_interrupt_handler=freertos_risc_v_trap_handler)
target_link_libraries(blsdk_components_os INTERFACE blsdk_components_libc)
# target_link_libraries(blsdk_components_os INTERFACE blsdk_lhal)
###############################################################################
# Utils
add_library(blsdk_components_log INTERFACE)
target_sources(blsdk_components_log INTERFACE ${components_path}/utils/log/log.c)
target_sources(blsdk_components_log INTERFACE ${components_path}/utils/log/log.c)
target_sources(blsdk_components_log INTERFACE ${components_path}/utils/log/bflog/bflog.c)
target_include_directories(blsdk_components_log INTERFACE ${components_path}/utils/log)
target_include_directories(blsdk_components_log INTERFACE ${components_path}/utils/log/bflog)
target_link_libraries(blsdk_components_log INTERFACE blsdk_lhal)
target_compile_definitions(blsdk_components_log INTERFACE CONFIG_BFLOG)
target_compile_definitions(blsdk_components_log INTERFACE CONFIG_LOG_LEVEL=3)
target_link_libraries(blsdk_components_log INTERFACE blsdk_components_libc)
###############################################################################
# FatFS
add_library(blsdk_components_fatfs INTERFACE)
target_sources(blsdk_components_fatfs INTERFACE ${components_path}/fs/fatfs/ff.c)
target_sources(blsdk_components_fatfs INTERFACE ${components_path}/fs/fatfs/diskio.c)
target_sources(blsdk_components_fatfs INTERFACE ${components_path}/fs/fatfs/ffsystem.c)
target_sources(blsdk_components_fatfs INTERFACE ${components_path}/fs/fatfs/ffunicode.c)
target_sources(blsdk_components_fatfs INTERFACE ${components_path}/fs/fatfs/diskio.c)
target_include_directories(blsdk_components_fatfs INTERFACE ${components_path}/fs/fatfs)
target_include_directories(blsdk_components_fatfs INTERFACE ${PROJECT_SOURCE_DIR}) # fatfs_conf_user.h
target_compile_definitions(blsdk_components_fatfs INTERFACE CONFIG_FATFS)
target_link_libraries(blsdk_components_fatfs INTERFACE blsdk_components_libc)
###############################################################################
# Timestamp
add_library(blsdk_components_timestamp INTERFACE)
target_sources(blsdk_components_timestamp INTERFACE ${components_path}/utils/bflb_timestamp/bflb_timestamp.c)
target_include_directories(blsdk_components_timestamp INTERFACE ${components_path}/utils/bflb_timestamp)
###############################################################################
# Libc
add_library(blsdk_components_libc INTERFACE)
target_sources(blsdk_components_libc INTERFACE ${components_path}/libc/newlib/port_memory.c)
target_sources(blsdk_components_libc INTERFACE ${components_path}/libc/newlib/syscalls.c)
target_sources(blsdk_components_libc INTERFACE ${components_path}/libc/newlib/port_tty.c)
target_sources(blsdk_components_libc INTERFACE ${components_path}/libc/newlib/port_time.c)
target_sources(blsdk_components_libc INTERFACE ${components_path}/libc/newlib/port_init_fini.c)
target_sources(blsdk_components_libc INTERFACE ${components_path}/libc/newlib/port_file_fatfs.c)
target_compile_definitions(blsdk_components_libc INTERFACE CONFIG_NEWLIB=1)
target_compile_definitions(blsdk_components_libc INTERFACE CONFIG_NEWLIB_FATFS=1)
target_link_libraries(blsdk_components_libc INTERFACE blsdk_components_mm)
target_link_libraries(blsdk_components_libc INTERFACE blsdk_lhal)
target_link_libraries(blsdk_components_libc INTERFACE blsdk_components_fatfs)
target_compile_options(blsdk_components_libc INTERFACE -fno-builtin)
###############################################################################
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.c)
target_sources(${PROJECT_NAME} PRIVATE ${bsp_path}/fw_header.c)
target_sources(${PROJECT_NAME} PRIVATE ${bsp_path}/board.c)
target_include_directories(${PROJECT_NAME} PRIVATE ${bsp_path})
target_link_libraries(${PROJECT_NAME} PRIVATE blsdk_components_libc)
target_link_libraries(${PROJECT_NAME} PRIVATE blsdk_components_log)
target_link_libraries(${PROJECT_NAME} PRIVATE blsdk_lhal)
target_link_libraries(${PROJECT_NAME} PRIVATE blsdk_components_mm)
target_link_libraries(${PROJECT_NAME} PRIVATE blsdk_components_os)
target_link_libraries(${PROJECT_NAME} PRIVATE blsdk_components_timestamp)
target_link_options(${PROJECT_NAME} PRIVATE -T${bsp_path}/bl808_flash_m0.ld -static)
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_DEPENDS ${bsp_path}/bl808_flash_m0.ld)
target_link_options(${PROJECT_NAME} PRIVATE -Wl,-Map=$<TARGET_FILE_DIR:${PROJECT_NAME}>/${PROJECT_NAME}.map)
target_link_options(${PROJECT_NAME} PRIVATE -ufw_header)
target_compile_definitions(${PROJECT_NAME} PRIVATE CONFIG_PSRAM)
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
set(BLFlashCommand "/home/ermacv/dev/proj/bl/bouffalo_sdk/tools/bflb_tools/bouffalo_flash_cube/BLFlashCommand-ubuntu")
add_custom_target(flash
  COMMAND ${BLFlashCommand} 
  --interface=uart
  --baudrate=2000000
  --port=/dev/ttyACM1
  --chipname=bl808
  --cpu_id=m0
  --config=${CMAKE_CURRENT_SOURCE_DIR}/flash_prog_cfg.ini
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  DEPENDS ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin
)
###############################################################################
