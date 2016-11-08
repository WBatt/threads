all: driver buffer

%: %.cc
	g++ -std=c++11 $< -o $@

%: %.c
	gcc $< -o $@

