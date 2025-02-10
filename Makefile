FLAGS = -Wall -Wextra -Werror
CC = cc
HEADER = minitalk.h
SRV_SRC = server.c utils.c
CLNT_SRC = client.c utils.c

S_OBJ = $(SRV_SRC:.c=.o)
C_OBJ = $(CLNT_SRC:.c=.o)

NAME = server
C_NAME = client

all: $(NAME) $(C_NAME)

$(NAME): $(S_OBJ) 
	$(CC) $^ -o $@

$(C_NAME): $(C_OBJ) 
	$(CC) $^ -o $@

%.o: %.c $(HEADER)
	$(CC) -c $< -o $@

fclean: clean
	rm -f $(NAME) $(C_NAME)
clean:
	rm -f $(S_OBJ) $(C_OBJ) 

re: fclean all

.PHONY: clean