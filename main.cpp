/**
  *<img src="/home/taismarconi/Scrivania/Programmazione 2/prog2/media">
  *@mainpage BENVENUTO
  *@brief
  *MACCCHINE è un gioco sviluppato con Allegro 5.<br>
  *L'idea di base è un semplice gioco di intrattenimento dai comandi semplici ed immediati.
  *Di seguito troverete il codice commentato e le varie spiegazioni per il suo funzionamento.
  *Buona lettura!
  *@author Mahmoud Marzak & Taisia Marconi
  *
  *<h4>Link alle pagine dei file:</h4>
  * • main.cpp<br>
  * • init.cpp<br>
  * • road.cpp<br>
  * • prova.cpp<br>
  * • mov.cpp<br>
  * • nemici.cpp<br>
  * • data.h<br>
  *
  *Portabilità: non su diverse architetture<br>
  *Tipo eseguibile: Dinamico<br>
  *Numero file: 7<br>
  *Debugging: -Wall & Tracing<br>
  *Pagina principale: main.cpp<br>
  *
  *<h2>Comandi</h2>
  *Il movimento del giocatore dipende dalle 4 frecce direzionali.<br>
  *Il comando SPAZIO permette nei vari stadi del gioco di iniziare, mettere in pausa e ricominciare.<br>
  *L'uscita è effettuata tramite l'ESC oppure usando la semplice X della finestra di gioco.
  *
  *<h2>Istruzioni</h2>
  *Il gioco presenta una schermata iniziale con una sintetica spiegazione del funzionamento.<br>
  *Allo start il giocatore dovrà evitare di collidere con le auto "nemiche", che si generano
  *casualmente su due file principali, e su 4 corsie.<br>
  *Più il giocatore sarà bravo, più la velocità aumenterà e il livello di difficoltà si alzerà.<br>
  *In caso di collisione il giocatore potrà scegliere se uscire o ricominciare.<br>
  *Il punteggio è calcolato automaticamente con l'avanzamento del gioco.<br>
  *
  *<h2> Come compilarlo</h2>
  *Per la creazione dell'eseguibile è stato creato l'apposito Makefile nella directory principale.<br>
  *In caso di problemi, in alternativa, entrare nella Directory contenente i file del gioco
  *e compilarlo mediante il comando sottostante:<br>
  *g++ -Wall  -o cars main.cpp init.cpp road.cpp prova.cpp mov.cpp nemici.cpp `pkg-config --cflags --libs allegro-5.0 allegro_acodec-5.0  
  *allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 	
  *allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0`
  */
  
#include <stdio.h>
#include <cstdlib> 
#include <ctime>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "data.h"
#include "function.h"

using namespace std;

/**Funzione principale.
 * Il richiamo alla funzione "gestione_menu" permette la creazione 
 * degli oggetti principali e l'inizio del gioco.
 */
 
int main(int argc, char** argv) {

	/** 
	 * Inizializzazione interfaccia grafica.
	 */
    	if(!al_init()){
        	al_show_native_message_box(NULL, NULL, NULL, "Could not inizialize Allegro5", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        	return -1;
    	}

	/** 
	 * Creazione del display.
	 */
    	ALLEGRO_DISPLAY *display = al_create_display(SCREEN_W, SCREEN_H); /*<Oggetto ALLEGRO_DISPLAY, rappresentante il "display". */
    	al_set_window_title(display, "Cars");
    	
    	/**
    	 * Controllo della creazione del display: se riscontra problemi il programma viene chiuso.
    	 */
    	if(!display){
        	al_show_native_message_box(display, "Sample Title", "Display Settings", "Display not create", NULL,ALLEGRO_MESSAGEBOX_ERROR);
        	return -1;   
    	}
    
       	al_init_primitives_addon(); /*<Inizializzazione addon principali. */
    	al_install_keyboard(); /*<Inizializzazione input per l'interazione col gioco. */
    	al_init_image_addon(); /*<Inizializzazione addon immagini. */
   
	gestione_menu(display); /*<Apertura della pagina principale del gioco. */

	/**
	 * Distruzione del display e uscita dal gioco.
	 */
    	al_destroy_display(display);
    	
    	return 0;
}

