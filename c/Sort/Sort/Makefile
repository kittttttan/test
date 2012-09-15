TARGET = Sort
CFLAGS	= -g -Wall
CC = gcc
OBJS = main.o sort.o

all: $(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $<

main.o:
sort.o:
