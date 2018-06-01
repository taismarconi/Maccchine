const char nome_file[12] = "record.txt";
const float FPS = 60;

#define SCREEN_W 840 /*<Larghezza del display. */
#define SCREEN_H 650 /*<Altezza del display. */
#define CAR_H 111
#define CAR_W 76
#define CAR_E 58
#define EXPLOSION_SIZE 128
#define SCOREBAR_SIZE 75

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
