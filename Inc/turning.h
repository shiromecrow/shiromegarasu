/*
 * turning.h
 *
 *  Created on: 2019/10/02
 *      Author: sf199
 */

#ifndef TURNING_H_
#define TURNING_H_

#include "parameter.h"


void slalomR(parameter,char test_mode);
void slalomL(parameter,char test_mode);
void turn90R(parameter,char test_mode);
void turn90L(parameter,char test_mode);
void turn180R(parameter,char test_mode);
void turn180L(parameter,char test_mode);
void turn45inR(parameter,char test_mode);
void turn45inL(parameter,char test_mode);
void turn135inR(parameter,char test_mode);
void turn135inL(parameter,char test_mode);
void turn45outR(parameter,char test_mode);
void turn45outL(parameter,char test_mode);
void turn135outR(parameter,char test_mode);
void turn135outL(parameter,char test_mode);
void V90R(parameter,char test_mode);
void V90L(parameter,char test_mode);



void testturning(parameter_speed,int,char,int);




#endif /* TURNING_H_ */
