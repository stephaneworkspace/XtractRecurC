MODULES=
CFLAGS=-std=c++11 -Wall

all: xtract

xtract: main.o
	$(CXX) $(CFLAGS) main.o -o xtract $(MODULES)

main.o: main.c
	$(CXX) $(CFLAGS) -c main.c

clean:
	rm -f *.o xtract

run: 
	@$(MAKE) && ./xtract
