TARGET = Cpp11
CFLAGS	= -g -Wall -std=c++11
CXX = g++
OBJS = gcc47.o

all: $(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS)

.cc.o:
	$(CXX) $(CFLAGS) -c $<

main.o:
