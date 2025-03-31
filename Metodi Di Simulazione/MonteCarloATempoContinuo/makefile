CC         = g++ 
CFLAGS     = --std=c++11 -g -Wall
CFLAGSROOT = `root-config --cflags`
LIBSROOT   = `root-config --glibs`

all: Main

Grid.o: Grid.cpp
	$(CC) $(CFLAGS) -c Grid.cpp  $(CFLAGSROOT)
Main: Main.cpp Grid.o
	$(CC) $(CFLAGS) -o Main Main.cpp Grid.o $(CFLAGSROOT) $(LIBSROOT)
clean:
	rm *.o