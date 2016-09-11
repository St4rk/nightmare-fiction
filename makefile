TARGET = nfe
LIBS = -lm -lGL -lglfw -lGLEW
CC = g++ 
CFLAGS = -std=c++11 -g -Wall 

.PHONY: default all clean

default: $(TARGET)
all: default

SHADERSDIR = shaders
OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
OBJECTS += $(patsubst %.cpp, %.o, $(wildcard shaders/*.cpp)) 
OBJECTS += $(patsubst %.cpp, %.o, $(wildcard lib/*.cpp)) 
HEADERS = $(wildcard *.h) $(wildcard shaders/*.h) 

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)