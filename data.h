const char nome_file[12] = "record.txt";
const float FPS = 60;

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
