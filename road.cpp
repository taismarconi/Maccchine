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

#define SCREEN_H 650
#define SCREEN_W 840
#define CAR_H 111

const char nome_file[12] = "record.txt";

const float FPS = 60;

float speed = 4.0;
float road_y = 2.0;
float speedinc = 0.2;
//float corsie[4] = {200, 325, 455, 585};

int num_enemies = 3;

extern int state;
extern bool doexit;
extern bool redraw;

enum MYKEYS {
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

bool key[4] = { false, false, false, false };

void moveroad(ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* road, car_t &c) {
	
	int index, corsia;
	
	//inizializzo le altre struct
	enemy_t *ene;
	ene = new enemy_t [num_enemies];
	
	score_t score;
	
	//inizializzo i nemici
	ene[0].x = 200; ene[0].y = -CAR_H; ene[0].imm = al_load_bitmap("media/bcar.png");
	ene[1].x = 325; ene[1].y = -CAR_H; ene[1].imm = al_load_bitmap("media/gcar.png");
	ene[2].x = 455; ene[2].y = -CAR_H; ene[2].imm = al_load_bitmap("media/wwcar.png");
	
	score.punteggio = 0;
	std::ifstream ifs("record.txt");
	ifs>>score.record;
	
	ALLEGRO_BITMAP *scorebar = NULL;
    	scorebar = al_load_bitmap("media/score-bar.png");
    
    	ALLEGRO_FONT *punteggiofont;
    	ALLEGRO_FONT *numerofont;
    	ALLEGRO_FONT *recordfont;
    	ALLEGRO_FONT *scorefont;
    			
	punteggiofont = al_load_font("media/arcade.ttf", 30, 0);
	numerofont = al_load_font("media/arcade.ttf", 40, 0);
	recordfont = al_load_font("media/arcade.ttf", 30, 0);
	scorefont = al_load_font("media/arcade.ttf", 40, 0);
	
	ALLEGRO_TIMER *timer = NULL;

	timer = al_create_timer(1.0 / FPS);
   	if(!timer) {
      		fprintf(stderr, "failed to create timer!\n");
    	}

    	ALLEGRO_EVENT_QUEUE *event_queue_one = NULL;
	event_queue_one = al_create_event_queue();
   	
   	if(!event_queue_one) {
    		fprintf(stderr, "failed to create event_queue!\n");
      		al_destroy_bitmap(road);
      		al_destroy_display(display);
      		al_destroy_timer(timer);
   	}
 
   	al_register_event_source(event_queue_one, al_get_display_event_source(display));
   	al_register_event_source(event_queue_one, al_get_timer_event_source(timer));
   	al_register_event_source(event_queue_one, al_get_keyboard_event_source());
 
   	al_flip_display();
 
   	al_start_timer(timer);

   	while(!doexit) {
      		ALLEGRO_EVENT ev;
      		al_wait_for_event(event_queue_one, &ev);
		
      		if(ev.type == ALLEGRO_EVENT_TIMER) {

      			score.punteggio += moveit(road_y);
      			//std::cout<<score.punteggio<<" "<<score.record<<"\n";
      			
      			if (score.punteggio > score.record) {
      				score.record = score.punteggio;
      				std::ofstream ofs("record.txt");
      				ofs<<score.record;
			}
    			
			move_car(c, ene);
 		}
 		
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
        	
        	else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(ev.keyboard.keycode) {
			    case ALLEGRO_KEY_UP:
			       key[KEY_UP] = true;
			       break;

			    case ALLEGRO_KEY_DOWN:
			       key[KEY_DOWN] = true;
			       break;

			    case ALLEGRO_KEY_LEFT: 
			       key[KEY_LEFT] = true;
			       break;

			    case ALLEGRO_KEY_RIGHT:
			       key[KEY_RIGHT] = true;
			       break;
			 }
      		}
      
      		else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
		   	switch(ev.keyboard.keycode) {
			    case ALLEGRO_KEY_UP:
			       	key[KEY_UP] = false;
			       	break;

			    case ALLEGRO_KEY_DOWN:
			       	key[KEY_DOWN] = false;
			       	break;

			    case ALLEGRO_KEY_LEFT: 
			       	key[KEY_LEFT] = false;
			       	break;

			    case ALLEGRO_KEY_RIGHT:
			       	key[KEY_RIGHT] = false;
			       	break;

			    case ALLEGRO_KEY_ESCAPE:
			    	gestione_menu(display);
			    	break;
			}
		}
		
     		if(redraw && al_is_event_queue_empty(event_queue_one)) {
         		redraw = false;
 
         		al_clear_to_color(al_map_rgb(0, 0, 0));

	     		al_draw_bitmap(road, 0, road_y, 0);
	     		al_draw_bitmap(road, 0, road_y - SCREEN_H + 5, 0);
	     		
	     		srand((unsigned)time(NULL));
			index = rand() % 3;
			corsia = rand() % 4;
	     		
	     		for (int i = 0; i < num_enemies; i++) {
	     			if (i == index) {
	     				move_enemies(ene, index, corsia);
	     			}
	     			else {
	     				ene[i].y += 3.0 + speedinc;
	     			}
	     		}
	     		
	     		for (int i = 0; i < num_enemies; i++) {
	     			al_draw_bitmap(ene[i].imm, ene[i].x, ene[i].y, 0);
	     		}
	   		
	   		//al_draw_bitmap(ene[1].imm, ene[1].x, ene[1].y, 0);
			//al_draw_bitmap(ene[2].imm, ene[2].x, ene[2].y, 0);
	
			if (key[KEY_LEFT]) {
				al_draw_bitmap(c.imm[2], c.x, c.y, 0);
			}
			else if (key[KEY_RIGHT]) {
				al_draw_bitmap(c.imm[1], c.x, c.y, 0);
			}
			else {
		 		al_draw_bitmap(c.imm[0], c.x, c.y, 0);
		 	}
		 	
		 	al_draw_bitmap(scorebar, 0, SCREEN_H - 74.0, 0);
		 	
		 	al_draw_text(punteggiofont, al_map_rgb(200, 100, 0), 15, 590, 0, "Punteggio");
		 	al_draw_textf(numerofont, al_map_rgb(200, 255, 255), 180, 585, 0, "%i", score.punteggio);
		 	
    			al_draw_text(recordfont, al_map_rgb(200, 100, 0), 585, 590, 0, "Record");
    			al_draw_textf(scorefont, al_map_rgb(200, 255, 255), 700, 585, 0, "%i", score.record);
         		
         		al_flip_display();
      		}
	}
}
