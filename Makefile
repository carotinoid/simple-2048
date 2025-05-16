CC = g++

main: compile execute
	

compile: 
	$(CC) board.cc main.cc -o main

execute:
	./main

clean:
	rm -f *.o
	rm -f *.log

format:
	clang-format -i *.cc *.hh