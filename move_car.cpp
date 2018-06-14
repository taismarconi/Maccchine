/**
 *	@file
 *	
 *	File che contiene la gestione del movimento della macchina
 *	e l'eventuale collisione (che è causato dal movimento).
 *
 *	@param ::num_enemies
 *	@param ::redraw
 *	@param ::speed
 *	@param ::key
 *
 *	@author Taisia Marconi e Mahmoud Marzak
 *
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
*La seguente definizione non è necessaria ma è comoda in quanto consente di scrivere D2(...) al posto di DBG (2, ...).
**/
#define D2(a) DBG(4, a)

using namespace std;

/*<Definizione di variabili esterne*/
extern int num_enemies;
extern bool redraw;
extern float speed;
extern bool key[6];

/**
 *	Questa funzione serve alla gestione del movimento
 *	della macchina con le frecce.
 *	@param c struttura che rappresenta la macchina (posizione x, posizione y, sprite)
 *	@param ene struttura che rappresenta la macchina nemica (posizione x, posizione y, sprite)
 *
 */
void move_car(car_t &c, enemy_t *&ene) 
{
	/*<Ad ogni tasto premuto corrisponde un movimento (su, giù, dx, sx)
	 *dove ci sono numeri sono accorgimenti di posizione
	 *per evitare di uscire dai bordi */
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
/**
 *	Questa funzione controlla che ci sia una collisione provocata
 *	dal movimento della macchina.
 *	
 *	@param c struttura che rappresenta la macchina (posizione x, posizione y, sprite)
 *	@param ene struttura che rappresenta la macchina nemica (posizione x, posizione y, sprite)
 *	@param collisione vero se avviene una collisione, falso altrimenti
 *	@param boom sprite di uno scoppio che appare in caso di collisione
 *	
 */
void check_collisione(car_t &c, enemy_t *&ene, bool &collisione, ALLEGRO_BITMAP *boom) 
{
	for (int i = 0; i < num_enemies; i++) {
		/*<Qui in è un controllo perimetrale intorno all'auto nemica, se supero un limite si causa la collisione*/
		if (c.x > ene[i].x - CAR_W + 13 && c.x < ene[i].x + CAR_E - 15) {
			if (c.y < ene[i].y + CAR_H - 10 && c.y > ene[i].y - CAR_H + 10) {
				D2(cout << "Collisione!" <<endl);
				collisione = true;
				
				/*<Controllo per per evitare di far apparire l'esplosione sopra alla barra della collsione.*/
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
