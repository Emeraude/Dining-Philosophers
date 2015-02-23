##
## Makefile for  in /home/broggi_t/projet/Dining-Philosophers
## 
## Made by broggi_t
## Login   <broggi_t@epitech.eu>
## 
## Started on  Mon Feb 23 23:31:27 2015 broggi_t
## Last update Mon Feb 23 23:31:27 2015 broggi_t
##

NAME	=	philo

SRCS	=	philosophe.c

CFLAGS	+=	-W -Wall -Wextra -Werror
LDFLAGS	+=	-pthread

CC	=	gcc

RM	=	rm -f

OBJS	=	$(SRCS:.c=.o)

%.o: %.c
		@printf "[\033[0;32mcompiled\033[0m] % 29s\n" $< | tr ' ' '.'
		@$(CC) -c -o $@ $< $(CFLAGS)

all:		$(NAME)

$(NAME):	$(OBJS)
		@$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)
		@printf "[\033[0;36mbuilt\033[0m] % 32s\n" $(NAME) | tr ' ' '.'

bonus:		CFLAGS+=-DBONUS;
bonus:		all

clean:
		@$(RM) $(OBJS)
		@printf "[\033[0;31mdeleted\033[0m] % 30s\n" $(OBJS) | tr ' ' '.'

fclean:		clean
		@$(RM) $(NAME)
		@printf "[\033[0;31mdeleted\033[0m] % 30s\n" $(NAME) | tr ' ' '.'

re:		fclean all

.PHONY:		all bonus clean fclean re
