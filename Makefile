CXX = g++
FLAGS = -std=c++17 -g -Wall -Wextra -Wconversion -Wno-sign-conversion -pedantic

e ?= a

run: $(e).out
	./$(e).out


$(e).out : $(e).cpp
	$(CXX) $(FLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f *.out
	rm -rf *.dSYM

