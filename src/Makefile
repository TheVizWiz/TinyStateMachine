CC = g++
FLAGS = -std=c++11 -Wall


main: TinyStateMachine.so main_local.cpp
	$(CC) $(FLAGS) main_local.cpp TinyStateMachine.so -o main.out

TinyStateMachine.so: TinyStateMachine.cpp TinyStateMachine.h
	$(CC) $(FLAGS) -c TinyStateMachine.cpp -o TinyStateMachine.so

clean:
	rm *.o *.so *.out