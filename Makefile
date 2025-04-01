CC=clang++
INCLUDEDIR=include
SOURCES=src\main.cpp src\bitmap.cpp src\idgenerator.cpp
OBJECTS=$(SOURCEFILES:.cpp=.o ) 
EXECUTABLE=bitmap



all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
