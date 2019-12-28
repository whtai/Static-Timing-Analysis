
all: cadb105

cadb105: main.o FinalGraph.o
	g++ -pthread -std=c++11 -O2  main.o FinalGraph.o -o cadb105

main.o: main.cpp
	g++ -pthread -std=c++11 -O2 -c main.cpp
FinalGraph.o: FinalGraph.cpp
	g++ -pthread -std=c++11 -O2 -c FinalGraph.cpp
 
# clean all the .o and executable files
clean:
	rm -rf *.o cadb105
