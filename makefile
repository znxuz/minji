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

run:
	./$(NAME)

debug: CFLAGS += -g

debug: fclean compile

compile: generate_cc $(NAME)

$(NAME): $(obj)
	$(CC) $(obj) $(SAN) -o $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	$(RM) $(obj)

fclean: clean
	$(RM) $(NAME)
	find . -type f -name "*.o" -delete

generate_cc:
	@echo $(CFLAGS) | sed 's/\s/\n/g' > compile_flags.txt
