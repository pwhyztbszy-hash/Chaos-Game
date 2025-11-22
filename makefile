SRC_DIR := ./code
OBJ_DIR := .
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Linux SFML link flags
LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Linux include path (SFML installs here)
CXXFLAGS := -g -Wall -fpermissive -std=c++17

TARGET := triangle_out

$(TARGET): $(OBJ_FILES)
	g++ -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CXXFLAGS) -c -o $@ $<

run:
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o
