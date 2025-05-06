.PHONY		: 	all clean fclean re

NAME		=	libft_ex.a

FT_PRINTF 	=	ft_printf/
FT_PRINTF_FD=	ft_printf_fd/
GNL 		=	get_next_line/
FT 			=	libft/

LIBFTPRINTF 	=	$(FT_PRINTF)libftprintf.a
LIBFTPRINTF_FD	=	$(FT_PRINTF_FD)libftprintf_fd.a
LIBGNL			=	$(GNL)libgnl.a
LIBFT			=	$(FT)libft.a

RM			=	rm -rf
LIBC		=	ar rc
LIBR		= 	ranlib

all		: $(NAME)

$(NAME)	: $(LIBFTPRINTF) $(LIBFTPRINTF_FD) $(LIBGNL) $(LIBFT)
		cp $(LIBFTPRINTF) .
		cp $(LIBFTPRINTF_FD) .
		cp $(LIBGNL) .
		cp $(LIBFT) .
		ar -x libftprintf.a
		ar -x libftprintf_fd.a
		ar -x libgnl.a
		ar -x libft.a
		$(LIBC) $(NAME) *.o
		$(LIBR) $(NAME)

$(LIBFTPRINTF_FD)	:
		$(MAKE) -C $(FT_PRINTF_FD)

$(LIBFTPRINTF)	:
		$(MAKE) -C $(FT_PRINTF)

$(LIBGNL)	:
		$(MAKE) -C $(GNL)

$(LIBFT)	:
		$(MAKE) -C $(FT)

clean	:
		$(MAKE) -C $(FT_PRINTF) clean
		$(MAKE) -C $(FT_PRINTF_FD) clean
		$(MAKE) -C $(GNL) clean
		$(MAKE) -C $(FT) clean
		$(RM) libftprintf.a libftprintf_fd.a libgnl.a libft.a
		$(RM) *.o
		$(RM) $(LIBFTPRINTF) $(LIBFTPRINTF_FD) $(LIBGNL) $(LIBFT)

fclean	: clean
		$(MAKE) -C $(FT_PRINTF) fclean
		$(MAKE) -C $(FT_PRINTF_FD) fclean
		$(MAKE) -C $(GNL) fclean
		$(MAKE) -C $(FT) fclean
		$(RM) $(NAME)

re		: fclean all
