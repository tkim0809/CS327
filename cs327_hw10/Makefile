CC = g++
CFLAGS = -Wall -std=c++17
LIBS = -lncurses

TARGET = airplane_battle
SOURCES = as.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LIBS)

clean:
	rm -f $(TARGET)
