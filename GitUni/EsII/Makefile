CC         = g++ 
CFLAGS     = --std=c++11 -g -Wall 
CFLAGSROOT = `root-config --cflags`
LIBSROOT   = `root-config --glibs`

all: Main

Vector3.o: Vector3.cpp
	$(CC) $(CFLAGS) -c Vector3.cpp      $(CFLAGSROOT)
MatPoint.o: MatPoint.cpp 
	$(CC) $(CFLAGS) -c MatPoint.cpp    $(CFLAGSROOT)
OdeSolver.o: OdeSolver.cpp
	$(CC) $(CFLAGS) -c OdeSolver.cpp      $(CFLAGSROOT)
Main: Main.cpp Vector3.o MatPoint.o OdeSolver.o
	$(CC) $(CFLAGS) -o Main Main.cpp Vector3.o OdeSolver.o MatPoint.o $(CFLAGSROOT) $(LIBSROOT)

clean:
	rm *.o Main 
