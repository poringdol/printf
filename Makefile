SHELL = /bin/sh

CC = clang
FLAGS = -Wall -Werror -Wextra -ggdb
AR = ar rs
RM = rm -rf

LIBFT = libft.a
LIBFTDIR = ./libft/
LIBFTHEADER = libft.h
LIBFTHEADERDIR = ./libft/includes/

NAME = libftprintf.a
HEADER = libftprintf.h
HEADERDIR = ./

SRC = ft_printf.c\
	  check_params.c\
	  flags.c\
	  print_char.c\
	  print_string.c\
	  print_number.c

SRCDIR = ./

OBJS = $(SRC:.c=.o)
OBJDIR = ./objects/
OBJ = $(addprefix $(OBJDIR), $(OBJS))

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	cp $(LIBFTDIR)$(LIBFT) $(NAME)
	$(AR) $(NAME) $(OBJ)

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER)
	test -d $(OBJDIR) || mkdir $(OBJDIR)
	$(CC) -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -c $< -o $@ $(FLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

test: $(NAME)
	$(CC) main.c -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -L./ -lftprintf -o $@ $(FLAGS)

clean:
	$(MAKE) clean -C $(LIBFTDIR)
	$(RM) $(OBJDIR)

fclean:
	$(MAKE) fclean -C $(LIBFTDIR)
	$(RM) $(OBJDIR) $(NAME) test

re: fclean $(LIBFT) all

.PHONY: all clean fclean re test 