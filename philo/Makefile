NAME	= philo

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -pthread

SRCS_DIR	= srcs/
INCS_DIR	= includes/

SRCS	= $(SRCS_DIR)main.c \
		  $(SRCS_DIR)init.c \
		  $(SRCS_DIR)utils.c \
		  $(SRCS_DIR)special_philos.c \
		  $(SRCS_DIR)monitor.c \
		  $(SRCS_DIR)cleanup.c \
		  $(SRCS_DIR)main_utils.c \
		  $(SRCS_DIR)init_utils.c \
		  $(SRCS_DIR)normal_philos.c

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(INCS_DIR)/philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
