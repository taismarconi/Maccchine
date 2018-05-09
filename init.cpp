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

using namespace std;

#define SCREEN_W 840
#define SCREEN_H 650
#define CAR_H 111

extern int state;

bool doexit = false;
bool redraw = true;

void gestione_menu(ALLEGRO_DISPLAY* display){

	al_install_audio();
   	al_init_acodec_addon();
    	al_init_font_addon();
    	al_init_ttf_addon();
   	
   	al_reserve_samples(10);
   	
    	ALLEGRO_BITMAP *road = NULL;
    	road = al_load_bitmap("media/road.png");

	if(!road) {
   		fprintf(stderr, "failed to create gestione_menu bitmap\n");
		al_destroy_display(display);
    	}
    	
    	ALLEGRO_FONT *titlefont;
    	ALLEGRO_FONT *startfont;
    	ALLEGRO_FONT *instructionsfont;
    	
    	titlefont = al_load_font("media/arcade.ttf", 70, 0);
    	startfont = al_load_font("media/arcade.ttf", 40, 0);
    	instructionsfont = al_load_font("media/arcade.ttf", 25, 0);
	
    	al_draw_bitmap(road, 0, 0, 0);
    	al_draw_text(titlefont, al_map_rgb(0, 0, 0), 260, 100, 0, "Maccchine");
    	al_draw_text(startfont, al_map_rgb(0, 0, 0), 155, 250, 0, "Premi spazio per cominciare");
    	al_draw_text(instructionsfont, al_map_rgb(0, 0, 0), 525, 585, 0, "Esc per uscire");
    	al_draw_text(instructionsfont, al_map_rgb(0, 0, 0), 150, 585, 0, "Usa  le  frecce  per");
    	al_draw_text(instructionsfont, al_map_rgb(0, 0, 0), 150, 600, 0, "evitare  le   auto");
	
	car_t c;
	
	//inizializzo la macchina
	c.x = SCREEN_W / 2.0 + 22.0;
	c.y = SCREEN_H - CAR_H - 75.0;
	
    	ALLEGRO_BITMAP *car = NULL;
    	car = al_load_bitmap("media/car.png");
    	
    	ALLEGRO_BITMAP *car_dx = NULL;
    	car_dx = al_load_bitmap("media/carR.png");
    	
    	ALLEGRO_BITMAP *car_sx = NULL;
    	car_sx = al_load_bitmap("media/carL.png");
    	
    	if(!car || !car_dx || !car_sx) {
    	    fprintf(stderr, "failed to create car bitmap\n");
    	    al_destroy_font(titlefont);
    	    al_destroy_font(startfont);
    	    al_destroy_font(instructionsfont);
    	    al_destroy_bitmap(road);
    	    al_destroy_display(display);
        }
	
	c.imm[0] = car;
	c.imm[1] = car_dx;
	c.imm[2] = car_sx;
	
    	al_draw_bitmap(car, c.x, c.y, 0);
	
    	al_flip_display();
	
    	ALLEGRO_EVENT events;
    	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    	
	al_register_event_source(event_queue, al_get_keyboard_event_source());
    	al_wait_for_event(event_queue, &events);
    	
    	/**if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		state = -1;
		doexit = true;
	}*/
	
	if(events.type==ALLEGRO_EVENT_KEY_DOWN){
    		switch(events.keyboard.keycode){
        		case ALLEGRO_KEY_ESCAPE:
        	    		state = -1;
        	    		doexit = true;
        	    		break;
        		case ALLEGRO_KEY_SPACE: {
                       		al_destroy_font(titlefont);
                        	al_destroy_font(startfont);
                        	al_destroy_font(instructionsfont);
            			moveroad(display, road, c); //in road.cpp
                    	} break;
    		}
	}
}
