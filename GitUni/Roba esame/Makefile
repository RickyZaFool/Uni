CC         = g++ 
CFLAGS     = --std=c++11 -g -Wall
CFLAGSROOT = `root-config --cflags`
LIBSROOT   = `root-config --glibs` -lMinuit

all: Integrali Zeri PValue Es8

Integrali: Integrali.cpp
	$(CC) $(CFLAGS) -o Integrali Integrali.cpp $(CFLAGSROOT) $(LIBSROOT)

Zeri: Zeri.cpp
	$(CC) $(CFLAGS) -o Zeri Zeri.cpp $(CFLAGSROOT) $(LIBSROOT)

PValue: Generare_secondo_distrib_e_verifica_compatibilita.cpp
	$(CC) $(CFLAGS) -o PValue Generare_secondo_distrib_e_verifica_compatibilita.cpp $(CFLAGSROOT) $(LIBSROOT)

Es8: Es8.cpp
	$(CC) $(CFLAGS) -o Es8 Es8.cpp $(CFLAGSROOT) $(LIBSROOT)

clean:
	-rm Integrali
	-rm Zeri
	-rm PValue
	-rm Es8