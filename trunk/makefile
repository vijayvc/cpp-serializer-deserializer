# --- macros
#CC=gcc
#CFLAGS=  -O3 -I /usr/local/lib/sprng/include -I /usr/local/lib/pgplot -g
CCFLAGS= --std=c++0x 
OBJECTS= archive.o test.o serializer
#LIBS = -L/usr/local/lib/sprng/lib -llcg -L/usr/local/lib/pgplot -lcpgplot -lpgplot -lX11 -lftn -lm


# --- targets
all: serializer

serializer:   archive.o test.o
	g++ $(CCFLAGS) archive.o test.o -o serializer

archive.o: archive.hpp archive.cpp
	g++ $(CCFLAGS) -o archive.o -c archive.cpp
test.o: archive.hpp archive.cpp test.cpp
	g++ $(CCFLAGS) -o test.o -c test.cpp 

# --- remove binary and executable files
clean:
	rm -f $(OBJECTS)

