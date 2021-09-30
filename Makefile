NAME	=	philo

SRCS	=	srcs/main.c				\
			srcs/initialize.c		\
			srcs/atoi.c				\
			srcs/destroy.c			\
			srcs/routine.c			\
			srcs/actions.c			\
			srcs/utils.c			\

INCLUDE	=	includes/

OBJS	=	$(SRCS:%.c=%.o)

CFLAGS	=	-Wall -Wextra -Werror -pthread -g -I ./$(INCLUDE)

CC		=	gcc

RM		=	rm -f

%.o : %.c
			$(CC) $(CFLAGS) -o $@ -c $<

$(NAME):	$(OBJS) $(DIRH)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		re all clean fclean