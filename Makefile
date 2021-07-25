ALL: CLEANOLD COMPLIE
CLEANOLD:
	rm -rf ./bin
COMPLIE:
	mkdir ./bin
	g++ ./src/Kirchhoff-Calculator.cpp -std=c++11 -o ./bin/Kirchhoff-Calculator.elf
