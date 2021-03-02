run : main 
	./main
main : main.cc chaser.cc fugitive.cc game.cc 
	g++ -Wall -g -o main main.cc fugitive.cc chaser.cc game.cc -pthread

test : main_test
	./main_test
main_test : main_test.cc chaser.cc fugitive.cc game.cc
	g++ -Wall -g -o main_test main_test.cc fugitive.cc chaser.cc game.cc -pthread