FILES = philo.c eatsleepthink.c init.c parsing.c quit.c routine.c rw_mutex_1.c rw_mutex_2.c time.c minilibft.c

SRCS = $(addprefix $(SRCDIR),$(FILES))

OBJS = $(addprefix $(OBJDIR),$(FILES:.c=.o))

SRCDIR = srcs/

OBJDIR = objs/

NAME = philo

ARGS = 2 300 200 200 2

ARGS2 = 2 500 200 200 2

CC = cc

CFLAGS = -pthread -Wall -Wextra -Werror

$(OBJDIR)%.o : $(SRCDIR)%.c
	mkdir -p $(OBJDIR)
	${CC} ${CFLAGS} -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -pthread

clean:
	rm -f $(OBJS)
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

push: fclean
	git add .
	git commit -m make
	git push

re: fclean all

x: $(NAME)
	./$(NAME) $(ARGS)

y: $(NAME)
	./$(NAME) $(ARGS2)

v: $(NAME)
	valgrind --tool=helgrind -s ./philo 20 14 5 5 4

.PHONY: all clean fclean re x v push
