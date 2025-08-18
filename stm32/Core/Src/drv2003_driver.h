/*
 * a4988_driver.h
 *
 *  Created on: Aug 18, 2025
 *      Author: jakub
 */

#ifndef SRC_DRV2003_DRIVER_H_
#define SRC_DRV2003_DRIVER_H_

#define GPIO_TYPEDEF_M1 GPIOA
#define GPIO_M1_0 GPIO_PIN_0
#define GPIO_M1_1 GPIO_PIN_1
#define GPIO_M1_2 GPIO_PIN_2
#define GPIO_M1_3 GPIO_PIN_3

#define GPIO_TYPEDEF_M2 GPIOA
#define GPIO_M2_0 GPIO_PIN_4
#define GPIO_M2_1 GPIO_PIN_5
#define GPIO_M2_2 GPIO_PIN_6
#define GPIO_M2_3 GPIO_PIN_7

static int8_t cur_motor_step = 8;

static void Motor_Full_Step(
		bool reverse,
		GPIO_TypeDef * gpioTypedef,
		uint16_t gpio0,
		uint16_t gpio1,
		uint16_t gpio2,
		uint16_t gpio3
) {
	switch (cur_motor_step) {
	case 0:
		  HAL_GPIO_WritePin(gpioTypedef, gpio0|gpio1, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(gpioTypedef, gpio2|gpio3, GPIO_PIN_RESET);
		break;
	case 1:
		  HAL_GPIO_WritePin(gpioTypedef, gpio1|gpio2, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(gpioTypedef, gpio0|gpio3, GPIO_PIN_RESET);
		break;
	case 2:
		  HAL_GPIO_WritePin(gpioTypedef, gpio2|gpio3, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(gpioTypedef, gpio0|gpio1, GPIO_PIN_RESET);
		break;
	case 3:
		  HAL_GPIO_WritePin(gpioTypedef, gpio0|gpio3, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(gpioTypedef, gpio1|gpio2, GPIO_PIN_RESET);
		break;
	}

	if (reverse) {
		cur_motor_step--;
	} else {
		cur_motor_step++;
	}

	if (cur_motor_step > 3) cur_motor_step = 0;

	if (cur_motor_step < 0) cur_motor_step = 3;
};


static void Motor_Step_1(bool reverse) {
	Motor_Full_Step(
		reverse,
		GPIO_TYPEDEF_M1,
		GPIO_M1_0,
		GPIO_M1_1,
		GPIO_M1_2,
		GPIO_M1_3
	);
};


static void Motor_Step_2(bool reverse) {
	Motor_Full_Step(
		reverse,
		GPIO_TYPEDEF_M2,
		GPIO_M2_0,
		GPIO_M2_1,
		GPIO_M2_2,
		GPIO_M2_3
	);
};

#endif /* SRC_DRV2003_DRIVER_H_ */
