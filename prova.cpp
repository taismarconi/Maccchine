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

float mov = 2.0;

int moveit(float &road_y){

	if(road_y > SCREEN_H - 10 && road_y < SCREEN_H + 10 ) {
    		road_y = 0;
    		return 100;
	}
         
    	road_y += mov;
    	return 0;
 }
