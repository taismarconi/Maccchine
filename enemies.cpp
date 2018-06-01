/**
 *	@file
 *	
 *	File che contiene la gestione del posizionamento dei nemici.
 *
 *	@param ::redraw
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

extern bool redraw;

/**
 * Funzione per il posizionamento di un determinato nemico in una determinata corsia
 *
 * @param ene struttura che rappresenta la macchina nemica (posizione x, posizione y, sprite)
 */
void move_enemies(enemy_t *&ene, int index, int &corsia) {
	
	/*<La variabile index determina quale dei 6 nemici deve essere posizionato.
	 *Se è compreso fra 0 e 2 l'auto è generata nella prima fila, altrimenti nella seconda.
	 *La variabile corsia determina in quale posizione l'auto deve essere generata*/
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
