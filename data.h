
struct enemy_t {
	float x;
	float y;
	ALLEGRO_BITMAP *imm;
};

struct car_t {
	float x;
	float y;
	ALLEGRO_BITMAP *imm[3];	
};

struct score_t {
	int punteggio;
	int record;
	char chrecord[6];
};

void gestione_menu(ALLEGRO_DISPLAY *display);
void moveroad(ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* road, car_t &c);
int moveit(float &road_y);
void move_car(car_t &c, enemy_t *&ene);
void move_enemies(enemy_t *&ene, int, int);
