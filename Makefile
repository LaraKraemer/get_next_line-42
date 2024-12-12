CC          = cc 

CFLAGS      = -Wall -Wextra -Werror 

NAME        = getnextline.a

SRC         = \
				ft_get_next_line.c \
				ft_get_next_line_utils.c \

# Object files - .c files
OBJ         = $(SRC:.c=.o)

# Default target
all: $(NAME)  $(TEST_EXEC)

# Create library  from object files
$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ) 

# Compile src file in out files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean: Remove .out files 
clean:
	rm -f $(OBJ)  $(TEST_OBJ)

# Full clean: Remove .out files & libary 
fclean:	clean
	rm -f $(NAME)  $(TEST_EXEC)

# Rebuild all
re:	fclean all

# Phony targets
.PHONY: all clean fclean re test