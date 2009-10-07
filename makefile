
CXX = g++
INC = -I$(HOME)/include -I/usr/local/include/ -I$(HOME)/include/boost-1_32
LIB = -L$(HOME)/lib -lboost_thread


fibonacci:  fibonacci.cpp
	$(CXX) $(INC) $(LIB) -o $@ $<