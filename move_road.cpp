/**
 *	@file
 *
 *	Questo file si occupa del movimento della strada.
 *	Il funzionmento è semplice: inizialmente vengono generate due
 *	sprite che rappresentano la strada, uno in modo da essere visibile
 *	nel display e l'altro con coordinata y = all'altezza della strada.
 *	Queste inizieranno a scorrere insieme.
 *	Anche il punteggio è gestito in questo file in quanto è direttamente
 *	in relazione con la strada che scorre.
 *
 *	@param ::mov
 *	@param ::speedinc
 *	@param ::num_enemies
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

/**Velocità iniziale della strada.*/
float mov = 2.0;

/*<Definizione di variabili esterne*/
extern float speedinc;
extern int num_enemies;

/**
 * 	Ad inizio partita iniziano a scorrere entrambe verso il basso fino
 *	a quando il pezzo di strada che non era visibile inizialmente è
 *	completamente visibile, a quel punto la strada tornerà al punto
 *	iniziale (quindi a y = 0) e ricomincia lo scorrere della strada.
 * 	Questa funzione gestisce questo processo.
 *	Restituisce un intero che mi servirà per il calcolo del punteggio.
 *	@param ::road_y posizione sulle ordinate della strada che scorre
 *	in verticale
 *	@return int un valore intero che sarà sommato in una variabile
 *	incrementale per il punteggio
 *
 */
int move_road(float &road_y)
{
	/*<Range entro il quale si torna al punto iniziale*/
	if(road_y > SCREEN_H - 10 && road_y < SCREEN_H + 10) {
		road_y = 0;
		
		/*<Quando si riporta la strada al punto iniziale
    		 *significa che abbiamo fatto un "giro" quindi 
    		 *incremento la velocità di scorrimento */
    		speedinc += 0.2;
    		/*<Quando si riporta la strada al punto iniziale
    		*significa che abbiamo fatto un "giro" quindi abbiamo fatto
    		100 punti che andranno a sommarsi a quelli raccolti prima */
    		return 100;
	}
        /*<Muovo la strada della velocità iniziale + l'inc di velocità*/
    	road_y += mov + speedinc;
    	/*<Restituisco 0 perchè qui non siamo nel caso di "giro completo"*/
    	return 0;
}
