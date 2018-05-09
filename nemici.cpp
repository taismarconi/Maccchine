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

void move_enemies(enemy_t *&ene) {
	
	int index; float posx;
	srand((unsigned)time(NULL));
	index = rand() % 3; //genera un numero casuale da 0 a 2
	
	//ene[0].x = posx;
	
	if(ene[0].y > SCREEN_H - 10 && ene[0].y < SCREEN_H + 10) {
    		ene[0].y = -CAR_H;
	}
        
    	ene[0].y += 3.0;
    	
	redraw = true;
}
