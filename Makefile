CC = g++
LIB =
LIBDIR =
CFLAGS = -g -Wall
TARGETS = fibonacci
SRCS = fibonacci.cpp
SRC_DIR = .
OBJS = $(SRCS:.cpp=.o)

all: format $(TARGETS) $(OBJS)

$(TARGETS): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(INCDIR) $(LIBDIR) $(LIB)

format:
	@for src in $(SRCS) ; do \
		echo "Formatting $$src..." ; \
		clang-format -i "$(SRC_DIR)/$$src" ; \
	done
	@echo "Done"

.PHONY: clean
clean:
	$(RM) *~ $(TARGETS) $(OBJS)
