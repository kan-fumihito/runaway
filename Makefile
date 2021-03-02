run : main 
	./main
main : main.cc predator.cc prey.cc game.cc 
	g++ -Wall -g -o main main.cc prey.cc predator.cc game.cc -pthread

test : main_test
	./main_test
main_test : main_test.cc predator.cc prey.cc game.cc
	g++ -Wall -g -o main_test main_test.cc prey.cc predator.cc game.cc -pthread