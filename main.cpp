#include <stdio.h>
#include <cstdlib> 
#include <ctime>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "data.h"

using namespace std;

#define SCREEN_W 840	/**< larghezza dello schermo*/
#define SCREEN_H 650		/**< altezza dello schermo*/

int state; // automaticamente settata a 0, extern permette di non passarla alle funzioni

int main() {

    	if(!al_init()){
        	al_show_native_message_box(NULL, NULL, NULL, "Could not inizialize Allegro5", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        	return -1;
    	}

    	ALLEGRO_DISPLAY *display = al_create_display(SCREEN_W,SCREEN_H);
    	al_set_window_title(display, "Cars");
    	if(!display){
        	al_show_native_message_box(display, "Sample Title", "Display Settings", "Display not create", NULL,ALLEGRO_MESSAGEBOX_ERROR);
        	return -1;   
    	}
    
       	al_init_primitives_addon();
    	al_install_keyboard();
    	al_init_image_addon(); 
   
    	while(state >= 0){
		switch(state){
            		case 0: 
                		gestione_menu(display);
                		break;
            		/**case 1:
                		game_over(state, display);
                		break; */
        	}
    	}
    	
    	al_destroy_display(display);
    	return 0;
}

