SHELL = /bin/sh

B&W = \033[0;0m
RED =  \033[0;31m
GREEN = \033[0;32m
PURPLE = \033[0;35m

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
	  get_params.c\
	  flags.c\
	  print_c.c\
	  print_s.c\
	  print_i_u_l_h.c\
	  print_p_x.c\
	  print_utils_num.c\
	  util_number.c

SRCDIR = ./

OBJS = $(SRC:.c=.o)
OBJDIR = ./objects/
OBJ = $(addprefix $(OBJDIR), $(OBJS))

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@cp $(LIBFTDIR)$(LIBFT) $(NAME)
	@$(AR) $(NAME) $(OBJ)
	@echo "$(PURPLE)  Library $(NAME) created  $(B&W)"

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER)
	@test -d $(OBJDIR) || mkdir $(OBJDIR)
	@$(CC) -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -c $< -o $@ $(FLAGS)
	@echo "$(GREEN)  Object file $@created  $(B&W)"

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

#test: $(NAME)
#	$(CC) main.c -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -L./ -lftprintf -o $@ $(FLAGS)

clean:
	@$(MAKE) clean -C $(LIBFTDIR)
	@$(RM) $(OBJDIR)

fclean:
	@$(MAKE) fclean -C $(LIBFTDIR)
	@$(RM) $(OBJDIR) $(NAME) test
	@echo "$(RED)  Library: $(NAME) deleted  $(B&W)"

re: fclean $(LIBFT) all

.PHONY: all clean fclean re test 