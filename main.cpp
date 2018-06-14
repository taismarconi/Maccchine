/**
  * @mainpage Benvenuto nella documentazione di Maccchine \n
  * Maccchine è un semplice endless ispirato a giochi dello stesso
  * genere. \n
  * La musica e le immagini sono tutte proveniente dal web da fonti
  * free-to-use e quindi non soggetti a copyright.\n
  *
  *
  * <b>Istruzioni di gioco:</b>\n
  * Il gioco è esclusivamente giocabile in singolo giocatore.
  * \nLo scopo è arrivare il più lontano possibile evitando le macchine
  * provenienti frontalmente.\n
  * La macchina è controllabile con le quattro frecce direzionali ed 
  * è possibile mettere in pausa il gioco. 
  * \nIl gameover può essere causato da:
  * <ul>
    <li>Andare contro ad una o più macchine "nemiche"</li>
  * </ul>
  * 
  * 
  * \n<b>Divisione in moduli:</b>\n
  * <ul>
    <li><b>function.h</b>: modulo dedicato alle funzioni della gestione di gioco.</li>
    <li><b>data.h</b>: modulo dedicato alle strutture e alle variabili costanti.</li>
  * </ul>
  * 
  *
  * <b>Per iniziare la navigazione, andare su <li>main.cpp</li>.</b>
  * 
  * <h4>Link alle pagine dei file:</h4>
  * • <li>main.cpp</li><br>
  * • <li>start_finish.cpp</li><br>
  * • <li>game_core.cpp</li><br>
  * • <li>move_road.cpp</li><br>
  * • <li>move_road.cpp</li><br>
  * • <li>enemies.cpp</li><br>
  * • <li>data.h</li><br>
  * • <li>function.h</li><br>
  *
  *
  * <b>N.B. PROBLEMI DI COMPILAZIONE</b>
  * Per la creazione dell'eseguibile è stato creato l'apposito makefile nella
  * directory principale.
  * In caso di problemi, in alternativa, entrare nella Directory contenente i file del
  * gioco e compilarlo mediante il comando sottostante:\n
  * g++ -Wall -o maccchine main.cpp start_finish.cpp move_road.cpp 
  * move_car.cpp game_core.cpp enemies.cpp `pkg-config --cflags --libs
  * allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0
  * allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0
  * allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 
  * allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0`\n\n
  *
  * Nel caso si utilizzasse Ubuntu e desse problemi di compilazione,
  * utilizzare la stessa riga per compilare ma togliendo il '.0'
  * nella versione di allegro.
  */

  /**
   * @file
   *
   * File da cui inizia l'esecuzione del programma.<br>
   * <b>Funzioni</b>
   * - ::main
   *
   * @author Taisia Marconi e Mahmoud Marzak
   *
   */
  
#include <iostream>
#include <cstdlib> 
#include <ctime>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "data.h"
#include "function.h"

using namespace std;

/**
*Impostazione del debug
**/
#ifdef DEBUG_MODE
unsigned int mask = 7;
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
*La seguente definizione non è necessaria ma è comoda in quanto consente di scrivere D1(...) al posto di DBG (1, ...).
**/
#define D1(a) DBG(1, a)

/**
 * 	Funzione principale\n
 * 	Il richiamo alla funzione gestione_menu permette la creazione 
 * 	degli oggetti principali e iniziare il gioco. 
 *	Vedere la documentazione della funzione ::gestione_menu per
 *	maggiori informazioni.
 */
int main(int argc, char** argv)
{
	D1(cout << "Inizializzazione interfaccia grafica.....");
	/*< Inizializzazione di Allegro.*/
	if(!al_init()){
    	al_show_native_message_box(NULL, NULL, NULL, "Could not inizialize Allegro5", NULL, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}
	D1(cout << "Fatto!" <<endl);

	D1(cout << "Creazione display.....");
	ALLEGRO_DISPLAY *display = al_create_display(SCREEN_W, SCREEN_H); /*<Oggetto ALLEGRO_DISPLAY, rappresentante il "display". */
	al_set_window_title(display, "Cars");
	D1(cout << "Fatto!" <<endl);
	
	D1(cout << "Inizializzazione display.....");
	/*<Inizializzazione display.*/
	if(!display){
    	al_show_native_message_box(display, "Sample Title", "Display Settings", "Display not create", NULL,ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;   
	}
	D1(cout << "Fatto!" <<endl);

	D1(cout << "Inizializzazione addon.....");
   	al_init_primitives_addon(); /*<Inizializzazione addon principali. */
   	D1(cout << "\tInizializzazione tastiera.....");
	al_install_keyboard(); /*<Inizializzazione input per l'interazione col gioco. */
	al_init_image_addon(); /*<Inizializzazione addon immagini. */
	D1(cout << "Fatto!" <<endl);
	
	gestione_menu(display);/*<Apertura della pagina principale del gioco. */

	D1(cout << "Uscita dal gioco.....");
	al_destroy_display(display);
	D1(cout << "Fatto!" << endl);
	
	return 0;
}
