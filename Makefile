CC = g++
FLAGS = -g -c -Wall -std=c++11
LFLAGS =

SRCS = 	difusioLT.cpp \
		difusioIC.cpp \
		greedyLT.cpp \
		greedyIC.cpp \
		localSearchLT.cpp \
		localSearchIC.cpp \
		metaheuristicIC.cpp \
		metaheuristicLT.cpp \
		readData.cpp  \
		graph.cpp \
		test_simulations.cpp \
		test_metaheuristic.cpp \
		test_benchmark_all.cpp  

OBJS = 	$(SRCS:.cpp=.o)

EXES = 	test_simulations_exe\
		test_metaheuristic_exe\
		test_benchmark_exe

all: $(EXES)

%.o: %.cpp
	$(CC) $(FLAGS) $< -o $@

test_simulations_exe:  difusioIC.o difusioLT.o test_simulations.o graph.o
	$(CC) -g $^ -o $@ $(LFLAGS) 

test_metaheuristic_exe: 	difusioIC.o difusioLT.o test_metaheuristic.o \
							graph.o metaheuristicLT.o #metaheuristicIC.o
	$(CC) -g $^ -o $@ $(LFLAGS)

test_benchmark_exe: 	test_benchmark_all.o \
						difusioIC.o difusioLT.o \
						greedyLT.cpp greedyIC.cpp \
						localSearchLT.cpp localSearchIC.cpp \
						metaheuristicIC.o metaheuristicLT.o \
						readData.o graph.o \
						
	$(CC) -g $^ -o $@ $(LFLAGS) 
	
clean:
	rm -f $(OBJS) $(EXES)
	rm -r debug_output

