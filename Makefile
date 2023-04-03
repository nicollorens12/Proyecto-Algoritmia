CC = g++
FLAGS = -g -c -Wall -std=c++11
LFLAGS =

SRCS = difusioLT.cpp difusioIC.cpp greedyLT.cpp localSearchLT.cpp metaheuristicIC.cpp
OBJS = $(SRCS:.cpp=.o)
EXES = difusioLT_exe difusioIC_exe greedyLT_exe localSearchLT_exe metaheuristicIC_exe

all: $(EXES)

%.o: %.cpp
	$(CC) $(FLAGS) $< -o $@

difusioLT_exe: difusioLT.o
	$(CC) -g $^ -o $@ $(LFLAGS)

difusioIC_exe: difusioIC.o
	$(CC) -g $^ -o $@ $(LFLAGS)

greedyLT_exe: greedyLT.o
	$(CC) -g $^ -o $@ $(LFLAGS)

localSearchLT_exe: localSearchLT.o
	$(CC) -g $^ -o $@ $(LFLAGS)
	
metaheuristicIC_exe: metaheuristicIC.o
	$(CC) -g $^ -o $@ $(LFLAGS)
	
clean:
	rm -f $(OBJS) $(EXES)

