SRC =		src/main.c 				\

SRC_B =		src_bonus/main_bonus.c	\

NAME	=	cub3D

NAME_B	=	so_long_bonus

OBJ		=	$(SRC:%.c=%.o)

OBJ_B	=	$(SRC_B:%.c=%_b.o)

CC		=	gcc

RM		=	rm -f

CFLAGS	=	-Wall -Wextra -Werror

FM		=	-framework OpenGL -framework AppKit

LIBS	=	-Llibft -lft -Lmlx -lmlx

%.o:		%.c
			$(CC) $(CFLAGS) -Imlx -c $< -o $@

%_b.o: 		%.c
			$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(NAME):	$(OBJ)
			@make -C libft
			@make -C mlx
			$(CC) $(OBJ) $(LIBS) $(FM) -o $(NAME)

$(NAME_B):	$(OBJ_B)
			@make -C libft
			@make -C mlx
			$(CC) $(OBJ_B) $(LIBS) $(FM) -o $(NAME_B)

all:		$(NAME)

run:		$(NAME)
			./$(NAME)

bonus:		$(NAME_B)

clean:
			@make -C libft clean
			@make -C mlx clean
			$(RM) $(OBJ) $(OBJ_B)

fclean:		clean
			$(RM) $(NAME) $(NAME_B)

re:			fclean all

.PHONY:		all clean fclean re
