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

int num_enemies = 6;
float speedinc = 0.2;
float road_y = 2.0;

bool doexit = false;
bool redraw = true;

enum MYKEYS {
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE, KEY_ESCAPE
};

bool key[6] = { false, false, false, false, false, false};

const float FPS = 60;

void replay(car_t &c, enemy_t *&ene, score_t &score) {
	
	c.x = SCREEN_W / 2.0 + 22.0;
	c.y = SCREEN_H - CAR_H - 75.0;
	
	ene[0].x = 195; ene[0].y = - CAR_H; ene[0].imm = al_load_bitmap("media/bcar.png");
	ene[1].x = 325; ene[1].y = - CAR_H; ene[1].imm = al_load_bitmap("media/gcar.png");
	ene[2].x = 455; ene[2].y = - CAR_H; ene[2].imm = al_load_bitmap("media/wwcar.png");
	
	ene[3].x = 530; ene[3].y = - CAR_H - SCREEN_H/2; ene[3].imm = al_load_bitmap("media/bcar.png");
	ene[4].x = 395; ene[4].y = - CAR_H - SCREEN_H/2; ene[4].imm = al_load_bitmap("media/gcar.png");
	ene[5].x = 260; ene[5].y = - CAR_H - SCREEN_H/2; ene[5].imm = al_load_bitmap("media/wwcar.png");
	
	score.punteggio = 0;
	
	speedinc = 0.2;
	num_enemies = 6;
	road_y = 2.0;
	
	for (int i = 0; i < 6; i++) {
		key[i] = false;
	}
}

void gestione_menu(ALLEGRO_DISPLAY* display){
    	
   	ALLEGRO_TIMER *timer = NULL;
	timer = al_create_timer(1.0 / FPS);
   	if(!timer) {
      		fprintf(stderr, "failed to create timer!\n");
   	}
   	
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
	
    	al_draw_bitmap(road, 0, 0, 0);
    	
    	ALLEGRO_FONT *titlefont = al_load_font("media/arcade.ttf", 70, 0);
    	ALLEGRO_FONT *startfont = al_load_font("media/arcade.ttf", 40, 0);
    	ALLEGRO_FONT *instructionsfont = al_load_font("media/arcade.ttf", 25, 0);
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
	
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    	event_queue = al_create_event_queue();
   	if(!event_queue) {
      		fprintf(stderr, "failed to create event_queue!\n");
      		
      		for (int i = 0; i < 3; i++) {
      			al_destroy_bitmap(c.imm[i]);
      		}
      		
      		al_destroy_bitmap(road);
      		al_destroy_display(display);
      		al_destroy_timer(timer);
   	}
 
   	al_register_event_source(event_queue, al_get_display_event_source(display));
   	al_register_event_source(event_queue, al_get_timer_event_source(timer));
   	al_register_event_source(event_queue, al_get_keyboard_event_source()); 
   
   	al_flip_display();
 
   	al_start_timer(timer);
 
   	while(!doexit) {
      		ALLEGRO_EVENT ev;
      		al_wait_for_event(event_queue, &ev);
      		
		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         		break;
      		}
      		
      		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
         		switch(ev.keyboard.keycode) {
         			case ALLEGRO_KEY_ESCAPE:
				       	doexit = false;
				       	break;
				case ALLEGRO_KEY_SPACE:
				       	key[KEY_SPACE] = true;
				       	break;
			 }
		}       

      		else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
			 switch(ev.keyboard.keycode) {
			    	case ALLEGRO_KEY_ESCAPE:
         				//state = -1;
			    		doexit = true;
			       		break;

			    	case ALLEGRO_KEY_SPACE:
         				moveroad(display, timer, event_queue, road, c);
			        	key[KEY_SPACE] = false;
			        	break;
			 }
      		}
   	}
}

void break_game(ALLEGRO_EVENT_QUEUE* event_queue, bool &pausa) {

	ALLEGRO_FONT *pausafont;
    	ALLEGRO_FONT *nextfont;

    	pausafont = al_load_font("media/arcade.ttf", 90, 0);
    	nextfont = al_load_font("media/arcade.ttf", 30, 0);

	al_draw_text(pausafont, al_map_rgb(250, 0, 0), 245, 100, 0, "PAUSA");
	al_draw_text(nextfont, al_map_rgb(250, 0, 0), 220, 200, 0, "Premi SPAZIO per riprendere");
	
	al_flip_display();

	while(!doexit) {
      		ALLEGRO_EVENT ev;
      		al_wait_for_event(event_queue, &ev);
      		       
                if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         		doexit = true;
         		pausa = false;
         		break;
      		}
      		
      		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
         		switch(ev.keyboard.keycode) {
         			case ALLEGRO_KEY_ESCAPE: {
				       	doexit = false;
				} break;
				
				case ALLEGRO_KEY_SPACE: {
					key[KEY_SPACE] = true;
				} break;
			}
		}	   

      		else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
			 switch(ev.keyboard.keycode) {
			 	case ALLEGRO_KEY_ESCAPE: {
			 		pausa = false;
			    		doexit = true;
			    	} break;
			       		
			 	case ALLEGRO_KEY_SPACE: {
			        	al_destroy_font(pausafont);
                                	al_destroy_font(nextfont);
                                	pausa = false;
			       	} return;
			 }
		}
      	}	
	
}

void game_over(ALLEGRO_EVENT_QUEUE *event_queue, car_t &c, enemy_t *&ene, bool &collisione) {

	cout<<"Collisione"<<endl;
	
	ALLEGRO_FONT *gameoverfont;
    	ALLEGRO_FONT *nextgamefont;

    	gameoverfont = al_load_font("media/arcade.ttf", 90, 0);
    	nextgamefont = al_load_font("media/arcade.ttf", 30, 0);

	al_draw_text(gameoverfont, al_map_rgb(250, 0, 0), 225, 100, 0, "GAME OVER");
	al_draw_text(nextgamefont, al_map_rgb(250, 0, 0), 220, 200, 0, "Premi SPAZIO per ricominciare");
    	al_draw_text(nextgamefont, al_map_rgb(250, 0, 0), 265, 235, 0, "Premi ESC per uscire");
    	
	al_flip_display();

	while(!doexit) {
      		ALLEGRO_EVENT ev;
      		al_wait_for_event(event_queue, &ev);
      		       
                if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         		doexit = true;
         		collisione = false;
         		break;
      		}
      		
      		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
         		switch(ev.keyboard.keycode) {
         			case ALLEGRO_KEY_ESCAPE: {
				       	doexit = false;
				} break;
				
				case ALLEGRO_KEY_SPACE: {
					key[KEY_SPACE] = true;
				} break;
			}
		}	   

      		else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
			 switch(ev.keyboard.keycode) {
			 	case ALLEGRO_KEY_ESCAPE: {
			 		collisione = false;
			    		doexit = true;
			    	} break;
			       		
			 	case ALLEGRO_KEY_SPACE: {
			        	al_destroy_font(gameoverfont);
                                	al_destroy_font(nextgamefont);
                                	collisione = false;
			       	} return;
			 }
		}
      	}	
}
