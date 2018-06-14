/**
  * @file
  *
  * File con le funzioni degli stati del gioco.<br>
  * <b>Funzioni</b>
  * - ::replay
  * - ::gestione_menu
  * - ::break_game
  * - ::game_over
  *
  *
  * @param ::num_enemies
  * @param ::speedinc
  * @param ::road_y
  * @param ::doexit
  * @param ::redraw
  * @param ::key
  * 
  * @author Taisia Marconi e Mahmoud Marzak
  *
  */
    
#include <iostream>
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

/**
*Impostazione del debug
**/
#ifdef DEBUG_MODE
extern unsigned int mask;
#define DBG(A, B)                                                                                  \
    {                                                                                              \
        if ((A)&mask)                                                                              \
        {                                                                                          \
            B;                                                                                     \
        }                                                                                          \
    }
#else
#define DBG(A, B)
#endif
/**
*La seguente definizione non è necessaria ma è comoda in quanto consente di scrivere D1(...) al posto di DBG (2, ...).
**/
#define D1(a) DBG(2, a)

/**Variabile intera che determina il numero di auto da evitare. */
int num_enemies = 6;
/**Variabile di tipo float che gestisce l'incremento della velocità strada. */
float speedinc = 0.2; 
/**Variabile di tipo float che gestisce il movimento della strada. */
float road_y = 2.0; 

/**Booleana per l'uscita dei cicli while.*/
bool doexit = false; 
/**Booleana per l'aggiornamento dello schermo.*/
bool redraw = true;

/**Chiavi del gioco settate a false in attesa di essere attivate.*/
bool key[6] = {false, false, false, false, false, false};

/**
 * Funzione per reimpostare gli stati iniziali del gioco.
 *
 * @param c struttura che rappresenta la macchina (posizione x, posizione y, sprite)
 * @param ene struttura che rappresenta la macchina nemica (posizione x, posizione y, sprite)
 * @param score variabile del punteggio
*/
void replay(car_t &c, enemy_t *&ene, score_t &score)
{  
	D1(cout << "Reinizializzazione delle variabili di gioco....." <<endl);
	
	D1(cout << "Reinizializzazione giocatore principale...");
  	c.x = SCREEN_W / 2.0 + 22.0; /*<Posizionamento orizzontale del giocatore*/
  	c.y = SCREEN_H - CAR_H - 75.0; /*<Posizionamento verticale del giocatore*/
  
  	D1(cout << "\tReinizializzazione nemici...");
  	ene[0].x = 195; ene[0].y = - CAR_H; ene[0].imm = al_load_bitmap("media/bcar.png"); /*<Inizializzazione primo nemico*/
  	ene[1].x = 325; ene[1].y = - CAR_H; ene[1].imm = al_load_bitmap("media/gcar.png"); /*<Inizializzazione secondo nemico*/
  	ene[2].x = 455; ene[2].y = - CAR_H; ene[2].imm = al_load_bitmap("media/wwcar.png"); /*<Inizializzazione terzo nemico*/
  	ene[3].x = 530; ene[3].y = - CAR_H - SCREEN_H/2; ene[3].imm = al_load_bitmap("media/bcar.png"); /*<Inizializzazione quarto nemico*/
  	ene[4].x = 395; ene[4].y = - CAR_H - SCREEN_H/2; ene[4].imm = al_load_bitmap("media/gcar.png"); /*<Inizializzazione quinto nemico*/ 
  	ene[5].x = 260; ene[5].y = - CAR_H - SCREEN_H/2; ene[5].imm = al_load_bitmap("media/wwcar.png"); /*<Inizializzazione sesto nemico*/
  
  	D1(cout << "\tAzzeramento punteggio...");
  	score.punteggio = 0; /*<Azzeramento del punteggio*/
  	D1(cout << "\tAzzeramento velocità...");
  	speedinc = 0.2; /*<Reimpostazione dell'incremento della velocità*/
  	num_enemies = 6; /*<Reimpostazione del numero di nemici*/ 
  	road_y = 2.0; /*<Riposizionamento del background*/ 
  
  	/*<Ciclo per settare tutte le chiavi a false*/
  	for (int i = 0; i < 6; i++) {
    		key[i] = false;
  	}
  	
  	D1(cout << "Fatto!" <<endl);
  	D1(cout << "Ripresa del gioco..." <<endl);
}

/**
 * Funzione per l'apertura della schermata iniziale.
 * Vedere la documentazione della funzione ::move_game per maggiori informazioni.
 *
 * @param display
 */
void gestione_menu(ALLEGRO_DISPLAY* display)
{
	D1(cout << "Apertura schermata principale...." <<endl);
	/*<Oggetto ALLEGRO_TIMER, utilizzato per la gestione del timer, ovvero la frequenza con la quale si ripetono le azioni del gioco.*/
	D1(cout << "Creazione del timer di gioco....." <<endl);
	ALLEGRO_TIMER *timer = NULL;
    	
    	D1(cout << "Inizializzazione del timer.....");
	/*<Inizializzazione del timer*/
	timer = al_create_timer(1.0 / FPS);
	if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
	}
	D1(cout << "Fatto!" <<endl);
    
    	D1(cout << "Installazione audio....." <<endl);
	al_install_audio();
	al_init_acodec_addon();
	D1(cout << "Installazione font....." <<endl);
	al_init_font_addon();
	al_init_ttf_addon();
    
	al_reserve_samples(10);
    
    	D1(cout << "Creazione del background....." <<endl);
	ALLEGRO_BITMAP *road = NULL; /*<Oggetto ALLEGRO_BITMAP contenente l'immagine del background. */
    	
	/*<Inizializzazione del background*/
	road = al_load_bitmap("media/road.png");
	if(!road) {
		fprintf(stderr, "failed to create gestione_menu bitmap\n");
		al_destroy_display(display);
	}
  
	al_draw_bitmap(road, 0, 0, 0);

	D1(cout << "Inizializzazione messaggi di gioco.....");
	/*<Oggetto ALLEGRO_FONT, rappresentante il font utilizzato per stampare il titolo. */
	ALLEGRO_FONT *titlefont = al_load_font("media/arcade.ttf", 70, 0);
	/*<Oggetto ALLEGRO_FONT, rappresentante il font utilizzato per stampare il comando di start. */
	ALLEGRO_FONT *startfont = al_load_font("media/arcade.ttf", 40, 0);
	/*<Oggetto ALLEGRO_FONT, rappresentante il font utilizzato per stampare le istruzioni principali. */
	ALLEGRO_FONT *instructionsfont = al_load_font("media/arcade.ttf", 25, 0); 
      
	al_draw_text(titlefont, al_map_rgb(0, 0, 0), 260, 100, 0, "Maccchine");
	al_draw_text(startfont, al_map_rgb(0, 0, 0), 155, 250, 0, "Premi spazio per cominciare");
	al_draw_text(instructionsfont, al_map_rgb(0, 0, 0), 525, 585, 0, "Esc per uscire");
	al_draw_text(instructionsfont, al_map_rgb(0, 0, 0), 150, 585, 0, "Usa  le  frecce  per");
	al_draw_text(instructionsfont, al_map_rgb(0, 0, 0), 150, 600, 0, "evitare  le   auto");
	
	D1(cout << "Fatto!"<<endl);
  
  	D1(cout << "Creazione struttura del giocatore principale....." <<endl);
	car_t c; /*<Oggetto di tipo car_t(struttura) rappresentante il giocatore principale. */

	D1(cout << "Posizionamento del giocatore....." <<endl);
	c.x = SCREEN_W / 2.0 + 22.0; /*<Posizionamento orizzontale del giocatore.*/
	c.y = SCREEN_H - CAR_H - 75.0; /*<Posizionamento verticale del giocatore.*/
  
  	D1(cout << "Caricamento immagine principale...");
	ALLEGRO_BITMAP *car = NULL; /*<Oggetto ALLEGRO_BITMAP contenente l'immagine del giocatore. */
	car = al_load_bitmap("media/car.png");
      
      	D1(cout << "\tCaricamento immagine dx...");
	ALLEGRO_BITMAP *car_dx = NULL; /*<Oggetto ALLEGRO_BITMAP contenente l'immagine del giocatore in movimento a dx. */
	car_dx = al_load_bitmap("media/carR.png");
      
      	D1(cout << "\tCaricamento immagine sx...");
	ALLEGRO_BITMAP *car_sx = NULL; /*<Oggetto ALLEGRO_BITMAP contenente l'immagine del giocatore in movimento a sx. */
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
	
	D1(cout << "Fatto!" <<endl);
  
  	D1(cout << "Creazione coda degli eventi di gioco....." <<endl);
	ALLEGRO_EVENT_QUEUE *event_queue = NULL; /*<Oggetto ALLEGRO_EVENT_QUEUE, rappresentante gli eventi. */
  	
  	D1(cout << "Inizializzazione coda degli eventi di gioco....." <<endl);
	/*<Inizializzazione coda di eventi.*/
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
 
 	D1(cout << "Creazione coda degli eventi di gioco....." <<endl);
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source()); 
   
	al_flip_display();
 
 	D1(cout << "Start del timer." <<endl);
	al_start_timer(timer);
 
	/*<Ciclo per la gestione degli eventi*/
	while(!doexit) {
		ALLEGRO_EVENT ev; /*<Oggetto ALLEGRO_EVENT che identifica il tipo di evento*/
		al_wait_for_event(event_queue, &ev);
          	
		/*<Chiusura del gioco tramite pulsante x*/
		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
          	
		/*<Gestione eventi da tastiera*/
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(ev.keyboard.keycode) {
				/*<Inizio del gioco*/
				case ALLEGRO_KEY_ESCAPE:
					doexit = false;
				break;
        			
				/*<Inizializzazione uscita dal gioco*/
				case ALLEGRO_KEY_SPACE:
					key[KEY_SPACE] = true;
				break;
			}
		}       

		else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch(ev.keyboard.keycode) {
				/*<Uscita dal gioco*/
				case ALLEGRO_KEY_ESCAPE:
					doexit = true;
				break;
				
				/*<Apertura frame del gioco*/
				case ALLEGRO_KEY_SPACE:
					move_game(display, timer, event_queue, road, c);
					key[KEY_SPACE] = false;
				break;
			}
		}
	}
}

/**
 * Funzione per mettere in pausa il gioco.
 *
 * @param event_queue coda degli eventi
 * @param pausa booleana che gestisce il l'entrata e l'uscita dallo stato di pausa
 */
void break_game(ALLEGRO_EVENT_QUEUE* event_queue, bool &pausa) 
{
	D1(cout << "Gioco in pausa!");
	
	D1(cout << "Inizializzazione stato del gioco.....");
	ALLEGRO_FONT *pausafont; /*<Oggetto di tipo ALLEGRO_FONT che segnala lo stato di pausa*/
	ALLEGRO_FONT *nextfont; /*<Oggetto di tipo ALLEGRO_FONT che descrive come uscire dallo stato di pausa*/	

	pausafont = al_load_font("media/arcade.ttf", 90, 0);
	nextfont = al_load_font("media/arcade.ttf", 30, 0);

	al_draw_text(pausafont, al_map_rgb(250, 0, 0), 245, 100, 0, "PAUSA");
	al_draw_text(nextfont, al_map_rgb(250, 0, 0), 220, 200, 0, "Premi SPAZIO per riprendere");
  
	al_flip_display();
	
	D1(cout << "Fatto!" <<endl);

	/*<Ciclo per la gestione degli eventi*/
	while(!doexit) {
		ALLEGRO_EVENT ev; /*<Oggetto ALLEGRO_EVENT che identifica il tipo di evento*/
		al_wait_for_event(event_queue, &ev);
                
                /*<Chiusura del gioco tramite pulsante x*/
		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			doexit = true;
			pausa = false;
			break;
		}
          
          	/*<Gestione eventi da tastiera*/
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(ev.keyboard.keycode) {
				/*<Inizializzazione uscita dal gioco*/
				case ALLEGRO_KEY_ESCAPE: {
					doexit = false;
				} break;
				/*<Inizializzazione ripresa del gioco*/
				case ALLEGRO_KEY_SPACE: {
					key[KEY_SPACE] = true;
				} break;
			}
		}    

		else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch(ev.keyboard.keycode) {
				/*<Uscita dal gioco*/
				case ALLEGRO_KEY_ESCAPE: {
					pausa = false;
					doexit = true;
				} break;
				/*<Uscita stato di pausa*/
				case ALLEGRO_KEY_SPACE: {
					al_destroy_font(pausafont);
					al_destroy_font(nextfont);
					pausa = false;
				} return;
			}
		}
	}
}

/**
 * Funzione per il gameover.
 *
 * @param event_queue coda degli eventi
 * @param c struttura che rappresenta la macchina (posizione x, posizione y, sprite)
 * @param ene struttura che rappresenta la macchina nemica (posizione x, posizione y, sprite)
 * @param collisione booleana che gestisce lo stato della collisione
 * @param boom oggetto BITMAP che disegna la collisione
 */
void game_over(ALLEGRO_EVENT_QUEUE *event_queue, car_t &c, enemy_t *&ene, score_t &score, bool &collisione, ALLEGRO_BITMAP *boom) 
{
	D1(cout <<"Game over! Inizializzazione dello stato di gioco.....");
  	//cout<<"Collisione"<<endl;
	ALLEGRO_FONT *gameoverfont; /*<Oggetto di tipo ALLEGRO_FONT che segnala lo stato di gameover*/
	ALLEGRO_FONT *nextgamefont; /*<Oggetto di tipo ALLEGRO_FONT che indica le istruzioni successive al gameover*/

	gameoverfont = al_load_font("media/arcade.ttf", 90, 0);
	nextgamefont = al_load_font("media/arcade.ttf", 30, 0);

	al_draw_text(gameoverfont, al_map_rgb(250, 0, 0), 225, 100, 0, "GAME OVER");
	al_draw_text(nextgamefont, al_map_rgb(250, 0, 0), 220, 200, 0, "Premi SPAZIO per ricominciare");
	al_draw_text(nextgamefont, al_map_rgb(250, 0, 0), 265, 235, 0, "Premi ESC per uscire");
      
	al_flip_display();

	D1(cout << "Fatto!" <<endl);
	/*<Ciclo per la gestione degli eventi*/
	while(!doexit) {
          	ALLEGRO_EVENT ev; /*<Oggetto ALLEGRO_EVENT che identifica il tipo di evento*/
		al_wait_for_event(event_queue, &ev);
                 
		/*<Chiusura del gioco tramite pulsante x*/
		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			doexit = true;
			collisione = false;
			break;
		}
          	
		/*<Gestione eventi da tastiera*/
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(ev.keyboard.keycode) {
				/*<Inizializzazione uscita dal gioco*/
				case ALLEGRO_KEY_ESCAPE: {
					doexit = false;
				} break;
        			
				/*<Inizializzazione restart del gioco*/
				case ALLEGRO_KEY_SPACE: {
					key[KEY_SPACE] = true;
				} break;
			}
		}    

		else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch(ev.keyboard.keycode) {
				/*<Uscita dal gioco*/
				case ALLEGRO_KEY_ESCAPE: {
					collisione = false;
					doexit = true;
				} break;
                
				/*<Restart del gioco*/
				case ALLEGRO_KEY_SPACE: {
					al_draw_bitmap(boom, -200, -200, 0);
					al_destroy_font(gameoverfont);
					al_destroy_font(nextgamefont);
					collisione = false;
					/*<Ripristino stato iniziale*/
					replay(c, ene, score);
				} return;
			}
		}
	} 
}
