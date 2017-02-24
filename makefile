CXX=g++
CXXFLAGS=-std=c++0x -Wall -g

main: main.o ReadConfig.o Court.o functions.o apiget.o
	$(CXX) $(CXXFLAGS) -o main main.o ReadConfig.o Court.o functions.o apiget.o -l bcm2835 -l curl
ReadConfig.o: ReadConfig.cpp ReadConfig.h
	$(CXX) $(CXXFLAGS) -c ReadConfig.cpp
main.o: main.cpp ReadConfig.h Court.h functions.h
	$(CXX) $(CXXFLAGS) -c main.cpp
Court.o: Court.cpp Court.h
	$(CXX) $(CXXFLAGS) -c Court.cpp
functions.o: functions.cpp functions.h
	$(CXX) $(CXXFLAGS) -c functions.cpp
apiget.o: apiget.cpp apiget.h
	$(CXX) $(CXXFLAGS) -c apiget.cpp -l curl
