#include <stdint.h>
#include <stdbool.h>
#include <FreeRTOS.h>
#include <task.h>

#include "bflb_mtimer.h"
#include "bflb_flash.h"
#include "bflb_clock.h"
#include "bflb_uart.h"
#include "bl808_glb.h"
#include "bl808_tzc_sec.h"
#include "mem.h"

#define DBG_TAG "SYS"
#include "log.h"

#define DEFAULT_TEST_UART                "uart1"
#define DEFAULT_TEST_UART_DMA_TX_REQUEST DMA_REQUEST_UART1_TX
#define DEFAULT_TEST_UART_DMA_RX_REQUEST DMA_REQUEST_UART1_RX
#define DEFAULT_TEST_UART_DMA_TDR        DMA_ADDR_UART1_TDR
#define DEFAULT_TEST_UART_DMA_RDR        DMA_ADDR_UART1_RDR

#define CONFIG_D0_FLASH_ADDR             0x100000
#define CONFIG_LP_FLASH_ADDR             0x20000
static struct bflb_device_s *uart0;

extern uint32_t __HeapBase;
extern uint32_t __HeapLimit;
extern uint32_t __psram_heap_base;
extern uint32_t __psram_limit;
extern void bflb_uart_set_console(struct bflb_device_s *dev);

void app_main(void *param) {
  while(true) {
    LOG_I("Ping from task\r\n");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

static void console_init()
{
    struct bflb_device_s *gpio;

    gpio = bflb_device_get_by_name("gpio");
#if defined(CPU_M0)
    bflb_gpio_uart_init(gpio, GPIO_PIN_14, GPIO_UART_FUNC_UART0_TX);
    bflb_gpio_uart_init(gpio, GPIO_PIN_15, GPIO_UART_FUNC_UART0_RX);
#elif defined(CPU_D0)
    /* sipeed m1s dock */
    bflb_gpio_init(gpio, GPIO_PIN_16, 21 | GPIO_ALTERNATE | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_1);
    bflb_gpio_init(gpio, GPIO_PIN_17, 21 | GPIO_ALTERNATE | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_1);
#elif defined(CPU_LP)
    /* map GPIO_PIN_18 and GPIO_PIN_19 as UART for LP core */
    bflb_gpio_uart_init(gpio, GPIO_PIN_18, GPIO_UART_FUNC_UART1_TX);
    bflb_gpio_uart_init(gpio, GPIO_PIN_19, GPIO_UART_FUNC_UART1_RX);
#endif
    struct bflb_uart_config_s cfg;
    cfg.baudrate = 2000000;
    cfg.data_bits = UART_DATA_BITS_8;
    cfg.stop_bits = UART_STOP_BITS_1;
    cfg.parity = UART_PARITY_NONE;
    cfg.flow_ctrl = 0;
    cfg.tx_fifo_threshold = 7;
    cfg.rx_fifo_threshold = 7;
#if defined(CPU_M0)
    uart0 = bflb_device_get_by_name("uart0");
#elif defined(CPU_D0)
    uart0 = bflb_device_get_by_name("uart3");
#elif defined(CPU_LP)
    uart0 = bflb_device_get_by_name("uart1");
#endif
    bflb_uart_init(uart0, &cfg);
    bflb_uart_set_console(uart0);
}

static void system_clock_init(void)
{
    /* wifipll/audiopll */
    GLB_Power_On_XTAL_And_PLL_CLK(GLB_XTAL_40M, GLB_PLL_WIFIPLL |
                                                    GLB_PLL_CPUPLL |
                                                    GLB_PLL_UHSPLL |
                                                    GLB_PLL_MIPIPLL);

    GLB_Set_MCU_System_CLK(GLB_MCU_SYS_CLK_WIFIPLL_320M);
    GLB_Set_DSP_System_CLK(GLB_DSP_SYS_CLK_CPUPLL_400M);
    GLB_Config_CPU_PLL(GLB_XTAL_40M, cpuPllCfg_480M);

    CPU_Set_MTimer_CLK(ENABLE, CPU_Get_MTimer_Source_Clock() / 1000 / 1000 - 1);
}

static void peripheral_clock_init(void)
{
    PERIPHERAL_CLOCK_ADC_DAC_ENABLE();
    PERIPHERAL_CLOCK_SEC_ENABLE();
    PERIPHERAL_CLOCK_DMA0_ENABLE();
    PERIPHERAL_CLOCK_UART0_ENABLE();
    PERIPHERAL_CLOCK_UART1_ENABLE();
    PERIPHERAL_CLOCK_SPI0_1_ENABLE();
    PERIPHERAL_CLOCK_I2C0_ENABLE();
    PERIPHERAL_CLOCK_PWM0_ENABLE();
    PERIPHERAL_CLOCK_TIMER0_1_WDG_ENABLE();
    PERIPHERAL_CLOCK_IR_ENABLE();
    PERIPHERAL_CLOCK_I2S_ENABLE();
    PERIPHERAL_CLOCK_USB_ENABLE();
    PERIPHERAL_CLOCK_CAN_UART2_ENABLE();

    GLB_Set_UART_CLK(ENABLE, HBN_UART_CLK_XCLK, 0);
    GLB_Set_DSP_UART0_CLK(ENABLE, GLB_DSP_UART_CLK_DSP_XCLK, 0);
    GLB_Set_SPI_CLK(ENABLE, GLB_SPI_CLK_MCU_MUXPLL_160M, 0);
    GLB_Set_I2C_CLK(ENABLE, GLB_I2C_CLK_XCLK, 0);
    GLB_Set_IR_CLK(ENABLE, GLB_IR_CLK_SRC_XCLK, 19);
    GLB_Set_ADC_CLK(ENABLE, GLB_ADC_CLK_XCLK, 1);
    GLB_Set_DIG_CLK_Sel(GLB_DIG_CLK_XCLK);
    GLB_Set_DIG_512K_CLK(ENABLE, ENABLE, 0x4E);
    GLB_Set_PWM1_IO_Sel(GLB_PWM1_IO_DIFF_END);
    GLB_Set_CAM_CLK(ENABLE, GLB_CAM_CLK_WIFIPLL_96M, 3);

    GLB_Set_PKA_CLK_Sel(GLB_PKA_CLK_MCU_MUXPLL_160M);

#ifdef CONFIG_BSP_SDH_SDCARD
    PERIPHERAL_CLOCK_SDH_ENABLE();
    uint32_t tmp_val;
    tmp_val = BL_RD_REG(PDS_BASE, PDS_CTL5);
    uint32_t tmp_val2 = BL_GET_REG_BITS_VAL(tmp_val, PDS_CR_PDS_GPIO_KEEP_EN);
    tmp_val2 &= ~(1 << 0);
    tmp_val = BL_SET_REG_BITS_VAL(tmp_val, PDS_CR_PDS_GPIO_KEEP_EN, tmp_val2);
    BL_WR_REG(PDS_BASE, PDS_CTL5, tmp_val);
    GLB_AHB_MCU_Software_Reset(GLB_AHB_MCU_SW_SDH);
#endif
#ifdef CONFIG_BSP_CSI
    GLB_CSI_Config_MIPIPLL(2, 0x21000);
    GLB_CSI_Power_Up_MIPIPLL();
    GLB_Set_DSP_CLK(ENABLE, GLB_DSP_CLK_MUXPLL_160M, 1);
#endif
    GLB_Set_USB_CLK_From_WIFIPLL(1);
}

int main(void) {
    uintptr_t flag = bflb_irq_save();

    GLB_Halt_CPU(GLB_CORE_ID_D0);
    GLB_Halt_CPU(GLB_CORE_ID_LP);

    int ret = bflb_flash_init();

    system_clock_init();
    peripheral_clock_init();
    bflb_irq_initialize();

    console_init();

#ifdef CONFIG_PSRAM
#ifndef CONFIG_PSRAM_COPY_CODE
    if (uhs_psram_init() < 0) {
        while (1) {
        }
    }
#endif
    // extern uint32_t __psram_load_addr;

    // extern uint32_t __psram_data_start__;
    // extern uint32_t __psram_data_end__;

    // uint32_t *pSrc, *pDest;

    // /* BF Add psram data copy */
    // pSrc = &__psram_load_addr;
    // pDest = &__psram_data_start__;

    // for (; pDest < &__psram_data_end__;) {
    //     *pDest++ = *pSrc++;
    // }

    // heap_len = ((size_t)&__psram_limit - (size_t)&__psram_heap_base);
    // pmem_init((void *)&__psram_heap_base, heap_len);
#endif

    size_t heap_len = ((size_t)&__HeapLimit - (size_t)&__HeapBase);
    kmem_init((void *)&__HeapBase, heap_len);

    if (ret != 0) {
        printf("flash init fail!!!\r\n");
    }

    printf("dynamic memory init success,heap size = %d Kbyte \r\n", ((size_t)&__HeapLimit - (size_t)&__HeapBase) / 1024);

    printf("sig1:%08x\r\n", BL_RD_REG(GLB_BASE, GLB_UART_CFG1));
    printf("sig2:%08x\r\n", BL_RD_REG(GLB_BASE, GLB_UART_CFG2));

    log_start();

#if (defined(CONFIG_LUA) || defined(CONFIG_BFLOG) || defined(CONFIG_FATFS))
    rtc = bflb_device_get_by_name("rtc");
#endif

    /* set CPU D0 boot XIP address and flash address */
    Tzc_Sec_Set_CPU_Group(GLB_CORE_ID_D0, 1);
    /* D0 boot from 0x58000000 */
    GLB_Set_CPU_Reset_Address(GLB_CORE_ID_D0, 0x58000000);
    /* D0 image offset on flash is CONFIG_D0_FLASH_ADDR+0x1000(header) */
    bflb_sf_ctrl_set_flash_image_offset(CONFIG_D0_FLASH_ADDR + 0x1000, 1, SF_CTRL_FLASH_BANK0);

    Tzc_Sec_Set_CPU_Group(GLB_CORE_ID_LP, 0);
    /* LP boot from 0x58020000 */
    GLB_Set_CPU_Reset_Address(GLB_CORE_ID_LP, 0x58020000);

    bflb_irq_restore(flag);

    // GLB_Release_CPU(GLB_CORE_ID_D0);
    // GLB_Release_CPU(GLB_CORE_ID_LP);

    // /* release d0 and then do can run */
    // BL_WR_WORD(IPC_SYNC_ADDR1, IPC_SYNC_FLAG);
    // BL_WR_WORD(IPC_SYNC_ADDR2, IPC_SYNC_FLAG);
    L1C_DCache_Clean_By_Addr(IPC_SYNC_ADDR1, 8);

    LOG_I("Starting\r\n");


    if (xTaskCreate(app_main, "app_main", 4096, NULL, 5, NULL) != pdPASS) {
        LOG_E("Failed to create app_main task");
        while (true) {
            ;
        }
    }
    LOG_I("Running...\r\n");
    vTaskStartScheduler();
}