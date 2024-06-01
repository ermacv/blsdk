###############################################################################
set(lhal_path "${SDK_PATH}/drivers/lhal")
set(std_path "${SDK_PATH}/drivers/soc/bl808/std")
set(bsp_path "${SDK_PATH}/bsp/board/bl808dk")
set(components_path "${SDK_PATH}/components")
###############################################################################
# blsdk_lhal
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

target_compile_definitions(blsdk_lhal INTERFACE CPU_M0)
target_compile_definitions(blsdk_lhal INTERFACE ARCH_RISCV)
target_compile_definitions(blsdk_lhal INTERFACE CONFIG_IRQ_NUM=80)
target_link_libraries(blsdk_lhal INTERFACE blsdk_components_os)
# target_link_libraries(blsdk_lhal INTERFACE blsdk_components_libc)
###############################################################################
# Components
add_library(blsdk_components_mm INTERFACE)
target_sources(blsdk_components_mm INTERFACE ${components_path}/mm/mem.c)
target_sources(blsdk_components_mm INTERFACE ${components_path}/mm/tlsf/tlsf.c )
target_sources(blsdk_components_mm INTERFACE ${components_path}/mm/tlsf/bflb_tlsf.c)
target_include_directories(blsdk_components_mm INTERFACE ${components_path}/mm)
target_include_directories(blsdk_components_mm INTERFACE ${components_path}/mm/tlsf)
target_link_libraries(blsdk_components_mm INTERFACE blsdk_lhal)
target_compile_definitions(blsdk_components_mm INTERFACE configSTACK_ALLOCATION_FROM_SEPARATE_HEAP=1)
# target_link_libraries(blsdk_components_mm INTERFACE blsdk_components_libc)
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
# target_link_libraries(blsdk_components_os INTERFACE blsdk_components_libc)
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
# target_compile_definitions(blsdk_components_log INTERFACE CONFIG_BFLOG)
target_compile_definitions(blsdk_components_log INTERFACE CONFIG_LOG)
target_compile_definitions(blsdk_components_log INTERFACE CONFIG_LOG_LEVEL=3)
# target_link_libraries(blsdk_components_log INTERFACE blsdk_components_libc)
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
# target_compile_definitions(blsdk_components_fatfs INTERFACE CONFIG_FATFS)
# target_link_libraries(blsdk_components_fatfs INTERFACE blsdk_components_libc)
###############################################################################
# Timestamp
add_library(blsdk_components_timestamp INTERFACE)
target_sources(blsdk_components_timestamp INTERFACE ${components_path}/utils/bflb_timestamp/bflb_timestamp.c)
target_include_directories(blsdk_components_timestamp INTERFACE ${components_path}/utils/bflb_timestamp)
###############################################################################
# Libc
add_library(blsdk_components_libc INTERFACE)
# target_sources(blsdk_components_libc INTERFACE ${components_path}/libc/newlib/port_memory.c)
# target_sources(blsdk_components_libc INTERFACE ${components_path}/libc/newlib/syscalls.c)
# target_sources(blsdk_components_libc INTERFACE ${components_path}/libc/newlib/port_tty.c)
# target_sources(blsdk_components_libc INTERFACE ${components_path}/libc/newlib/port_time.c)
# target_sources(blsdk_components_libc INTERFACE ${components_path}/libc/newlib/port_init_fini.c)
# target_sources(blsdk_components_libc INTERFACE ${components_path}/libc/newlib/port_file_fatfs.c)
# target_compile_definitions(blsdk_components_libc INTERFACE CONFIG_NEWLIB=1)
# target_compile_definitions(blsdk_components_libc INTERFACE CONFIG_NEWLIB_FATFS=1)
target_link_libraries(blsdk_components_libc INTERFACE blsdk_components_mm)
target_link_libraries(blsdk_components_libc INTERFACE blsdk_lhal)
target_link_libraries(blsdk_components_libc INTERFACE blsdk_components_fatfs)
target_compile_options(blsdk_components_libc INTERFACE -fno-builtin)
# The following sources are used when default libc is used (NOT CONFIG_NEWLIB)
target_sources(blsdk_components_libc INTERFACE ${components_path}/libc/snprintf.c)
target_sources(blsdk_components_libc INTERFACE ${components_path}/libc/sprintf.c)
target_sources(blsdk_components_libc INTERFACE ${components_path}/libc/vsprintf.c)
target_sources(blsdk_components_libc INTERFACE ${components_path}/libc/vsnprintf.c)
target_sources(blsdk_components_libc INTERFACE ${components_path}/libc/printf.c)
target_link_options(blsdk_components_libc INTERFACE -Wl,-wrap,snprintf)
target_link_options(blsdk_components_libc INTERFACE -Wl,-wrap,sprintf)
###############################################################################
add_library(blsdk_bsp STATIC EXCLUDE_FROM_ALL)
target_sources(blsdk_bsp PRIVATE ${bsp_path}/fw_header.c)
target_sources(blsdk_bsp PRIVATE ${bsp_path}/board.c)
target_include_directories(blsdk_bsp PUBLIC ${bsp_path})
target_link_options(blsdk_bsp PUBLIC -T${bsp_path}/bl808_flash_m0.ld -static)
set_target_properties(blsdk_bsp PROPERTIES LINK_DEPENDS ${bsp_path}/bl808_flash_m0.ld)
target_link_options(blsdk_bsp PUBLIC -ufw_header)
target_link_libraries(blsdk_bsp PRIVATE blsdk_lhal)
target_link_libraries(blsdk_bsp PUBLIC blsdk_components_libc)
# target_compile_definitions(blsdk_bsp INTERFACE CONFIG_PSRAM)
###############################################################################