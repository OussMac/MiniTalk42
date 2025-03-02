FLAGS = -Wall -Wextra -Werror
CC = cc
HEADER = minitalk.h

# mandatory source files
SRV_SRC = server.c utils.c
CLNT_SRC = client.c utils.c

# mandatory object files
S_OBJ = $(SRV_SRC:.c=.o)
C_OBJ = $(CLNT_SRC:.c=.o)

# mandatory outputs (target files)
NAME = server
C_NAME = client

# bonus source files
B_SRV_SRC = bonus/server_bonus.c utils.c
B_CLNT_SRC = bonus/client_bonus.c utils.c

# bonus object files
B_S_OBJ = $(B_SRV_SRC:.c=.o)
B_C_OBJ = $(B_CLNT_SRC:.c=.o)

# bonus outputs (target files)
B_NAME = server_bonus
B_C_NAME = client_bonus

# ------------------------------------------------------------------- #

all: $(NAME) $(C_NAME)


$(NAME): $(S_OBJ) 
	$(CC) $^ -o $@

$(C_NAME): $(C_OBJ) 
	$(CC) $^ -o $@

# ------------- bonus rules ----------------------#
bonus: $(B_NAME) $(B_C_NAME)

$(B_NAME): $(B_S_OBJ) 
	$(CC) $^ -o $@

$(B_C_NAME): $(B_C_OBJ) 
	$(CC) $^ -o $@
# ------------- bonus rules ----------------------#

%.o: %.c $(HEADER)
	$(CC) -c $< -o $@

%.o: %.c $(HEADER)
	$(CC) -c $< -o $@

fclean: clean
	rm -f $(NAME) $(C_NAME) $(B_NAME) $(B_C_NAME)
clean:
	rm -f $(S_OBJ) $(C_OBJ) $(B_S_OBJ) $(B_C_OBJ)

re: fclean all

.PHONY: clean