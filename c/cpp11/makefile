TARGET = cpp11
CXX = g++
CFLAGS	= -g -Wall -Wextra -std=c++11
OBJDIR = obj/
OBJS = $(OBJDIR)gcc47.o #$(OBJDIR)main.o

all: $(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS)

$(OBJDIR)%.o: %.cc
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)
