#include "FreeRTOS.h"
#include "task.h"

#include <stdio.h>
#include <assert.h>

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    puts("Stack Overflow checked\r\n");
    printf("Task Name %s\r\n", pcTaskName);
    while (1) {
        /*empty here*/
    }
}

void vApplicationMallocFailedHook(void)
{
    printf("Memory Allocate Failed. Current left size is %lu bytes\r\n", xPortGetFreeHeapSize());
    while (1) {
        /*empty here*/
    }
}

void vApplicationIdleHook(void) {}


void app_main(void *param) {
  while(1) {
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

int main(void) {
    BaseType_t rc = xTaskCreate(app_main, "app_main", 256, NULL, 5, NULL);
    assert(rc == pdPASS);
    vTaskStartScheduler();
}
