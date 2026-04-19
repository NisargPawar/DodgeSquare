CXX      = g++
CXXFLAGS = -std=c++17 -Wall
LIBS     = -lsfml-graphics -lsfml-window -lsfml-system
TARGET   = DodgeSquare
SRC      = main.cpp
HEADERS  = SquareShape.h PlayerController.h ObstacleSpawner.h GameOverScreen.h HUD.h
RES      = resources.rc
OBJ_RES  = Resources.o

$(TARGET): $(SRC) $(HEADERS) $(OBJ_RES)
	$(CXX) $(CXXFLAGS) $(SRC) $(OBJ_RES) -o $(TARGET) $(LIBS)

release: $(SRC) $(HEADERS) $(OBJ_RES)
	$(CXX) $(CXXFLAGS) -mwindows $(SRC) $(OBJ_RES) -o $(TARGET) $(LIBS)

$(OBJ_RES): $(RES)
	windres $(RES) -o $(OBJ_RES)

clean:
	rm -f $(TARGET) $(OBJ_RES)