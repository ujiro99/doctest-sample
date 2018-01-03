CC = g++
LIBS =
CFLAGS = -g -Wall
LDFLAGS =

# output files
TARGETS = fibonacci

# directories
SRC_DIR = ./src
INC_DIR = ./inc
OBJ_DIR = ./obj

# files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
INCS = $(wildcard $(INC_DIR)/*.hpp)
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.cpp=.o)))
DEPENDS = $(OBJS:.o=.d)

# tasks
all: format $(TARGETS) test

$(TARGETS): $(OBJS) $(LIBS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if [ ! -d $(OBJ_DIR) ]; \
		then echo "mkdir -p $(OBJ_DIR)"; mkdir -p $(OBJ_DIR); \
		fi
	$(CC) $(CFLAGS) -I$(INC_DIR) -o $@ -c $<

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

clean:
	$(RM) $(TARGETS) $(OBJS) $(DEPENDS)

-include $(DEPENDS)

.PHONY: all clean docs
