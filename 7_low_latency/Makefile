run: output
	@echo 1
	# @./output

output: main.o
	@g++ main.o -o output

main.o: main.cpp
	@g++ -c main.cpp

clean:
	@rm *.o output