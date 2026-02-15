CXXFLAGS =	-std=c++23 -O0 -Wall
#CXXFLAGS += -DFIX_FALSE_SHARING

TARGET =	a.out

main.o: main.cpp
  g++ -o $@ -c $< $(CXXFLAGS)

$(TARGET):	main.o
	g++ -o $@ $^

all:	$(TARGET)

clean:
	rm -f main.o $(TARGET)
