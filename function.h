
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