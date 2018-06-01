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
#include "function.h"

using namespace std;

extern int num_enemies;
extern bool redraw;
extern float speed;
extern bool key[6];

enum MYKEYS {
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE, KEY_ESCAPE
};

void move_car(car_t &c, enemy_t *&ene) {
	
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

void check_collisione(car_t &c, enemy_t *&ene, bool &collisione, ALLEGRO_BITMAP *boom) {
	for (int i = 0; i < num_enemies; i++) {
		if (c.x > ene[i].x - CAR_W + 13 && c.x < ene[i].x + CAR_E - 15) {
			if (c.y < ene[i].y + CAR_H - 10 && c.y > ene[i].y - CAR_H + 10) {
				collisione = true;
				if (ene[i].y <= SCREEN_H - SCOREBAR_SIZE - EXPLOSION_SIZE) {
					al_draw_bitmap(boom, ene[i].x - 30.0, ene[i].y, 0);
				}	
				else {
					al_draw_bitmap(boom, ene[i].x - 30.0, SCREEN_H - SCOREBAR_SIZE - EXPLOSION_SIZE, 0);
				}	
			}
		}
	}
}
