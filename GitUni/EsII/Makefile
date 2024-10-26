CC         = g++ 
CFLAGS     = --std=c++11 -g -Wall 
CFLAGSROOT = `root-config --cflags`
LIBSROOT   = `root-config --glibs`

all: Main
LorentzVector.o: LorentzVector.cpp
	$(CC) $(CFLAGS) -c LorentzVector.cpp  $(CFLAGSROOT)
Vector3.o: Vector3.cpp
	$(CC) $(CFLAGS) -c Vector3.cpp      $(CFLAGSROOT)
MatPoint.o: MatPoint.cpp 
	$(CC) $(CFLAGS) -c MatPoint.cpp    $(CFLAGSROOT)
OdeSolver.o: OdeSolver.cpp
	$(CC) $(CFLAGS) -c OdeSolver.cpp      $(CFLAGSROOT)
Main: Main.cpp Vector3.o MatPoint.o OdeSolver.o LorentzVector.o
	$(CC) $(CFLAGS) -o Main Main.cpp Vector3.o LorentzVector.o OdeSolver.o MatPoint.o $(CFLAGSROOT) $(LIBSROOT)

TestLorentzVector: TestLorentzVector.cpp Vector3.o LorentzVector.o
	$(CC) $(CFLAGS) -o Main TestLorentzVector.cpp Vector3.o LorentzVector.o $(CFLAGSROOT) $(LIBSROOT)
clean:
	rm *.o Main 
