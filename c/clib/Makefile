TARGET = clib
CFLAGS	= -g -Wall
CC = gcc
OBJS = main.o list.o

all: $(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $<

main.o:
list.o:
