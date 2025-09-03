# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/02 23:04:36 by abendrih          #+#    #+#              #
#    Updated: 2025/09/03 04:51:11 by abendrih         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ┌─────────────────────────────┐
# │          PROJET 42          │
# └─────────────────────────────┘
NAME        = philo

# ┌─────────────────────────────┐
# │         REPERTOIRES         │
# └─────────────────────────────┘
SRC_DIR     = src
PARSING_DIR = parsing
UTILS_DIR = utils
INCLUDE_DIR = include

# ┌─────────────────────────────┐
# │           SOURCES           │
# └─────────────────────────────┘
SRC         = \
	$(SRC_DIR)/main.c \
	$(PARSING_DIR)/parsing.c \
	$(UTILS_DIR)/ft_atoi.c \
	$(UTILS_DIR)/ft_error.c \
	$(UTILS_DIR)/ft_split.c \

OBJ         = $(SRC:.c=.o)

# ┌─────────────────────────────┐
# │         COMPILATION         │
# └─────────────────────────────┘
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g3
CPPFLAGS    = -I$(INCLUDE_DIR)
LDFLAGS     = -pthread

# ┌─────────────────────────────┐
# │           COULEURS          │
# └─────────────────────────────┘
RESET       = \033[0m
GREEN       = \033[0;32m
YELLOW      = \033[0;33m
RED         = \033[0;31m
CYAN        = \033[0;36m
MATRIX_GREEN= \033[38;5;46m

DINNER_BOOT = "\n\
$(MATRIX_GREEN)\
> Initializing dining protocol...\n\
> Mutex array online [OK]\n\
> Thread spawner armed [OK]\n\
> Binary path secured: $(NAME)\n\
> Philosophers ready to dine.\n\
> [▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓] 100%\n\
> SYSTEM READY.\n\
$(RESET)"

DINNER_CLEAN = "\n\
\033[38;5;93m╔════════════════════════════════════╗\n\
\033[38;5;93m║ \033[38;5;51mReleasing forks...\033[0m                 \033[38;5;93m║\n\
\033[38;5;93m║ \033[38;5;51m[▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓] \033[38;5;198m100%%\033[0m         \033[38;5;93m║\n\
\033[38;5;93m║ \033[38;5;201mAll objects neutralized\033[0m            \033[38;5;93m║\n\
\033[38;5;93m║ \033[38;5;51mPhilosophers dismissed\033[0m             \033[38;5;93m║\n\
\033[38;5;93m╚════════════════════════════════════╝\n\
$(RESET)"

# ┌─────────────────────────────┐
# │          COMMANDES          │
# └─────────────────────────────┘
all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)
	@echo $(DINNER_BOOT)

%.o: %.c
	@echo "$(CYAN)Compiling$(RESET) $<"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	@echo "$(CYAN)Cleaning object files...$(RESET)"
	@rm -f $(OBJ)
	@echo $(DINNER_CLEAN)

fclean: clean
	@echo "$(RED)Removing binary:$(RESET) $(NAME)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
