/**
 * @file
 *	
 * Header dedicato alla dichiarazione
 * delle costanti utilizzate dal programma.
 *
 */

/**Nome file in cui è salvato il record*/
const char nome_file[12] = "record.txt";
/**Costante per gestire i Frame Per Secondo*/
const float FPS = 60;

/**Larghezza del display.*/
#define SCREEN_W 840
/**Altezza del display.*/		
#define SCREEN_H 650
/**Altezza macchina.*/
#define CAR_H 111
/**Larghezza macchina.*/
#define CAR_W 76
/**Larghezza macchina nemici*/
#define CAR_E 58
/**Grandezza esplosione.*/
#define EXPLOSION_SIZE 128
/**Grandezza barra punteggio.*/
#define SCOREBAR_SIZE 75

/**Enumerato necessario per i tasti premuti*/
enum MYKEYS 
{
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE, KEY_ESCAPE
};

/**Struttura per la creazione dei nemici*/
struct enemy_t {
	/**Movimento in orizzontale*/
	float x;
	/**Movimento in verticale*/
	float y;
	/**Immagine del nemico*/
	ALLEGRO_BITMAP *imm;
};

/**Struttura per la creazione della macchina principale*/
struct car_t {
	/**Movimento in orizzontale*/
	float x;
	/**Movimento in verticale*/
	float y;
	/**Immagine del nemico*/
	ALLEGRO_BITMAP *imm[3];
};

/**Struttura per la gestione del punteggio*/
struct score_t {
	/**Variabile che memorizza il punteggio corrente*/
	int punteggio;
	/**Variabile per la memorizzazione del record*/
	int record;
};
