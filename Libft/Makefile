.PHONY		: 	all clean fclean re

NAME		=	libft_ex.a

FT_PRINTF 	=	ft_printf/
GNL 		=	get_next_line/
FT 			=	libft/

LIBFTPRINTF =	$(FT_PRINTF)libftprintf.a
LIBGNL		=	$(GNL)libgnl.a
LIBFT		=	$(FT)libft.a

RM			=	rm -rf
LIBC		=	ar rc
LIBR		= 	ranlib

all		: $(NAME)

$(NAME)	: $(LIBFTPRINTF) $(LIBGNL) $(LIBFT)
		cp $(LIBFTPRINTF) .
		cp $(LIBGNL) .
		cp $(LIBFT) .
		ar -x libftprintf.a
		ar -x libgnl.a
		ar -x libft.a
		$(LIBC) $(NAME) *.o
		$(LIBR) $(NAME)

$(LIBFTPRINTF)	:
		$(MAKE) -C $(FT_PRINTF)

$(LIBGNL)	:
		$(MAKE) -C $(GNL)

$(LIBFT)	:
		$(MAKE) -C $(FT)

clean	:
		$(MAKE) -C $(FT_PRINTF) clean
		$(MAKE) -C $(GNL) clean
		$(MAKE) -C $(FT) clean
		$(RM) libftprintf.a libgnl.a libft.a
		$(RM) *.o
		$(RM) $(LIBFTPRINTF) $(LIBGNL) $(LIBFT)

fclean	: clean
		$(MAKE) -C $(FT_PRINTF) fclean
		$(MAKE) -C $(GNL) fclean
		$(MAKE) -C $(FT) fclean
		$(RM) $(NAME)

re		: fclean all
