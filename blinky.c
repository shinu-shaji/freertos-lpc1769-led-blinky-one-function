#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
/*declare a structure for storing delay and led number*/
struct datta {
	int del;
	int led;
} data[3];
/* setup system hardware */
static void prvSetupHardware(void) {
	SystemCoreClockUpdate();
	4
	Board_Init();
	/* Initial LED0 state is off */
	Board_LED_Set(0, true);
	Board_LED_Set(1, true);
	Board_LED_Set(2, true);
}
/*led task*/
static void vLEDTask2(void *pvParameters) {
	/*cast the void pointer*/
	struct datta *dd = pvParameters;
	bool LedState = false;
	vTaskDelay((*dd).del);
	while (1) {
		Board_LED_Set((*dd).led, false);
		vTaskDelay(1000);
		Board_LED_Set((*dd).led, true);
		vTaskDelay(3500);
	}
}
int main(void) {
	data[0].del = 0;
	data[0].led = 0;
	data[1].del = 1500;
	data[1].led = 1;
	data[2].del = 3000;
	data[2].led = 2;
	prvSetupHardware();
	xTaskCreate(vLEDTask2, (signed char* ) "vTaskLed1",
			configMINIMAL_STACK_SIZE, &data[0], (tskIDLE_PRIORITY + 1UL),
			(xTaskHandle *) NULL);
	xTaskCreate(vLEDTask2, (signed char* ) "vTaskLed2",
			configMINIMAL_STACK_SIZE, &data[1], (tskIDLE_PRIORITY + 1UL),
			(xTaskHandle *) NULL);
	
	xTaskCreate(vLEDTask2, (signed char* ) "vTaskLed3",
			configMINIMAL_STACK_SIZE, &data[2], (tskIDLE_PRIORITY + 1UL),
			(xTaskHandle *) NULL);
	vTaskStartScheduler();
	/* Should never arrive here */
	return 1;
}
