compile:	main.cpp
	g++ -Wall -g main.cpp -o main.out

run:		main.out
	./main.out

clean:		main.out
	rm main.out

format:		main.cpp
	clang-format main.cpp > dummy.cpp && cat dummy.cpp > main.cpp && rm dummy.cpp
