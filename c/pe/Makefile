TARGET = pe
CC = gcc
CFLAGS = -g -Wall -Wextra -O2
SRCDIR = src/
INCLUDES = -I./include/
OBJDIR = obj/
OUTDIR = build/
SOURCES = $(wildcard $(SRCDIR)*.c)
OBJS = $(SOURCES:$(SRCDIR)%.c=$(OBJDIR)%.o)

all: $(TARGET)

clean:
	-$(RM) $(OUTDIR)$(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CC) -o $(OUTDIR)$@ $(OBJS)

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(INCLUDES) $(CFLAGS) -c -o $@ $<

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)
