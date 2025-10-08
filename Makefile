MAKE 			= make --no-print-directory -C


#==============================================================================#
#                                     NAMES                                    #
#==============================================================================#

NAME 			= philo

_SUCCESS 		= [$(B)$(GRN)SUCCESS$(D)]

#==============================================================================#
#                                    PATHS                                     #
#==============================================================================#

SRC_PATH		= src
INC_PATH		= include
BUILD_PATH		= .build

FILES			= dinner.c getter_setter.c init.c main.c parser.c philo.c safe.c utils.c

SRC				= $(addprefix $(SRC_PATH)/, $(FILES))
OBJS			= $(SRC:$(SRC_PATH)/%.c=$(BUILD_PATH)/%.o)

HEADERS			= $(INC_PATH)/philosophers.h

#==============================================================================#
#                              COMPILER & FLAGS                                #
#==============================================================================#

CC				= cc

CFLAGS 			= -Wall -Wextra -Werror -pthread -g

INC				= -I $(INC_PATH)

RM				= rm -rf
AR				= ar rcs
MKDIR_P			= mkdir -p

#==============================================================================#
#                                  RULES                                       #
#==============================================================================#


all: $(BUILD_PATH) $(NAME)	## Compile

$(NAME): $(BUILD_PATH) $(LIBFT_ARC) $(OBJS)	## Compile
	@echo "  $(B)$(GOLD)Compiling$(SILV)$(NAME)$(GOLD)mandatory version$(D)"
	@$(CC) $(CFLAGS) $(OBJS) $(INC) -o $(NAME)
	@echo "$(D)  $(B)$(GOLD)Executable $(SILV)$(NAME)$(GOLD) created successfully!$(D): $(_SUCCESS) ✔︎ 📂"
	@clear
	@printf "\n"
	@printf "$(GOLD)\n"
	@printf "	██████╗ ██╗  ██╗██╗██╗      ██████╗ \n"
	@printf "	██╔══██╗██║  ██║██║██║     ██╔═══██╗\n"
	@printf "	██████╔╝███████║██║██║     ██║   ██║\n"
	@printf "	██╔═══╝ ██╔══██║██║██║     ██║   ██║\n"
	@printf "	██║     ██║  ██║██║███████╗╚██████╔╝\n"
	@printf "	╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ \n"
	@printf "$(D)\n"
	@printf "\n"
	@printf "\n"

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(BUILD_PATH):
	@$(MKDIR_P) $(BUILD_PATH)
	@echo "  $(B)$(GOLD)Creating $(SILV)$(BUILD_PATH)$(GOLD) folder :$(D)$(_SUCCESS) ✔︎ 📂"

clean:				## Remove object files
	@echo "  $(B)$(GOLD)Cleaning object files $(D)"
	@$(RM) $(BUILD_PATH); 
	@echo "  $(B)$(GOLD)Removing $(SILV)$(BUILD_PATH)$(GOLD) folder & files$(D): $(_SUCCESS) 🧹";

fclean: clean			## Remove executable
	@echo "  $(B)$(GOLD)Cleaning executables $(D)"
	@$(RM) $(NAME);
	@$(RM) 42-philosophers-tester;
	@echo "  $(B)$(GOLD)Removing $(SILV)$(NAME)$(GOLD) file: $(D) $(_SUCCESS) 🧹";

re: fclean all	## Purge & Recompile

tester: re
	@git clone https://github.com/dantonik/42-philosophers-tester.git
	@cd 42-philosophers-tester && ./test.sh

.PHONY: all clean fclean re tester

#==============================================================================#
#                                  UTILS                                       #
#==============================================================================#

# Basic colors
B  		= $(shell tput bold)
RED		= $(shell tput setaf 1)
GRN		= $(shell tput setaf 2)
BLU		= $(shell tput setaf 4)

# Extended colors used in your makefile
GOLD    = $(shell tput setaf 220)
SILV    = $(shell tput setaf 250)

# Reset
D       = $(shell tput sgr0)
