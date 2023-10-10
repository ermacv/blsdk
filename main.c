#include <stdint.h>
#include <stdbool.h>
// #include "sdkconfig.h"
#include <FreeRTOS.h>
#include <task.h>

#include "board.h"
#include "bflb_mtimer.h"

#define DBG_TAG "SYS"
#include "log.h"

void app_main(void *param) {
  while(true) {
    LOG_I("Ping from task\r\n");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

int main(void) {
    board_init();

    LOG_I("Starting\r\n");


    if (xTaskCreate(app_main, "app_main", 4096, NULL, 5, NULL) != pdPASS) {
        LOG_E("Failed to create app_main task");
        while (true) {
            ;
        }
    }
    LOG_I("Running...\r\n");

    vTaskStartScheduler();

    // while (1) {
    //     LOG_I("ping\r\n");
    //     bflb_mtimer_delay_ms(5000);
    // }
}
