CXX=g++
CXXFLAGS=-O2 -std=c++11


mc: main.o param.o read.o
	$(CXX) $(CXXFLAGS) main.o param.o read.o -o mc

main.o: main.cpp include/utils.hpp include/rng.hpp include/param.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

param.o: param.cpp include/utils.hpp include/rng.hpp include/param.hpp \
	include/read.hpp
	$(CXX) $(CXXFLAGS) -c param.cpp

read.o: read.cpp include/param.hpp
	$(CXX) $(CXXFLAGS) -c read.cpp

clean:
	rm -f *.o a.out mc

