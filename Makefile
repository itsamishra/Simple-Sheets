compile:	main.cpp
	g++ -Wall -g main.cpp -o main.out

run:		main.out
	./main.out

clean:		main.out
	rm main.out
