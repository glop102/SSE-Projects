objs = \
build/glopConfig.o build/globals.o build/config_registry.o \
build/armor.o build/enemy.o build/status_effect.o build/weapon.o\
build/player.o build/item.o build/battle.o
CC = g++
CC_OPTS = -std=c++11


game: main.cpp $(objs)
	$(CC) $(CC_OPTS) -o game main.cpp $(objs)

build:
	mkdir build

build/glopConfig.o: glopConfig.h glopConfig.cpp | build
	$(CC) $(CC_OPTS) -c glopConfig.cpp -o build/glopConfig.o
build/globals.o: globals.cpp globals.h | build
	$(CC) $(CC_OPTS) -c globals.cpp -o build/globals.o
build/config_registry.o: config_registry.h config_registry.cpp | build
	$(CC) $(CC_OPTS) -c config_registry.cpp -o build/config_registry.o

build/armor.o: armor.cpp armor.h | build
	$(CC) $(CC_OPTS) -c armor.cpp -o build/armor.o
build/enemy.o: enemy.cpp enemy.h | build
	$(CC) $(CC_OPTS) -c enemy.cpp -o build/enemy.o
build/status_effect.o: status_effect.cpp status_effect.h | build
	$(CC) $(CC_OPTS) -c status_effect.cpp -o build/status_effect.o
build/weapon.o: weapon.cpp weapon.h | build
	$(CC) $(CC_OPTS) -c weapon.cpp -o build/weapon.o

build/player.o: player.h player.cpp | build
	$(CC) $(CC_OPTS) -c player.cpp -o build/player.o
build/item.o: item.h item.cpp | build
	$(CC) $(CC_OPTS) -c item.cpp -o build/item.o
build/battle.o: battle.h battle.cpp | build
	$(CC) $(CC_OPTS) -c battle.cpp -o build/battle.o


.PHONY : clean
clean:
	rm -rf build
	rm -f game