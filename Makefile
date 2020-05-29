SHELL = /bin/sh

B&W = \033[0;0m
RED =  \033[0;31m
GREEN = \033[0;32m
PURPLE = \033[0;35m

CC = gcc
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
	  print_i.c\
	  print_u.c\
	  print_p_x.c\
	  print_o.c\
	  print_f.c\
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
	@echo "$(GREEN)  Object file $(PURPLE)$@ $(GREEN)created  $(B&W)"

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

############################# TEST ###############################
test:
	@$(CC) ./test/main.c -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -ggdb -w -L./ -lftprintf -o ./test/$@ && ./test/test
c:
	@$(CC) ./test/main_c.c -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -ggdb -w -L./ -lftprintf -o ./test/$@ && ./test/c
s:
	@$(CC) ./test/main_s.c -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -ggdb -w -L./ -lftprintf -o ./test/$@ && ./test/s
i:
	@$(CC) ./test/main_i.c -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -ggdb -w -L./ -lftprintf -o ./test/$@ && ./test/i
d:
	@$(CC) ./test/main_d.c -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -ggdb -w -L./ -lftprintf -o ./test/$@ && ./test/d
u:
	@$(CC) ./test/main_u.c -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -ggdb -w -L./ -lftprintf -o ./test/$@ && ./test/u
lu:
	@$(CC) ./test/main_lu.c -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -ggdb -w -L./ -lftprintf -o ./test/$@ && ./test/lu
x:
	@$(CC) ./test/main_x.c -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -ggdb -w -L./ -lftprintf -o ./test/$@ && ./test/x
bigx:
	@$(CC) ./test/main_bigx.c -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -ggdb -w -L./ -lftprintf -o ./test/$@ && ./test/bigx
p:
	@$(CC) ./test/main_p.c -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -ggdb -w -L./ -lftprintf -o ./test/$@ && ./test/p
wf:
	@$(CC) ./test/main_without_flags.c -I$(HEADERDIR) -I$(LIBFTHEADERDIR) -ggdb -w -L./ -lftprintf -o ./test/$@ && ./test/wf
tests: all c s d i u p wf x bigx lu
###################################################################

clean:
	@$(MAKE) clean -C $(LIBFTDIR)
	@$(RM) $(OBJDIR)

fclean:
	@$(MAKE) fclean -C $(LIBFTDIR)
	@$(RM) $(OBJDIR) $(NAME) ./tests
	@echo "$(RED)  Library $(NAME) deleted  $(B&W)"

re: fclean $(LIBFT) all

.PHONY: all bonus clean fclean re test c d i p s u wf x tests lu
