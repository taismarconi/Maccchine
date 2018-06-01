/**
 *	@file
 *	Questo file è dove convergono tutte le funzionalità del gioco e vengono mosse.
 *      
 *	<b>Funzioni</b>
 * 	- ::move_game
 * 	
 *	@param ::speed
 *	@param ::num_enemies
 *	@param ::speedinc
 *	@param ::road_y
 *	@param ::doexit
 *	@param ::redraw
 *	@param ::key
 */

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

/**Velocità del giocatore*/
float speed = 6.0;

extern int num_enemies;
extern float speedinc, road_y;

extern bool doexit;
extern bool redraw;
extern bool key[6];

/**
 *	Questa funzione gestisce la parte viva del gioco, chiama tutte le 
 *	funzioni e usa controlli per la gestione delle situazioni.
 *
 *	@param display dove viene visualizzato il gioco
 *	@param timer evento ciclico
 *	@param event_queue lo stack degli eventi
 *	@param road l'immagine della strada che scorre
 *	@param c struttura che rappresenta la macchina (pos. x, pos. y, immagini)
 */
void move_game(ALLEGRO_DISPLAY* display, ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_BITMAP* road, car_t &c) {
	
	/*<Variabile per controllare la velocità, una volta superata la soglia
	prestabilita (speedinc > 3.5) viene settata a false in modo da non entrare più nell'if*/
	bool controllo = true;
	
	/*<Variabile per controllare se c'è o meno una collisione*/
	bool collisione = false;
	
	/*<Variabile per gestire l'entrare e l'uscita dallo stato di pausa*/
	bool pausa = false;
	
	/*<Variabili per la generazione di numeri casuali:
	 * index_1 numero da 0 a 2
	 * index_2 numero da 3 a 5
	 * corsia numero da 0 a 7
	 */
	int index_1, index_2, corsia;
	
	/*<Inizializzo le altre struct*/
	enemy_t *ene;
	ene = new enemy_t [num_enemies];
	
	score_t score;
	
	/*<Inizializzo i nemici*/
	ene[0].x = 195; ene[0].y = - CAR_H; ene[0].imm = al_load_bitmap("media/bcar.png");
	ene[1].x = 325; ene[1].y = - CAR_H; ene[1].imm = al_load_bitmap("media/gcar.png");
	ene[2].x = 455; ene[2].y = - CAR_H; ene[2].imm = al_load_bitmap("media/wwcar.png");
	
	ene[3].x = 530; ene[3].y = - CAR_H - SCREEN_H/2; ene[3].imm = al_load_bitmap("media/bcar.png");
	ene[4].x = 395; ene[4].y = - CAR_H - SCREEN_H/2; ene[4].imm = al_load_bitmap("media/gcar.png");
	ene[5].x = 260; ene[5].y = - CAR_H - SCREEN_H/2; ene[5].imm = al_load_bitmap("media/wwcar.png");
	
	/*<Set del punteggio*/
	score.punteggio = 0;
	/*<Scrittura su file*/
	std::ifstream ifs("record.txt");
	ifs>>score.record;
	
	/*<Oggetto di tipo ALLEGRO_BITMAP che disegna la barra per la visualizzazione del punteggio e del record*/
	ALLEGRO_BITMAP *scorebar = NULL;
    	scorebar = al_load_bitmap("media/score-bar.png");
    	
    	ALLEGRO_SAMPLE *playsong = NULL;
    	ALLEGRO_SAMPLE *crash = NULL;

    	if(!al_install_audio()){
    		cout << "cannot start audio\n";
    	}

    	playsong = al_load_sample("media/arcade.wav");
    	al_play_sample(playsong, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

    	crash = al_load_sample("media/crash.wav");
    	
    	/*<Oggetto di tipo ALLEGRO_BITMAP che disegna l'esplosione nella collisione*/
    	ALLEGRO_BITMAP *boom = NULL;
    	boom = al_load_bitmap("media/boom.png");
    
    	/*<Font che scrivono il punteggio e il record*/
    	ALLEGRO_FONT *punteggiofont;
    	ALLEGRO_FONT *numerofont;
    	ALLEGRO_FONT *recordfont;
    	ALLEGRO_FONT *scorefont;
    	
    	/*<Font che spiega come impostare la pausa*/
    	ALLEGRO_FONT *pausafont;
    	pausafont = al_load_font("media/arcade.ttf", 20, 0);
    			
	punteggiofont = al_load_font("media/arcade.ttf", 30, 0);
	numerofont = al_load_font("media/arcade.ttf", 40, 0);
	recordfont = al_load_font("media/arcade.ttf", 30, 0);
	scorefont = al_load_font("media/arcade.ttf", 40, 0);
 
   	al_flip_display();

	/*<Ciclo per la gestione degli eventi*/
   	while(!doexit) {
      		ALLEGRO_EVENT ev; /*<Oggetto ALLEGRO_EVENT che identifica il tipo di evento*/
      		al_wait_for_event(event_queue, &ev);
		
      		if(ev.type == ALLEGRO_EVENT_TIMER) {
			
			/*<Conteggio dei punti*/
      			score.punteggio += move_road(road_y);
      			
      			/*Controllo per verificare se si è effettuato un record*/
      			if (score.punteggio > score.record) {
      				score.record = score.punteggio;
      				/*<Scrittura su file*/
      				std::ofstream ofs("record.txt");
      				ofs<<score.record;
			}
			
			/*<Movimento del giocatore*/
			move_car(c, ene);
			
			collisione = false;
			
			/*<Controllo delle collisioni*/
			check_collisione(c, ene, collisione, boom);
			
			/*<Se si verifica una collisione, la booleana viene settata a true e viene riprodotto il suono dell'esplosione*/
			if (collisione) {
				al_play_sample(crash, 3.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
			
			/*<Finchè la collisione è vera lo stato del gioco è sul gameover,
			 *da cui si può uscire tramite due opzioni (spazio per ricominciare, esc per uscire)*/	
			while(collisione){
				/*<Stato del gameover*/
				game_over(event_queue, c, ene, collisione, boom);
				/*<Ripristino stato iniziale*/
				replay(c, ene, score);
 			}
 		}
 		
 		/*<Chiusura del gioco tramite pulsante x*/
 		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         		doexit = true;
         		break;
      		}
      		
      		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
         		switch(ev.keyboard.keycode) {
         			case ALLEGRO_KEY_ESCAPE:
			       		doexit = false;
			       		break;
         			
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
			       		
			       	case ALLEGRO_KEY_SPACE:
			       		key[KEY_SPACE] = true;
			       		break;	
			 }   
		}       

      		else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
			 switch(ev.keyboard.keycode) {
			 	case ALLEGRO_KEY_ESCAPE:
			       		doexit = true;
			       		break;
			       		
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
				
				case ALLEGRO_KEY_SPACE:
					pausa = true;
					while (pausa) {
						break_game(event_queue, pausa);
					}
					
			       		key[KEY_SPACE] = false;
			       		break;       	
			 }
		}	 
		
     		if(redraw && al_is_event_queue_empty(event_queue)) {	
     			
     			srand((unsigned)time(NULL));
			index_1 = rand() % 3;
			index_2 = rand() % 3 + 3;
			corsia = rand() % 7;
        
         		al_clear_to_color(al_map_rgb(0, 0, 0));

	     		al_draw_bitmap(road, 0, road_y, 0);
	     		al_draw_bitmap(road, 0, road_y - SCREEN_H + 5, 0);
			
			/*<Posizionamento dei nemici su due file diverse; le corsie sulla quale vengono generati
			* è gestito casualmente dalla variabile "corsia", quale macchina viene generata dagli
			* indici index_1 e index_2 */
			for (int i = 0; i < num_enemies; i++) {
				if (ene[i].y > SCREEN_H - 10 && ene[i].y < SCREEN_H + 10) {
					ene[i].y = - CAR_H;
					
					/*<Si generano due diversi numeri casuali per gestire separatamente le due file,
					in base a quale fila sto considerando uno dei due verrà passato alla funzione*/
					if (i < 3) {
						move_enemies(ene, index_1, corsia);
					}
					else {
						move_enemies(ene, index_2, corsia);
					}
				}
				
				ene[i].y += 3.0 + speedinc;
	   		}
	   		
	   		/*<Controllo della velocità, una volta superata 
			una soglia il numero di nemici si abbassa a 3*/
			if (speedinc > 3.5 && controllo && ene[index_2].y > SCREEN_H - CAR_H) {
				num_enemies = 3;
				controllo = false;
			}	
			
			/*<Disegno dei nemici sulla strada*/
			for (int i = 0; i < num_enemies; i++) {
	   			al_draw_bitmap(ene[i].imm, ene[i].x, ene[i].y, 0);
	   		}
	   		
			if (key[KEY_LEFT]) {
				al_draw_bitmap(c.imm[2], c.x, c.y, 0);
			}
			else if (key[KEY_RIGHT]) {
				al_draw_bitmap(c.imm[1], c.x, c.y, 0);
			}
			else {
		 		al_draw_bitmap(c.imm[0], c.x, c.y, 0);
		 	}
		 	
		 	/*<Disegno barra del punteggio*/
		 	al_draw_bitmap(scorebar, 0, SCREEN_H - 74.0, 0);
		 	
		 	/*<Disegno del contenuto della barra del punteggio*/
		 	al_draw_text(punteggiofont, al_map_rgb(200, 100, 0), 15, 590, 0, "Punteggio");
		 	al_draw_textf(numerofont, al_map_rgb(200, 255, 255), 180, 585, 0, "%i", score.punteggio);
    			al_draw_text(recordfont, al_map_rgb(200, 100, 0), 585, 590, 0, "Record");
    			al_draw_textf(scorefont, al_map_rgb(200, 255, 255), 700, 585, 0, "%i", score.record);
    			al_draw_text(pausafont, al_map_rgb(200, 230, 100), 15, 625, 0, "premere SPAZIO per mettere in pausa");
         		
         		al_flip_display();
      		}
	}
}
