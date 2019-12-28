
all		: cadb105

cadb105	: main.o FinalGraph.o
	g++ -pthread -std=c++11 -O2  main.o FinalGraph.o -o cadb105

main.o		: main.cpp
	g++ -pthread -std=c++11 -O2 -c main.cpp
FinalGraph.o	: FinalGraph.cpp
	g++ -pthread -std=c++11 -O2 -c FinalGraph.cpp
 
run_case1:
	time ./run_sta1
  
run_case2:
	time ./run_sta2
 
run_case3: 
	time ./run_sta3
  
run_case4:  
	time ./run_sta4
  
run_case5:   
	time ./run_sta5
  
 
# clean all the .o and executable files
clean:
	rm -rf *.o cadb105
