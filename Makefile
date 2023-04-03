CC = g++
FLAGS = -g -c -Wall -std=c++11
LFLAGS =

SRCS = difusioLT.cpp difusioIC.cpp greedyLT.cpp localSearchLT.cpp metaheuristicIC.cpp test_simulations.cpp
OBJS = $(SRCS:.cpp=.o)
EXES = greedyLT_exe localSearchLT_exe metaheuristicIC_exe test_simulations_exe 

all: $(EXES)

%.o: %.cpp
	$(CC) $(FLAGS) $< -o $@

greedyLT_exe: greedyLT.o difusioLT.o
	$(CC) -g $^ -o $@ $(LFLAGS)

localSearchLT_exe: localSearchLT.o difusioLT.o
	$(CC) -g $^ -o $@ $(LFLAGS)
	
metaheuristicIC_exe: metaheuristicIC.o difusioIC.o
	$(CC) -g $^ -o $@ $(LFLAGS)

test_simulations_exe: test_simulations.o difusioIC.o difusioLT.o
	$(CC) -g $^ -o $@ $(LFLAGS)
	
clean:
	rm -f $(OBJS) $(EXES)

