# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/08 12:50:41 by tsaby             #+#    #+#              #
#    Updated: 2025/05/06 13:37:49 by tsaby            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		:= \
					ft_printf_fd.c\
					ft_itoa.c\
					ft_strlen.c\
					ft_uitoa.c\
					ft_itoahex.c\
					ft_printf_fd_2.c\

SRCS_D		:=	src/

OBJS_D		:=	objs/

OBJS		:=	$(SRCS:%.c=$(OBJS_D)%.o)

HEAD		:=	ft_printf_fd.h

HEAD_D		:=	.

CFLAGS		:= -Wall -Wextra -Werror

AR			:=	ar rcs

NAME		:=	libftprintf_fd.a

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
