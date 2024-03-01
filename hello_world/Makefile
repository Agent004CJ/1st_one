# version avec deux variables CXX et CXXFLAGS

# Makefile

CXX = g++
CXXFLAGS = -g -Wall -std=c++11

all: helloworld

helloworld   : helloworld.o
	$(CXX) helloworld.o -o helloworld

clean:
@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
@/bin/rm -f *.o *.x *.cc~ *.h~