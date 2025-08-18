/*
 * a4988_driver.h
 *
 *  Created on: Aug 18, 2025
 *      Author: jakub
 */

#ifndef SRC_A4988_DRIVER_H_
#define SRC_A4988_DRIVER_H_

#define GPIO_TYPEDEF_M1 GPIOA
#define GPIO_M1_DIR GPIO0
#define GPIO_M1_STEP GPIO1

#define GPIO_TYPEDEF_M2 GPIOA
#define GPIO_M2_DIR GPIO2
#define GPIO_M2_STEP GPIO3


#define STEP_HIGH_DURATION_MS 50

sprawdz jaka moze byc najmniejsza dlugosc stanu wysokiego


static void Motor_Full_Step(bool reverse) {
	  HAL_GPIO_WritePin(gpioTypedef, gpio0|gpio1, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(gpioTypedef, gpio2|gpio3, GPIO_PIN_RESET);
}


// https://www.pololu.com/product/1182



#endif /* SRC_A4988_DRIVER_H_ */
