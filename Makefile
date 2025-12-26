NAME := app

SRCS := $(wildcard src/*.c)

HEADER := includes/header.h

OBJS := $(SRCS:.c=.o)

CC := cc

FLAGS := -Wall -Werror -Wextra -g
LFLAGS := -lpthread

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LFLAGS)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re