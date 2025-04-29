# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsaby <tsaby@student.42lyon.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/23 17:03:26 by tsaby             #+#    #+#              #
#    Updated: 2025/04/29 18:47:22 by tsaby            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all bonus clean fclean re re_bonus valgrind valgrindext

YELLOW	:= \033[0;33m
NC		:= \033[0m

#*------------------------------------------------------------------------------*

SRCS		:=	main.c \
				clean.c \
				token.c \
				init.c \
				utils_token.c \
				expand.c \
				utils_expand.c \
				debug.c

#SRCS_BONUS	:=

#*------------------------------------------------------------------------------*

SRCS_D		:=	sources/

#SRCS_B		:=	sources/bonus/

OBJS_D		:=	objs/

#OBJS_B_D	:=	objs_bonus/

#*------------------------------------------------------------------------------*

OBJS		:=	$(SRCS:%.c=$(OBJS_D)%.o)

#OBJS_B		:=	$(SRCS_BONUS:%.c=$(OBJS_B_D)%.o)

#*------------------------------------------------------------------------------*

HEAD		:=	includes/minishell.h \
				includes/error.h \
				includes/expand.h \
				includes/token.h

#HEAD_BONUS	:=	includes/minishell_bonus.h \

HEAD_D		:=	.

#*------------------------------------------------------------------------------*

CFLAGS		:=	-Wall -Wextra -Werror -g3

#*------------------------------------------------------------------------------*

NAME		:=	minishell

#NAME_B		:=	minishell_bonus

#*------------------------------------------------------------------------------*

LIBFT		=	Libft/

LIBFT_A		=	$(addprefix $(LIBFT), libft_ex.a)

#*------------------------------------------------------------------------------*

all			:
				@$(MAKE) --no-print-directory $(NAME)

#bonus		:
#				@$(MAKE) --no-print-directory $(NAME_B)

#*------------------------------------------------------------------------------*

VFLAGS			=	--leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes
VFLAGS			+=	--suppressions=ignore_readline.supp -s
VFLAGS			+=	--log-socket=127.0.0.1:4242

#*------------------------------------------------------------------------------*

$(NAME)		:	$(OBJS_D) $(OBJS) $(LIBFT_A) $(HEAD)
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)  -Lft_ex $(LIBFT_A) -lreadline
				@echo "$(YELLOW)$(NAME) successfully built!$(NC)"

#$(NAME_B)	:	$(OBJS_B_D) $(OBJS_B) $(LIBFT_A) $(HEAD_BONUS)
#				@$(CC)  -o $(NAME_B) $(OBJS_B)  -Lft_ex $(LIBFT_A)
#				@echo "$(YELLOW)$(NAME_B) successfully built!$(NC)"

$(OBJS)		:	$(OBJS_D)%.o: $(SRCS_D)%.c $(HEAD)
				@echo "$(YELLOW)Compiling $<, depends on $(HEAD)...$(NC)"
				@$(CC) $(CFLAGS) -Iincludes -I$(LIBFT)/includes -c $< -o $@

#$(OBJS_B)	:	$(OBJS_B_D)%.o: $(SRCS_B)%.c $(HEAD_BONUS)
#				@echo "$(YELLOW)Compiling $<, depends on $(HEAD_BONUS)...$(NC)"
#				@$(CC) $(CFLAGS) -Iincludes -I$(LIBFT)/includes -c $< -o $@

$(LIBFT_A):
				@$(MAKE) -s --no-print-directory -C $(LIBFT)

$(OBJS_D)	:
				@mkdir -p $(OBJS_D)

#$(OBJS_B_D)	:
#				@mkdir -p $(OBJS_B_D)

#*------------------------------------------------------------------------------*

clean		:
				@$(RM) -r $(OBJS) $(OBJS_D) $(OBJS_B) $(OBJS_B_D)
				@$(MAKE) clean -s --no-print-directory -C $(LIBFT)
				@echo "$(YELLOW)Clean complete$(NC)"

fclean		:	clean
				@$(RM) $(NAME) $(NAME_B)
				@$(MAKE) fclean -s --no-print-directory -C $(LIBFT)
				@echo "$(YELLOW)Full clean complete$(NC)"

re			:	fclean all


valgrind		:
				@echo "\033[31m\033[1mNow launch make valgrindext in another console"
				@echo "Errors will appear here CTRL+C to stop\033[0m"
				valgrind-listener 4242

valgrindext		:
				valgrind $(VFLAGS) ./$(NAME)

#re_bonus	:	fclean bonus


