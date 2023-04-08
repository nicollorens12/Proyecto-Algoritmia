CC = g++
FLAGS = -g -c -Wall -std=c++11
LFLAGS =

SRCS = difusioLT.cpp difusioIC.cpp greedyLT.cpp greedyIC.cpp localSearchLT.cpp metaheuristicIC.cpp metaheuristicLT.cpp test_simulations.cpp readData.cpp graph.cpp
OBJS = $(SRCS:.cpp=.o)
EXES = greedyIC_exe greedyLT_exe localSearchLT_exe metaheuristicIC_exe metaheuristicLT_exe test_simulations_exe 

all: $(EXES)

%.o: %.cpp
	$(CC) $(FLAGS) $< -o $@

greedyIC_exe: greedyIC.o difusioIC.o readData.o graph.o
	$(CC) -g $^ -o $@ $(LFLAGS)

greedyLT_exe: greedyLT.o difusioLT.o readData.o
	$(CC) -g $^ -o $@ $(LFLAGS)

localSearchLT_exe: localSearchLT.o difusioLT.o
	$(CC) -g $^ -o $@ $(LFLAGS)
	
metaheuristicLT_exe: metaheuristicLT.o difusioLT.o readData.o
	$(CC) -g $^ -o $@ $(LFLAGS)	
	
metaheuristicIC_exe: metaheuristicIC.o difusioIC.o readData.o
	$(CC) -g $^ -o $@ $(LFLAGS)

test_simulations_exe: test_simulations.o difusioIC.o difusioLT.o
	$(CC) -g $^ -o $@ $(LFLAGS)
	
clean:
	rm -f $(OBJS) $(EXES)

