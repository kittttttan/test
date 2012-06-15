CXX = g++
CFLAGS = -g -Wall -O2
TARGET = struct
OBJS = main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS)

clean:
	-$(RM) $(TARGET) $(OBJS)

.cc.o:
	$(CXX) $(CFLAGS) -c $<

main.o: 
