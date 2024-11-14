CC         = g++ 
CFLAGS     = --std=c++11 -g -Wall
CFLAGSROOT = `root-config --cflags`
LIBSROOT   = `root-config --glibs`

all: Main


Main: PrismScheme.cpp
	$(CC) $(CFLAGS) -o Main PrismScheme.cpp $(CFLAGSROOT) $(LIBSROOT)
clean:
	rm Main
