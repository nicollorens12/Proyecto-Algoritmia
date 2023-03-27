OBJS	= main.o
SOURCE	= main.cc
HEADER	= LT_graph.hh
OUT	= program.exe
CC	 = g++
FLAGS	 = -g -c -Wall -std=c++11
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cc
	make clean
	$(CC) $(FLAGS) main.cc 


clean:
	rm -f $(OBJS) $(OUT)