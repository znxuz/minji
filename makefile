SRC_DIR := src
NAME := mj

CC := clang++
LANG := c++
STD := c++20
WARNINGS := -Wall -Wextra -Wpedantic -Weffc++ -Wconversion -Wshadow -Wnon-virtual-dtor \
			-Wcast-align -Woverloaded-virtual -Wnull-dereference \
			-Wno-unused-parameter -Wno-unused-function -Wno-unused-variable
SAN := -fsanitize=address,undefined
CFLAGS := -x $(LANG) -std=$(STD) $(WARNINGS) $(DEBUG)

src := $(shell find $(SRC_DIR) -type f -name "*.cpp")
obj := $(src:.cpp=.o)

all: compile

run: compile
	./$(NAME)

debug: CFLAGS += -g

debug: fclean compile

compile: $(NAME)

$(NAME): $(obj)
	$(CC) $(obj) $(SAN) -o $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	$(RM) $(obj)

fclean: clean
	$(RM) $(NAME)
	find . -type f -name "*.o" -delete
