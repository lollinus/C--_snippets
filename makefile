
CXX = g++
INC = -I/usr/local/include/ -I$(HOME)include
LIB = -L/usr/local/lib -lboost_thread

all: fibonacci

fibonacci: boost_task_fibonacci.cpp
	$(CXX) $(INC) $(LIB) -o $@ $?

