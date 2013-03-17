TARGET = TinyCalc
CXX = g++
CFLAGS= -g -Wall -Wextra -Derrno_t=int
OBJDIR = obj/
SOURCES = $(wildcard *.cc)
OBJS = $(addprefix $(OBJDIR), $(SOURCES:%.cc=%.o))

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
