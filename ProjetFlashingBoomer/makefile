INCLUDE_DIR_SDL = -I/usr/include/SDL2
LIBS_SDL = -L/usr/include/x86_64-linux-gnu  -lSDL2 -lSDL2_image


all: bin/mainTestRunner bin/mainTestCanon bin/mainTestTxtMapping bin/mainFinal

bin/mainFinal: obj/mainFinal.o obj/runner.o obj/game.o obj/map.o obj/timer.o obj/tweening.o obj/canon.o obj/button.o obj/weapon.o obj/projectile.o obj/menu.o obj/coin.o obj/hud.o obj/heart.o obj/write.o
	g++ -g -ggdb obj/mainFinal.o obj/runner.o obj/game.o obj/map.o obj/timer.o obj/tweening.o obj/canon.o obj/button.o obj/weapon.o obj/projectile.o obj/menu.o obj/coin.o obj/hud.o obj/heart.o obj/write.o -o bin/mainFinal $(LIBS_SDL)

bin/mainTestTxtMapping: obj/mainTestTxtMapping.o obj/runner.o obj/game.o obj/map.o obj/timer.o obj/tweening.o obj/canon.o obj/button.o obj/weapon.o obj/projectile.o obj/menu.o obj/coin.o obj/hud.o obj/heart.o obj/write.o
	g++ -g -ggdb obj/mainTestTxtMapping.o obj/runner.o obj/game.o obj/map.o obj/timer.o obj/tweening.o obj/canon.o obj/button.o obj/weapon.o obj/projectile.o obj/menu.o obj/coin.o obj/hud.o obj/heart.o obj/write.o -o bin/mainTestTxtMapping $(LIBS_SDL)

bin/mainTestCanon: obj/mainTestCanon.o obj/runner.o obj/game.o obj/map.o obj/timer.o obj/tweening.o obj/canon.o obj/button.o obj/weapon.o obj/projectile.o obj/menu.o obj/coin.o obj/hud.o obj/heart.o obj/write.o
	g++ -g -ggdb obj/mainTestCanon.o obj/runner.o obj/game.o obj/map.o obj/timer.o obj/tweening.o obj/canon.o obj/button.o obj/weapon.o obj/projectile.o obj/menu.o obj/coin.o obj/hud.o obj/heart.o obj/write.o -o bin/mainTestCanon $(LIBS_SDL)

bin/mainTestRunner: obj/mainTestRunner.o obj/runner.o obj/game.o obj/map.o obj/timer.o obj/tweening.o obj/canon.o obj/button.o obj/weapon.o obj/projectile.o obj/menu.o obj/coin.o obj/hud.o obj/heart.o obj/write.o
	g++ -g -ggdb obj/mainTestRunner.o obj/runner.o obj/game.o obj/map.o obj/timer.o obj/tweening.o obj/canon.o obj/button.o obj/weapon.o obj/projectile.o obj/menu.o obj/coin.o obj/hud.o obj/heart.o obj/write.o -o bin/mainTestRunner $(LIBS_SDL)

obj/mainFinal.o: src/mainFinal.cpp
	g++ -g -Wall -ggdb $(INCLUDE_DIR_SDL) -c src/mainFinal.cpp -o obj/mainFinal.o

obj/mainTestTxtMapping.o: src/mainTestTxtMapping.cpp
	g++ -g -Wall -ggdb $(INCLUDE_DIR_SDL) -c src/mainTestTxtMapping.cpp -o obj/mainTestTxtMapping.o

obj/mainTestCanon.o: src/mainTestCanon.cpp
	g++ -g -Wall -ggdb $(INCLUDE_DIR_SDL) -c src/mainTestCanon.cpp -o obj/mainTestCanon.o

obj/mainTestRunner.o: src/mainTestRunner.cpp
	g++ -g -Wall -ggdb $(INCLUDE_DIR_SDL) -c src/mainTestRunner.cpp -o obj/mainTestRunner.o

obj/runner.o: src/runner.cpp src/runner.h
	g++ -g -Wall -ggdb $(INCLUDE_DIR_SDL) -c src/runner.cpp -o obj/runner.o

obj/canon.o: src/canon.cpp src/canon.h
	g++ -g -Wall -ggdb $(INCLUDE_DIR_SDL) -c src/canon.cpp -o obj/canon.o

obj/weapon.o: src/weapon.cpp src/weapon.h
	g++ -g -Wall -ggdb $(INCLUDE_DIR_SDL) -c src/weapon.cpp -o obj/weapon.o

obj/projectile.o: src/projectile.cpp src/projectile.h
	g++ -g -Wall -ggdb $(INCLUDE_DIR_SDL) -c src/projectile.cpp -o obj/projectile.o

obj/game.o: src/game.cpp src/game.h
	g++ -g -Wall -ggdb $(INCLUDE_DIR_SDL) -c src/game.cpp -o obj/game.o

obj/map.o: src/map.cpp src/map.h
	g++ -g -Wall -ggdb $(INCLUDE_DIR_SDL) -c src/map.cpp -o obj/map.o

obj/timer.o: src/timer.cpp src/timer.h
	g++ -g -Wall -ggdb $(INCLUDE_DIR_SDL) -c src/timer.cpp -o obj/timer.o

obj/tweening.o: src/tweening.cpp src/tweening.h
	g++ -g -Wall -ggdb $(INCLUDE_DIR_SDL) -c src/tweening.cpp -o obj/tweening.o

obj/button.o: src/button.cpp src/button.h
	g++ -g -Wall -ggdb $(INCLUDE_DIR_SDL) -c src/button.cpp -o obj/button.o

obj/menu.o: src/menu.cpp src/menu.h
	g++ -g -Wall -ggdb $(INCLUDE_DIR_SDL) -c src/menu.cpp -o obj/menu.o

obj/coin.o: src/coin.cpp src/coin.h
	g++ -g -Wall -ggdb $(INCLUDE_DIR_SDL) -c src/coin.cpp -o obj/coin.o

obj/hud.o: src/hud.cpp src/hud.h
	g++ -g -Wall -ggdb $(INCLUDE_DIR_SDL) -c src/hud.cpp -o obj/hud.o

obj/heart.o: src/heart.cpp src/heart.h
	g++ -g -Wall -ggdb $(INCLUDE_DIR_SDL) -c src/heart.cpp -o obj/heart.o

obj/write.o: src/write.cpp src/write.h
	g++ -g -Wall -ggdb $(INCLUDE_DIR_SDL) -c src/write.cpp -o obj/write.o
clean:
	rm obj/*.o bin/*
