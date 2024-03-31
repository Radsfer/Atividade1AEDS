CC = g++
CFLAGS = -Wall
SRC_DIR = src
BUILD_DIR = build
EXECUTABLE = App
TARGET_DIR=datasets

SRCS := $(wildcard $(SRC_DIR)/*.cpp)

OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

all: $(BUILD_DIR/)/$(EXECUTABLE)

clean:
	rm -f $(TARGET_DIR)/geracoes.mps
	rm -f $(BUILD_DIR)/*.o

run:
	mkdir -p $(TARGET_DIR)
	chmod +w $(TARGET_DIR)
	./$(BUILD_DIR)/$(EXECUTABLE)

