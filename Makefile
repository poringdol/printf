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
	  print_o.c\
	  print_utils_num.c\
	  util_number.c

SRCDIR = ./

OBJS = $(SRC:.c=.o)
OBJDIR = ./objects/
OBJ = $(addprefix $(OBJDIR), $(OBJS))

DEP = $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@cp $(LIBFTDIR)$(LIBFT) $(NAME)
	@$(AR) $(NAME) $(OBJ)
	@echo "$(PURPLE)  Library $(NAME) created  $(B&W)"

-include $(DEP)

bonus: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@test -d $(OBJDIR) || mkdir $(OBJDIR)
	@$(CC) -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -MMD -c $< -o $@ $(FLAGS)
	@echo "$(GREEN)  Object file$(PURPLE) $@ $(GREEN)created  $(B&W)"

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

#test:
#	$(CC) main.c -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -L./ -lftprintf -o $@ -ggdb
#c:
#	@$(CC) main_c.c -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -ggdb -w -L./ -lftprintf -o $@ && ./c
#s:
#	@$(CC) main_s.c -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -ggdb -w -L./ -lftprintf -o $@ && ./s
#i:
#	@$(CC) main_i.c -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -ggdb -w -L./ -lftprintf -o $@ && ./i
#d:
#	@$(CC) main_d.c -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -ggdb -w -L./ -lftprintf -o $@ && ./d
#u:
#	@$(CC) main_u.c -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -ggdb -w -L./ -lftprintf -o $@ && ./u
#x:
#	@$(CC) main_x.c -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -ggdb -w -L./ -lftprintf -o $@ && ./x
#bigx:
#	@$(CC) main_bigx.c -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -ggdb -w -L./ -lftprintf -o $@ && ./bigx
#p:
#	@$(CC) main_p.c -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -ggdb -w -L./ -lftprintf -o $@ && ./p
#wf:
#	@$(CC) main_without_flags.c -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -ggdb -w -L./ -lftprintf -o $@ && ./wf
#tests: c s d i u p wf x bigx

clean:
	@$(MAKE) clean -C $(LIBFTDIR)
	@$(RM) $(OBJDIR)

fclean:
	@$(MAKE) fclean -C $(LIBFTDIR)
	@$(RM) $(OBJDIR) $(NAME) test
	@echo "$(RED)  Library $(NAME) deleted  $(B&W)"

re: fclean $(LIBFT) all

.PHONY: all bonus clean fclean re test
