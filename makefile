MODULES=
CFLAGS=-std=c++11 -Wall
SOURCE=main.cpp split.cpp
OBJECTS=$(SOURCE:.cpp=.o)

all: xtract

xtract: $(OBJECTS)
	$(CXX) $(CFLAGS) $(OBJECTS) -o $@ $(MODULES)

split.o: split.cpp
	$(CXX) $(CFLAGS) -c split.cpp

main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp

clean:
	rm -f *.o xtract

run: 
	@$(MAKE) && ./xtract
