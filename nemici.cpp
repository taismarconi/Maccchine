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

extern int num_enemies;
extern bool redraw;
extern float speedinc;

void move_enemies(enemy_t *&ene, int index, int corsia) {
	
	if (ene[index].y > SCREEN_H - 10 && ene[index].y < SCREEN_H + 10) {
    		ene[index].y = -CAR_H;
	}
		
	ene[index].y += 3.0 + speedinc;
	
	switch(corsia) {
		case 0: ene[index].x = 200; break;
		case 1: ene[index].x = 325; break;
		case 2: ene[index].x = 455; break;
		case 3: ene[index].x = 585; break;
	}
    	
	redraw = true;
}
