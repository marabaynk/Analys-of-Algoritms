CFLAGS := -std=c++11
CC := g++
SRC := $(wildcard *.cpp)
OBJ := $(SRC:%.cpp%=%.o)

main.exe: $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.o : %.cpp *.hpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.exe *.o

