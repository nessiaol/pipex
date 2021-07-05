NAME = pipex

HPATH = -Iincludes

CC = gcc

FLAGS = -Wall -Wextra -Werror

DIR_SRCS = srcs
DIR_MINILIBFT= minilibft
DIR_PIPEX = pipex
DIR_OBJS = objs

MINILIBFT_PATH = $(addprefix $(DIR_SRCS)/, $(DIR_MINILIBFT))
PIPEX_PATH = $(addprefix $(DIR_SRCS)/, $(DIR_PIPEX))


MINILIBFT_FILES =	ft_putstr_fd.c \
					ft_strcat.c \
				 	ft_strncmp.c \
					ft_strlen.c \
					ft_putchar_fd.c \

PIPEX_FILES	=	pipex.c \
				utils.c \

SRCS_MINILIBFT = $(addprefix $(MINILIBFT_PATH)/, $(MINILIBFT_FILES))
SRCS_PIPEX = $(addprefix $(PIPEX_PATH)/, $(PIPEX_FILES))
SRCS = $(SRCS_MINILIBFT) $(SRCS_PIPEX)

OBJS_FILES = $(PIPEX_FILES:.c=.o) $(MINILIBFT_FILES:.c=.o)
OBJS = $(addprefix $(DIR_OBJS)/, $(OBJS_FILES))

all: $(NAME)

$(OBJS) : $(SRCS)
	-@$(CC) $(FLAGS) $(SRCS) -c
	mv *.o $(DIR_OBJS)

$(NAME) : $(OBJS)
	@echo Compiling: $(NAME)
	@$(CC) $(FLAGS) $(HPATH) $(OBJS) -o $(NAME)
	@echo Compiled successfully!

clean:
	@echo Deleting objects files...
	@rm -f $(OBJS)
	@echo Deleting done!

fclean: clean
	@echo Deleting $(NAME)...
	@rm -rf $(NAME)
	@rm -rf *.o
	@echo Deleting done!

re: fclean all

.PHONY: all clean fclean re