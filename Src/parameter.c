/*
 * parameter.c
 *
 *  Created on: 2019/11/18
 *      Author: sf199
 */
#include "parameter.h"


void input_parameter(void){

speed500.slalom_R.g_speed=500;
speed500.slalom_R.t_speed=500;
speed500.slalom_R.t_acc=9000;
speed500.slalom_R.f_ofset=41;//55;
speed500.slalom_R.e_ofset=25;

speed500.slalom_L.g_speed=500;
speed500.slalom_L.t_speed=500;
speed500.slalom_L.t_acc=9000;
speed500.slalom_L.f_ofset=40;//50;
speed500.slalom_L.e_ofset=29;

//*********************************800********************************************

speed800.slalom_R.g_speed=1000;
speed800.slalom_R.t_speed=1000;
speed800.slalom_R.t_acc=14000;
speed800.slalom_R.f_ofset=0;
speed800.slalom_R.e_ofset=15;

speed800.slalom_L.g_speed=1000;
speed800.slalom_L.t_speed=1000;
speed800.slalom_L.t_acc=14000;
speed800.slalom_L.f_ofset=5;
speed800.slalom_L.e_ofset=5;

speed800.turn90_R.g_speed=500;
speed800.turn90_R.t_speed=650;
speed800.turn90_R.t_acc=15000;
speed800.turn90_R.f_ofset=55;
speed800.turn90_R.e_ofset=40;

speed800.turn90_L.g_speed=500;
speed800.turn90_L.t_speed=650;
speed800.turn90_L.t_acc=15000;
speed800.turn90_L.f_ofset=50;
speed800.turn90_L.e_ofset=44;

speed800.turn180_R.g_speed=500;
speed800.turn180_R.t_speed=650;
speed800.turn180_R.t_acc=15000;
speed800.turn180_R.f_ofset=55;
speed800.turn180_R.e_ofset=40;

speed800.turn180_L.g_speed=500;
speed800.turn180_L.t_speed=650;
speed800.turn180_L.t_acc=15000;
speed800.turn180_L.f_ofset=50;
speed800.turn180_L.e_ofset=44;

speed800.turn45in_R.g_speed=500;
speed800.turn45in_R.t_speed=650;
speed800.turn45in_R.t_acc=15000;
speed800.turn45in_R.f_ofset=55;
speed800.turn45in_R.e_ofset=40;

speed800.turn45in_L.g_speed=500;
speed800.turn45in_L.t_speed=650;
speed800.turn45in_L.t_acc=15000;
speed800.turn45in_L.f_ofset=50;
speed800.turn45in_L.e_ofset=44;

speed800.turn135in_R.g_speed=500;
speed800.turn135in_R.t_speed=650;
speed800.turn135in_R.t_acc=15000;
speed800.turn135in_R.f_ofset=55;
speed800.turn135in_R.e_ofset=40;

speed800.turn135in_L.g_speed=500;
speed800.turn135in_L.t_speed=650;
speed800.turn135in_L.t_acc=15000;
speed800.turn135in_L.f_ofset=50;
speed800.turn135in_L.e_ofset=44;

speed800.turn45out_R.g_speed=500;
speed800.turn45out_R.t_speed=650;
speed800.turn45out_R.t_acc=15000;
speed800.turn45out_R.f_ofset=55;
speed800.turn45out_R.e_ofset=40;

speed800.turn45out_L.g_speed=500;
speed800.turn45out_L.t_speed=650;
speed800.turn45out_L.t_acc=15000;
speed800.turn45out_L.f_ofset=50;
speed800.turn45out_L.e_ofset=44;

speed800.turn135out_R.g_speed=500;
speed800.turn135out_R.t_speed=650;
speed800.turn135out_R.t_acc=15000;
speed800.turn135out_R.f_ofset=55;
speed800.turn135out_R.e_ofset=40;

speed800.turn135out_L.g_speed=500;
speed800.turn135out_L.t_speed=650;
speed800.turn135out_L.t_acc=15000;
speed800.turn135out_L.f_ofset=50;
speed800.turn135out_L.e_ofset=44;

speed800.V90_R.g_speed=500;
speed800.V90_R.t_speed=650;
speed800.V90_R.t_acc=15000;
speed800.V90_R.f_ofset=55;
speed800.V90_R.e_ofset=40;

speed800.V90_L.g_speed=500;
speed800.V90_L.t_speed=650;
speed800.V90_L.t_acc=15000;
speed800.V90_L.f_ofset=50;
speed800.V90_L.e_ofset=44;

//*********************************1000********************************************

speed1000.slalom_R.g_speed=1000;
speed1000.slalom_R.t_speed=550;
speed1000.slalom_R.t_acc=12000;
speed1000.slalom_R.f_ofset=30;
speed1000.slalom_R.e_ofset=60;

speed1000.slalom_L.g_speed=1000;
speed1000.slalom_L.t_speed=550;
speed1000.slalom_L.t_acc=12000;
speed1000.slalom_L.f_ofset=30;
speed1000.slalom_L.e_ofset=60;

speed1000.turn90_R.g_speed=1000;
speed1000.turn90_R.t_speed=400;
speed1000.turn90_R.t_acc=12000;
speed1000.turn90_R.f_ofset=30;
speed1000.turn90_R.e_ofset=60;

speed1000.turn90_L.g_speed=1000;
speed1000.turn90_L.t_speed=400;
speed1000.turn90_L.t_acc=12000;
speed1000.turn90_L.f_ofset=30;
speed1000.turn90_L.e_ofset=60;

speed1000.turn180_R.g_speed=1000;
speed1000.turn180_R.t_speed=500;
speed1000.turn180_R.t_acc=10000;
speed1000.turn180_R.f_ofset=30;
speed1000.turn180_R.e_ofset=70;

speed1000.turn180_L.g_speed=1000;
speed1000.turn180_L.t_speed=500;
speed1000.turn180_L.t_acc=10000;
speed1000.turn180_L.f_ofset=30;
speed1000.turn180_L.e_ofset=70;

speed1000.turn45in_R.g_speed=1000;
speed1000.turn45in_R.t_speed=750;
speed1000.turn45in_R.t_acc=12000;
speed1000.turn45in_R.f_ofset=20;
speed1000.turn45in_R.e_ofset=70;

speed1000.turn45in_L.g_speed=1000;
speed1000.turn45in_L.t_speed=750;
speed1000.turn45in_L.t_acc=12000;
speed1000.turn45in_L.f_ofset=20;
speed1000.turn45in_L.e_ofset=70;

speed1000.turn135in_R.g_speed=1000;
speed1000.turn135in_R.t_speed=680;
speed1000.turn135in_R.t_acc=14000;
speed1000.turn135in_R.f_ofset=20;
speed1000.turn135in_R.e_ofset=50;

speed1000.turn135in_L.g_speed=1000;
speed1000.turn135in_L.t_speed=680;
speed1000.turn135in_L.t_acc=14000;
speed1000.turn135in_L.f_ofset=20;
speed1000.turn135in_L.e_ofset=50;

speed1000.turn45out_R.g_speed=1000;
speed1000.turn45out_R.t_speed=750;
speed1000.turn45out_R.t_acc=14000;
speed1000.turn45out_R.f_ofset=50;
speed1000.turn45out_R.e_ofset=50;

speed1000.turn45out_L.g_speed=1000;
speed1000.turn45out_L.t_speed=750;
speed1000.turn45out_L.t_acc=14000;
speed1000.turn45out_L.f_ofset=50;
speed1000.turn45out_L.e_ofset=50;

speed1000.turn135out_R.g_speed=1000;
speed1000.turn135out_R.t_speed=770;
speed1000.turn135out_R.t_acc=14000;
speed1000.turn135out_R.f_ofset=30;
speed1000.turn135out_R.e_ofset=90;

speed1000.turn135out_L.g_speed=1000;
speed1000.turn135out_L.t_speed=770;
speed1000.turn135out_L.t_acc=14000;
speed1000.turn135out_L.f_ofset=30;
speed1000.turn135out_L.e_ofset=90;

speed1000.V90_R.g_speed=1000;
speed1000.V90_R.t_speed=950;
speed1000.V90_R.t_acc=18000;
speed1000.V90_R.f_ofset=20;
speed1000.V90_R.e_ofset=60;

speed1000.V90_L.g_speed=1000;
speed1000.V90_L.t_speed=950;
speed1000.V90_L.t_acc=18000;
speed1000.V90_L.f_ofset=20;
speed1000.V90_L.e_ofset=60;

//*********************************12/00********************************************

speed1200.slalom_R.g_speed=1200;
speed1200.slalom_R.t_speed=650;
speed1200.slalom_R.t_acc=15000;
speed1200.slalom_R.f_ofset=47;
speed1200.slalom_R.e_ofset=40;

speed1200.slalom_L.g_speed=1200;
speed1200.slalom_L.t_speed=650;
speed1200.slalom_L.t_acc=15000;
speed1200.slalom_L.f_ofset=53;
speed1200.slalom_L.e_ofset=44;

speed1200.turn90_R.g_speed=1200;
speed1200.turn90_R.t_speed=650;
speed1200.turn90_R.t_acc=10000;
speed1200.turn90_R.f_ofset=45;
speed1200.turn90_R.e_ofset=46;

speed1200.turn90_L.g_speed=1200;
speed1200.turn90_L.t_speed=650;
speed1200.turn90_L.t_acc=10000;
speed1200.turn90_L.f_ofset=50;
speed1200.turn90_L.e_ofset=47;

speed1200.turn180_R.g_speed=1200;
speed1200.turn180_R.t_speed=800;
speed1200.turn180_R.t_acc=8000;
speed1200.turn180_R.f_ofset=20;
speed1200.turn180_R.e_ofset=30;

speed1200.turn180_L.g_speed=1200;
speed1200.turn180_L.t_speed=780;
speed1200.turn180_L.t_acc=8000;
speed1200.turn180_L.f_ofset=20;
speed1200.turn180_L.e_ofset=40;

speed1200.turn45in_R.g_speed=1200;
speed1200.turn45in_R.t_speed=900;
speed1200.turn45in_R.t_acc=13000;
speed1200.turn45in_R.f_ofset=25;
speed1200.turn45in_R.e_ofset=60;

speed1200.turn45in_L.g_speed=1200;
speed1200.turn45in_L.t_speed=900;
speed1200.turn45in_L.t_acc=13000;
speed1200.turn45in_L.f_ofset=32;
speed1200.turn45in_L.e_ofset=60;

speed1200.turn135in_R.g_speed=1200;
speed1200.turn135in_R.t_speed=900;
speed1200.turn135in_R.t_acc=12000;
speed1200.turn135in_R.f_ofset=53;
speed1200.turn135in_R.e_ofset=47;

speed1200.turn135in_L.g_speed=1200;
speed1200.turn135in_L.t_speed=900;
speed1200.turn135in_L.t_acc=12000;
speed1200.turn135in_L.f_ofset=40;
speed1200.turn135in_L.e_ofset=55;

speed1200.turn45out_R.g_speed=1200;
speed1200.turn45out_R.t_speed=900;
speed1200.turn45out_R.t_acc=10000;
speed1200.turn45out_R.f_ofset=45;
speed1200.turn45out_R.e_ofset=10;

speed1200.turn45out_L.g_speed=1200;
speed1200.turn45out_L.t_speed=900;
speed1200.turn45out_L.t_acc=10000;
speed1200.turn45out_L.f_ofset=40;
speed1200.turn45out_L.e_ofset=10;

speed1200.turn135out_R.g_speed=1200;
speed1200.turn135out_R.t_speed=1000;
speed1200.turn135out_R.t_acc=12000;
speed1200.turn135out_R.f_ofset=25;
speed1200.turn135out_R.e_ofset=90;

speed1200.turn135out_L.g_speed=1200;
speed1200.turn135out_L.t_speed=1000;
speed1200.turn135out_L.t_acc=12000;
speed1200.turn135out_L.f_ofset=40;
speed1200.turn135out_L.e_ofset=95;

speed1200.V90_R.g_speed=1200;
speed1200.V90_R.t_speed=1650;
speed1200.V90_R.t_acc=24500;
speed1200.V90_R.f_ofset=50;
speed1200.V90_R.e_ofset=65;

speed1200.V90_L.g_speed=1200;
speed1200.V90_L.t_speed=1550;
speed1200.V90_L.t_acc=22000;
speed1200.V90_L.f_ofset=28;
speed1200.V90_L.e_ofset=55;


}
