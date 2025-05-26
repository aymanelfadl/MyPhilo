NAME	= philo

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

SRCS_DIR	= srcs/
INCS_DIR	= includes/
OBJS_DIR	= objs/

SRCS	= $(SRCS_DIR)main.c \
		  $(SRCS_DIR)init.c \
		  $(SRCS_DIR)utils.c \
		  $(SRCS_DIR)philo.c \
		  $(SRCS_DIR)monitor.c \
		  $(SRCS_DIR)cleanup.c \
		  $(SRCS_DIR)main_utils.c \
		  $(SRCS_DIR)init_utils.c

OBJS	= $(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -pthread

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -I$(INCS_DIR) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $@

clean:
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
