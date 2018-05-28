
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

/**Prototipi delle funzioni del gioco*/
void replay(car_t&, enemy_t*&, score_t&);
void gestione_menu(ALLEGRO_DISPLAY*);
void moveroad(ALLEGRO_DISPLAY*, ALLEGRO_TIMER*, ALLEGRO_EVENT_QUEUE*, ALLEGRO_BITMAP*, car_t&);
void break_game(ALLEGRO_EVENT_QUEUE*, bool&);
void game_over(ALLEGRO_EVENT_QUEUE*, car_t&, enemy_t*&, bool&, ALLEGRO_BITMAP*);
int moveit(float&);
void move_car(car_t&, enemy_t*&);
void check_collisione(car_t&, enemy_t*&, bool&, ALLEGRO_BITMAP*);
void move_enemies(enemy_t*&, int, int&);
