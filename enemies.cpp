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

#define SCREEN_H 650
#define SCREEN_W 840
#define CAR_H 111

extern bool redraw;

void move_enemies(enemy_t *&ene, int index, int &corsia) {
	
	switch(corsia) {
		case 0: ene[index].x = 195; break;
		case 1: ene[index].x = 260; break;
		case 2: ene[index].x = 325; break;
		case 3: ene[index].x = 395; break;
		case 4: ene[index].x = 455; break;
		case 5: ene[index].x = 530; break;
		case 6: ene[index].x = 588; break;
	}
    	
	redraw = true;
}
