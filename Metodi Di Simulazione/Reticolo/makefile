CC         = g++ 
CFLAGS     = --std=c++11 -g -Wall
CFLAGSROOT = `root-config --cflags`
LIBSROOT   = `root-config --glibs`

all: Main

Main: Main.cpp
	$(CC) $(CFLAGS) -o Main Main.cpp $(CFLAGSROOT) $(LIBSROOT)
clean:
	rm *.o
