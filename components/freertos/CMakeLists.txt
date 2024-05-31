###############################################################################
cmake_minimum_required(VERSION 3.20)
###############################################################################
project(freertos LANGUAGES C ASM)
###############################################################################
add_library(freertos STATIC EXCLUDE_FROM_ALL)
target_sources(freertos PRIVATE croutine.c)
target_sources(freertos PRIVATE event_groups.c)
target_sources(freertos PRIVATE list.c)
target_sources(freertos PRIVATE queue.c)
target_sources(freertos PRIVATE stream_buffer.c)
target_sources(freertos PRIVATE tasks.c)
target_sources(freertos PRIVATE timers.c)
target_sources(freertos PRIVATE portable/GCC/RISC-V/port.c)
target_sources(freertos PRIVATE portable/GCC/RISC-V/portASM.S)
target_sources(freertos PRIVATE portable/GCC/RISC-V/port_stat_trap.c)
target_sources(freertos PRIVATE portable/MemMang/heap_5.c)
target_sources(freertos PRIVATE panic/panic_c.c)
target_include_directories(freertos PUBLIC include)
target_include_directories(freertos PUBLIC misaligned)
target_include_directories(freertos PUBLIC panic)
target_include_directories(freertos PUBLIC portable/GCC/RISC-V)
target_include_directories(freertos PUBLIC portable/GCC/RISC-V/chip_specific_extensions/Thead_E906FD_RV32IMAFDC)
###############################################################################