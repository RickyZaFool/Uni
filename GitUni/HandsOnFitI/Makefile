CC         = g++ 
CFLAGS     = --std=c++11 -g -Wall
CFLAGSROOT = `root-config --cflags`
LIBSROOT   = `root-config --glibs`
MINUIT     = -lMinuit

all: Main


Main: Kater.cpp
	$(CC) $(CFLAGS) -o Main Kater.cpp $(CFLAGSROOT) $(LIBSROOT) $(MINUIT)
clean:
	rm Main
