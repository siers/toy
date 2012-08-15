CXX=g++
CXXFLAGS=-Wall -g3 -I/usr/include/libdrm -I/usr/include/GL -D_GNU_SOURCE=1 -D_REENTRANT -I/usr/include/SDL
LDFLAGS=-lSDL -lGLU -lGL -lpthread
OBJ=bin/log.o bin/timer.o bin/models.o bin/physical.o bin/vehicle.o bin/logic.o bin/scene.o bin/camera.o bin/main.o

all: bin/main

bin/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

bin/main: $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^
	strip $@

clean:
	rm -f bin/*
