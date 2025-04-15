CXX = g++
CXXFLAGS = -std=c++17 -I/usr/lib/glut/include -I/usr/include -I/usr/lib/sfml/SFML-3.0.0/include -I/usr/lib/ -L/usr/lib/glew/include
LDFLAGS = -L/usr/lib/sfml/SFML-3.0.0/lib -L/usr/lib/glut/lib -L/usr/lib/ -L/usr/lib/glew/lib
LDLIBS = -g -lsfml-graphics -lsfml-window -lsfml-system -lGLEW -lGL -lGLU -lglut -lX11 -pthread -lsfml-system -lsfml-audio -llua

TARGET = start
SRC = game/src/engine/engineStart.cpp \
	game/src/engine/multithreading.cpp \
	game/src/engine/GameImgui.cpp \
	game/src/engine/lua/lua.cpp \
	game/src/engine/mainMenu.cpp \
	game/src/engine/console.cpp \
	game/src/shaders/vertex.cpp \
	game/src/game/game.cpp \
	game/src/game/mapSystem.cpp \
	game/src/game/physics.cpp \
	game/src/game/event.cpp \
	game/src/game/renderEvent.cpp \
	game/src/game/render.cpp \
	game/src/game/Audio/audio.cpp \
	game/src/game/scene/scene.cpp \
	game/src/game/scene/material.cpp \
	imgui/imgui_draw.cpp \
	imgui/imgui_tables.cpp \
	imgui/imgui_widgets.cpp \
	imgui/imgui-SFML.cpp \
	imgui/imgui.cpp
OBJ = $(SRC:.cpp=.o)  

all: $(TARGET)
	rm -f game/src/shaders/vertex.o game/src/game/render.o
	./$(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

r: $(TARGET)
	rm -f $(OBJ)
	./$(TARGET)

debug:  $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) -pg $(LDLIBS) -o $(TARGET)
	./$(TARGET)
	gprof $(TARGET) gmon.out > profile.txt  