SRCS		:= \
					get_next_line.c\
					get_next_line_utils.c\

SRCS_D		:=	src/

OBJS_D		:=	objs/

OBJS		:=	$(SRCS:%.c=$(OBJS_D)%.o)

HEAD		:=	get_next_line.h

HEAD_D		:=	.

CFLAGS		:= -Wall -Wextra -Werror

AR			:=	ar rcs

NAME		:=	libgnl.a

all			:	$(NAME)

$(NAME)		:	$(OBJS_D) $(OBJS) Makefile
					$(AR) $(NAME) $(OBJS)

$(OBJS)		:	$(OBJS_D)%.o: $(SRCS_D)%.c $(HEAD)
				$(CC) $(CFLAGS) -I$(HEAD_D) -c $< -o $@

$(OBJS_D)	:
				@mkdir -p $(OBJS_D)

clean		:
				$(RM) -r $(OBJS) $(OBJS_D)

fclean		:	clean
				$(RM) $(NAME)

re			:	fclean all

.PHONY:	all clean fclean re
