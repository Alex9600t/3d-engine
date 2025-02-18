CXX = g++
CXXFLAGS = -std=c++17 -I/usr/lib/glut/include -I/usr/include -I/usr/lib/sfml/SFML-3.0.0/include
LDFLAGS = -L/usr/lib/sfml/SFML-3.0.0/lib -L/usr/lib/glut/lib
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system -lGL -lGLU -lglut -lX11

TARGET = start
SRC = game/src/engine/engineStart.cpp \
	game/src/engine/GameImgui.cpp \
	game/src/shaders/vertex.cpp \
	game/src/game/game.cpp \
	game/src/game/event.cpp \
	game/src/game/render.cpp \
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