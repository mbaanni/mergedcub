
OS = $(shell uname)
LIBMLX = ./MLX
LIBS = $(LIBMLX)/libmlx42.a -ldl -lglfw -L"$(HOME)/.brew/Cellar/glfw/3.3.8/lib" -pthread -lm -framework Cocoa -framework OpenGL -framework IOKit
CFLAG= -O3 -Ofast -flto   -Wall -Wextra -Werror
HEADER = -I ./includes -I $(LIBMLX)/include
CC= cc
SRC= main.c event.c maps.c calculation.c draw_mini_map.c dor.c miniplayer.c calculation_1.c
PRC= check_elemnts.c linkedlist_utils.c map_parsing.c singelton_object.c valid_chars.c check_dirs.c check_map.c errors.c map_check_utils.c
NAME= Cub3d
BNAME= Cub3d_bonus
DIR_SRC = src/
DIR_PRC = parser/
DIR_OBG = obj/

BSRC= $(addprefix $(DIR_SRC), $(SRC))
BSRC+= $(addprefix $(DIR_PRC), $(PRC))

OBG= $(addprefix $(DIR_OBG), $(SRC:.c=.o))
OBG+= $(addprefix $(DIR_OBG), $(PRC:.c=.o))
B = 0
all : $(NAME)

bonus : $(BNAME)

$(NAME) : $(OBG)
	@make -C libft > /dev/null
	$(CC) $(CFLAG) $(OBG) $(LIBS) libft/libft.a $(HEADER) -o $(NAME)
$(BNAME) :
	@make -C libft > /dev/null
	$(CC) $(CFLAG) -D BONUS=1 $(BSRC) $(LIBS) libft/libft.a $(HEADER) -o $(BNAME)

$(DIR_OBG)%.o: $(DIR_SRC)%.c includes/Cub3D.h
	@mkdir -p $(DIR_OBG)
	@$(CC) $(CFLAG) $(HEADER) -c $< -o $@
$(DIR_OBG)%.o: $(DIR_PRC)%.c includes/Cub3D.h
	@mkdir -p $(DIR_OBG)
	@$(CC) $(CFLAG) $(HEADER) -c $< -o $@
clean :
	@make -C libft clean
	@rm -rf $(DIR_OBG)
fclean : clean
	@make -C libft fclean
	@rm -rf $(NAME)
	@rm -rf $(BNAME)

re : fclean all

.PHONY: all clean fclean re bonus




