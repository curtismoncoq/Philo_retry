FILES = philo.c eatsleepthink.c parsing.c quit.c routine.c time.c semaphores.c minilibft.c cleaning.c rw_data.c

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
	valgrind --tool=helgrind -s ./philo 2 300 100 100 2

d: $(NAME)
	valgrind --tool=drd ./philo 2 300 100 100 2

.PHONY: all clean fclean push re x y v d
