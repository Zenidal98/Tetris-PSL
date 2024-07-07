CXX = g++
CXXFLAGS = -Wall -g
LDFLAGS = -lncurses

SRCS = Tutils.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = tetris

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: clean
