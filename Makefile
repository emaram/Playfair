CXX		:= g++
CXXFLAGS	:= -std=gnu++14 -Wall
OBJ_DIR		:= obj
OBJECTS		:= $(OBJ_DIR)/main.o $(OBJ_DIR)/EncryptionManager.o $(OBJ_DIR)/Playfair.o 
TARGET		:= Playfair

all: build $(TARGET)

build:
	@mkdir -p $(OBJ_DIR)

Playfair: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

.PHONY: all build debug clean

debug: CXXFLAGS += -DDEBUG -g
debug: all

clean:
	-@rm -f *.o $(OBJECTS) Playfair
	-@rmdir $(OBJ_DIR)

