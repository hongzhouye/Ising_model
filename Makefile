CXX=g++
CXXFLAGS=-O2 -std=c++11


mc: main.o param.o
	$(CXX) $(CXXFLAGS) main.o param.o -o mc

main.o: main.cpp include/utils.hpp include/rng.hpp include/param.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

param.o: param.cpp include/utils.hpp include/rng.hpp include/param.hpp
	$(CXX) $(CXXFLAGS) -c param.cpp

clean:
	rm -f *.o a.out mc

