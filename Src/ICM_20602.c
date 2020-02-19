/*
 * ICM_20602.c
 *
 *  Created on: 2019/05/07
 *      Author: sf199
 */

#include "spi.h"

#include <stdio.h>

#include "ICM_20602.h"

GYRO_DATA gyro;

static uint8_t set_flag = 0;

uint8_t read_byte(uint8_t reg)

{

	uint8_t ret, val;

	HAL_GPIO_WritePin( CS1_GPIO_Port, CS1_Pin, GPIO_PIN_RESET); //cs = 0;

	ret = reg | 0x80;

	HAL_SPI_Transmit(&hspi1, &ret, 1, 100);

	HAL_SPI_Receive(&hspi1, &val, 1, 100);

	HAL_GPIO_WritePin( CS1_GPIO_Port, CS1_Pin, GPIO_PIN_SET); //cs = 1;

	return val;

}

void write_byte(uint8_t reg, uint8_t val)

{

	uint8_t ret;

	ret = reg & 0x7F;

	HAL_GPIO_WritePin( CS1_GPIO_Port, CS1_Pin, GPIO_PIN_RESET);

	HAL_SPI_Transmit(&hspi1, &ret, 1, 100);

	HAL_SPI_Transmit(&hspi1, &val, 1, 100);

	HAL_GPIO_WritePin( CS1_GPIO_Port, CS1_Pin, GPIO_PIN_SET);

}

void ICM20602_init(void)

{

	uint8_t who_am_i = 0;

// check WHO_AM_I (0x75)

	who_am_i = read_byte(0x75);

// who am i = 0x12

	printf("\r\nwho_am_i = 0x%x\r\n", who_am_i);

// recheck

	if (who_am_i != 0x12) {

		HAL_Delay(100);

		who_am_i = read_byte(0x75);

		if (who_am_i != 0x12) {

			while (1) {

				printf("gyro_error\r");

			}

		}

	}

// set pwr might

// PWR_MIGHT_1 0x6B

	write_byte(0x6B, 0x00);

	HAL_Delay(50);

// PWR_MIGHT_2 0x6C

	write_byte(0x6C, 0x00);

	HAL_Delay(50);

// set gyro config

// GYRO_CONFIG 0x1B

	write_byte(0x1B, 0x18); // use 2000 dps

	HAL_Delay(50);

// ACCEL_CONFIG 0x1C

	write_byte(0x1B, 0x18); // use pm 16g

	HAL_Delay(50);

	set_flag = 1;

}

float ICM20602_GYRO_READ(uint8_t H_reg)

{

	int16_t data = (int16_t) (((uint8_t) read_byte(H_reg) << 8)
			| (uint8_t) read_byte(H_reg + 1));

	float omega = (float) (data / 16.4f);

	return omega;

}

float ICM20602_ACCEL_READ(uint8_t H_reg)

{

	int16_t data = (int16_t) (((uint8_t) read_byte(H_reg) << 8)
			| (uint8_t) read_byte(H_reg + 1));

	float accel = (float) (data / 2048.0f);

	return accel;

}

void ICM20602_DataUpdate(void)

{

	if (set_flag == 1) {

// get yawrate

		gyro.omega_x = ICM20602_GYRO_READ(0x43);

		gyro.omega_y = ICM20602_GYRO_READ(0x45);

		gyro.omega_z = ICM20602_GYRO_READ(0x47);

// get accel

		gyro.accel_x = ICM20602_ACCEL_READ(0x3B);

		gyro.accel_y = ICM20602_ACCEL_READ(0x3D);

		gyro.accel_z = ICM20602_ACCEL_READ(0x3F);

	}

}

void reset_ICM(void) {
	int s = 0;
	angle = 0;
	for (s = 1; s <= 1000; s++) {
		a_speed += gyro.omega_z;
		a_speedx += gyro.omega_x;
		acc0 += gyro.accel_y;
		HAL_Delay(1);
	}
	a_speed = a_speed / 1000;
	a_speedx = a_speedx / 1000;
	acc0 = acc0 / 1000;
	//オフセットする文

	angle = 0;
	anglex = 0;
	gf_speed = 0;
	gf_distance = 0;
	for (s = 0; s < 10; s++) {
		angle_speed_ave[s] = 0;
	}
}

void interrupt_ICM(void) {
	int j = 9;
	angle_speed0 = angle_speed;

	ICM20602_DataUpdate();
	//if(gyro.omega_x >=400)
//	if((gyro.omega_z - a_speed)<=3 && (gyro.omega_z - a_speed)>=-3){
//		gyro.omega_z=a_speed;
//	}
	for (j = 9; j >= 1; j--) {
		angle_speed_ave[j] = angle_speed_ave[j - 1];
	}
	angle_speed_ave[0] = (gyro.omega_z - a_speed) * 90 / 96;

	angle_speed = (angle_speed_ave[0] + angle_speed_ave[1] + angle_speed_ave[2]
			+ angle_speed_ave[3] + angle_speed_ave[4] + angle_speed_ave[5]
			+ angle_speed_ave[6] + angle_speed_ave[7] + angle_speed_ave[8]
			+ angle_speed_ave[9]) / 10;
	//angle_speed=(gyro.omega_z-a_speed)*90/94;//deg/sec
	angle += 0.001 * angle_speed; //deg
	anglex += 0.001 * (gyro.omega_x - a_speedx); //deg
	angle_acceleration = (angle_speed - angle_speed0) * 1000; //deg/sec^2

	gf_distance += gf_speed * 0.001;
	gf_speed += (gyro.accel_y - acc0) * 0.001;

	record_in_gyro();

}
