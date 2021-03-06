CPP = main.cpp start_finish.cpp game_core.cpp move_road.cpp move_car.cpp enemies.cpp
OBJ = main.o start_finish.o game_core.o move_road.o move_car.o enemies.o

CFLAGS = -Wall 
LDFLAGS = `pkg-config --cflags --libs allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0`

cars: $(OBJ)
	g++ $(CFLAGS) -o cars $(OBJ) $(LDFLAGS)
	make clean

-include dependencies
.PHONY: clean cleanall debug

clean:
	rm *.o
cleanall:
	rm cars
debug:
	g++ -g -D DEBUG_MODE $(CFLAGS) -o cars $(CPP) $(LDFLAGS)
