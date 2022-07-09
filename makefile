NAME	:=	philosophers

CC	:= gcc
CFLAGS	:=	#-Wall -Wextra -Werror

DIR_SRCS	:=	srcs
DIR_OBJS	:=	.objs
DIR_INCS	:=	incs

LST_SRCS	:=	philosophers.c \
				execution.c \


LST_OBJS	:=	$(LST_SRCS:.c=.o)

LST_INCS	:=	philosophers.h

SRCS	:=	$(addprefix $(DIR_SRCS)/,$(LST_SRCS))
OBJS	:=	$(addprefix $(DIR_OBJS)/,$(LST_OBJS))
INCS	:=	$(addprefix $(DIR_INCS)/,$(LST_INCS))

all: $(NAME)	

$(NAME): $(OBJS) $(INCS) makefile 
	$(CC) $(CFLAGS) $(OBJS) -o $@ -I $(DIR_INCS)

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c
	mkdir -p $(DIR_OBJS)
	$(CC) $(CFLAGS) -I $(DIR_INCS) -c $< -o $@

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)

clean:
	rm -rf $(DIR_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY:    all bonus clean fclean re
