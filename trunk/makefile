CPP = g++
CPP_OPTIONS = -fno-exceptions -fno-rtti --std=c++0x 

all: serializer

clean:
	rm -f *.o serializer

test.o: test.cpp archive.h
	$(CPP) $(CPP_OPTIONS) -c test.cpp -o test.o

#archive.o: archive.cpp archive.h
#	$(CPP) $(CPP_OPTIONS) -c archive.cpp -o archive.o

serializer: test.o 
	$(CPP) $(CPP_OPTIONS) test.o -o serializer
