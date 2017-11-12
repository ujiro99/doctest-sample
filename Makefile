CC = g++
LIBS =
CFLAGS = -g -Wall
LDFLAGS =
TARGETS = ./bin/fibonacci
SRC_DIR = ./src
INC_DIR = ./inc
OBJ_DIR = ./obj
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
INCS = $(wildcard $(INC_DIR)/*.hpp)
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.cpp=.o)))

$(TARGETS): $(OBJS) $(LIBS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	-mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -o $@ -c $<

all: format docs $(TARGETS) $(OBJS)

format:
	@for src in $(INCS) ; do \
		echo "Formatting $$src..." ; \
		clang-format -i "$$src" ; \
	done
	@for src in $(SRCS) ; do \
		echo "Formatting $$src..." ; \
		clang-format -i "$$src" ; \
	done
	@echo "Done"

docs:
	@doxygen

.PHONY: clean
clean:
	$(RM) *~ $(TARGETS) $(OBJS)
