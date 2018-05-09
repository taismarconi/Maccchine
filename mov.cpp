#include <iostream>
#include <stdio.h>
#include <cstdlib> 
#include <ctime>
#include <fstream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "data.h"

#define SCREEN_H 650
#define SCREEN_W 840
#define CAR_H 111

extern bool redraw;
extern float speed;
extern bool key[4];

enum MYKEYS {
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

void move_car(car_t &c) {
	
	if(key[KEY_UP] && c.y > 5) {
        	c.y -= speed;
        }

	if(key[KEY_DOWN] && c.y < SCREEN_H - CAR_H - 75.0) {
		c.y += speed;
	}

	if(key[KEY_LEFT] && c.x > 140) {
		c.x -= speed;
	}

	if(key[KEY_RIGHT] && c.x < SCREEN_W - 215) {
		c.x += speed;
	}

	redraw = true;
}
