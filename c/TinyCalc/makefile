TARGET = TinyCalc
CFLAGS	= -g -Wall -Derrno_t=int
CXX = g++
OBJS = main.o lexer.o parser.o

all: $(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS)

.cc.o:
	$(CXX) $(CFLAGS) -c $<

main.o:
lexer.o:
parser.o:
