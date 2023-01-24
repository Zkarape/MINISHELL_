NAME = minishell

SRCS = $(wildcard *.c)

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -g -ggdb3 -Wall -Wextra -fsanitize=address 

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME) -I ./

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re
