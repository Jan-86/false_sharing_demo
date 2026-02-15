CXXFLAGS = -std=c++23 -O2 -Wall

all: with_false_sharing.out without_false_sharing.out

without_false_sharing.out: main.cpp
	g++ -o $@ $< $(CXXFLAGS) -DFIX_FALSE_SHARING
	
with_false_sharing.out: main.cpp
	g++ -o $@ $< $(CXXFLAGS)

clean:
	rm -f without_false_sharing.out with_false_sharing.out
