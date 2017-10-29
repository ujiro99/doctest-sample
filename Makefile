CC = g++
LIB =
LIBDIR =
CFLAGS = -g -Wall
TARGETS = fibonacci
SRCS = fibonacci.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGETS) $(OBJS)

$(TARGETS): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(INCDIR) $(LIBDIR) $(LIB)

.PHONY: clean
clean:
	$(RM) *~ $(TARGETS) $(OBJS)
