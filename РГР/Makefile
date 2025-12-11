# Project: lifegame gametest
# Makefile created by Dev-C++ 5.11

CPP      = g++
CC       = gcc
WINDRES  = windres.exe
OBJ      = obj/src/libgame.a obj/src/main.o
LINKOBJ  = obj/src/main.o obj/src/libgame.a
OBJTEST  = obj/src/main_test.o obj/src/libgame_test.o obj/src/libgame.a
LIBS     = -L src/MinGW64cop/lib -L src/MinGW64cop/x86_64-w64-mingw32/lib -L src/SFML-2.4.2/lib -static-libgcc -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -lopengl32
CXXINCS  = -I src/SFML-2.4.2/include -I src/libgame -I thirdparty/ctest
BIN      = bin/lifegame.exe
BINTEST  = bin/gametest.exe
CXXFLAGS = $(CXXINCS) 
RM       = rm.exe -f

.PHONY: all clean clean-custom

all: $(BIN) $(BINTEST)

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(LINKOBJ)
	$(CPP) -fPIC $(LINKOBJ) -o $(BIN) $(LIBS) -fPIC

$(BINTEST): obj/src/main_test.o obj/src/ctest.o obj/src/libgame_test.o
	$(CPP) -I thirdparty -I obj/src obj/src/main_test.o obj/src/libgame_test.o obj/src/ctest.o obj/src/libgame.a -o $(BINTEST) $(LIBS)

obj/src/libgame.a: obj/src/libgame.o
	ar rcs $@ $^

obj/src/libgame.o: src/libgame/libgame.cpp
	$(CPP) $(CXXFLAGS) -c src/libgame/libgame.cpp -o obj/src/libgame.o 

obj/src/main.o: src/lifegame/main.cpp
	$(CPP) $(CXXFLAGS) -c -Isrc/libgame src/lifegame/main.cpp -o obj/src/main.o 
	
obj/src/main_test.o: test/main_test.cpp thirdparty/ctest.h
	$(CPP) $(CXXFLAGS) -I thirdparty -std=c++14 -c test/main_test.cpp -o obj/src/main_test.o 
	
obj/src/libgame_test.o: test/libgame_test.cpp thirdparty/ctest.h
	$(CPP) $(CXXFLAGS) -I thirdparty -std=c++14 -c test/libgame_test.cpp -o obj/src/libgame_test.o 
	
obj/src/ctest.o: thirdparty/ctest.c
	$(CC) -std=c99 -c thirdparty/ctest.c -o obj/src/ctest.o
