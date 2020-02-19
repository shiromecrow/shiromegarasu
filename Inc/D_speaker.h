/*
 * D_speaker.h
 *
 *  Created on: 2019/06/27
 *      Author: sf199
 */

#ifndef D_SPEAKER_H_
#define D_SPEAKER_H_

typedef struct {
	float interval;
	uint16_t waittime;
} soundData;

#define speed 5
#define unknow_storyNUM 843
soundData unknow_story[unknow_storyNUM];
#define tyounenNUM 657
soundData tyounen[tyounenNUM];
#define Zelda_songNUM 98
soundData Zelda_song[Zelda_songNUM];
#define item_getNUM 5
soundData item_get[item_getNUM];
#define seriaNUM 170
soundData seria[seriaNUM];
#define Zelda_nazoNUM 8
soundData Zelda_nazo[Zelda_nazoNUM];
#define missNUM 17
soundData miss[missNUM];


uint16_t calSoundCount(float);

void MakeMusicScale(char);

void interupt_Sound(uint16_t , soundData *);
void interupt_oneSound(char, uint16_t);


void playSoundData(uint16_t, soundData *);

void inputunknow_story();
void inputtyounen();
void inputZelda_song();
void inputitem_get();
void inputseria();
void inputZelda_nazo();
void inputmiss();

short speakermode;

#endif /* D_SPEAKER_H_ */
