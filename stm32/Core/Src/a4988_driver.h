/*
 * a4988_driver.h
 *
 *  Created on: Aug 18, 2025
 *      Author: jakub
 */

#ifndef SRC_A4988_DRIVER_H_
#define SRC_A4988_DRIVER_H_

#define GPIO_TYPEDEF_M1 GPIOA
#define GPIO_M1_DIR GPIO_PIN_0
#define GPIO_M1_STEP GPIO_PIN_1

#define GPIO_TYPEDEF_M2 GPIOA
#define GPIO_M2_DIR GPIO_PIN_2
#define GPIO_M2_STEP GPIO_PIN_3

// https://www.pololu.com/file/0J450/A4988.pdf
#define STEP_HIGH_DURATION_MS 2


static void Motor_Full_Step(
	bool reverse,
	GPIO_TypeDef * gpioTypedef,
	uint16_t gpioDir,
	uint16_t gpioStep
) {
	if (reverse) {
		HAL_GPIO_WritePin (gpioTypedef, gpioDir, GPIO_PIN_RESET);
	} else {
		HAL_GPIO_WritePin (gpioTypedef, gpioDir, GPIO_PIN_SET);
	}

	HAL_GPIO_WritePin(gpioTypedef, gpioStep, GPIO_PIN_SET);

	HAL_Delay(STEP_HIGH_DURATION_MS);

	HAL_GPIO_WritePin(gpioTypedef, gpioStep, GPIO_PIN_RESET);
}

static void Motor_Step_1(bool reverse) {
	Motor_Full_Step(
		reverse,
		GPIO_TYPEDEF_M1,
		GPIO_M1_DIR,
		GPIO_M1_STEP
	);
};


static void Motor_Step_2(bool reverse) {
	Motor_Full_Step(
		reverse,
		GPIO_TYPEDEF_M2,
		GPIO_M2_DIR,
		GPIO_M2_STEP
	);
};

// https://www.pololu.com/product/1182



#endif /* SRC_A4988_DRIVER_H_ */
