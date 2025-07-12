MAKE 			= make --no-print-directory -C


#==============================================================================#
#                                     NAMES                                    #
#==============================================================================#

NAME 			= philo

### Message Vars
_SUCCESS 		= [$(B)$(GRN)SUCCESS$(D)]
_INFO 			= [$(B)$(BLU)INFO$(D)]
_NORM 			= [$(B)$(MAG)Norminette$(D)]
_NORM_SUCCESS 	= $(B)$(GRN)=== OK:$(D)
_NORM_INFO 		= $(B)$(BLU)File no:$(D)
_NORM_ERR 		= $(B)$(RED)=== KO:$(D)
_SEP 			= =====================

#==============================================================================#
#                                    PATHS                                     #
#==============================================================================#

SRC_PATH		= src
INC_PATH		= include
BUILD_PATH		= .build

FILES			= dinner.c getters_setters.c init.c main.c monitor.c parsing.c safe.c syncro_utils.c utils.c write.c

SRC				= $(addprefix $(SRC_PATH)/, $(FILES))
OBJS			= $(SRC:$(SRC_PATH)/%.c=$(BUILD_PATH)/%.o)

HEADERS			= $(INC_PATH)/philo.h

#==============================================================================#
#                              COMPILER & FLAGS                                #
#==============================================================================#

CC				= cc

CFLAGS			= -Wall -Wextra -Werror -g

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
	@printf "\n"
	@printf "          ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n"
	@printf "          ┃$(BLINK)$(B)$(GOLD)𝐏 𝐡 𝐢 𝐥 𝐨 𝐬 𝐨 𝐩 𝐡 𝐞 𝐫 𝐬$(D)  ┃\n"
	@printf "     ┏━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━┓\n"
	@printf "     ┃ Program has compiled ${GRN}${BOLD}SUCCESSFULLY! ${D}┃\n"
	@printf "     ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n"
	@printf "\n"
	@printf "\n"
	
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(BUILD_PATH):
	@$(MKDIR_P) $(BUILD_PATH)
	@echo "  $(B)$(GOLD)Creating$(SILV)$(BUILD_PATH)$(GOLD)folder :$(D)$(_SUCCESS) ✔︎ 📂"

clean:				## Remove object files
	@echo "  $(B)$(GOLD)Cleaning object files $(D)"
	@$(RM) $(BUILD_PATH); 
	@echo "  $(B)$(GOLD)Removing $(SILV)$(BUILD_PATH)$(GOLD) folder & files$(D): $(_SUCCESS) 🧹";
	@printf "\n"

fclean: clean			## Remove executable
	@echo "  $(B)$(GOLD)Cleaning executables $(D)"
	@$(RM) $(NAME);
	@echo "  $(B)$(GOLD)Removing $(SILV)$(NAME)$(GOLD) file: $(D) $(_SUCCESS) 🧹";
	@printf "\n"

re: fclean all	## Purge & Recompile

.PHONY: all clean fclean re

#==============================================================================#
#                                  UTILS                                       #
#==============================================================================#

# Colors
#
# Run the following command to get list of available colors
# bash -c 'for c in {0..255}; do tput setaf $c; tput setaf $c | cat -v; echo =$c; done'
#
B  		= $(shell tput bold)
BLA		= $(shell tput setaf 0)
RED		= $(shell tput setaf 1)
GRN		= $(shell tput setaf 2)
YEL		= $(shell tput setaf 3)
BLU		= $(shell tput setaf 4)
MAG		= $(shell tput setaf 5)
CYA		= $(shell tput setaf 6)
WHI		= $(shell tput setaf 7)
GRE		= $(shell tput setaf 8)
BRED 	= $(shell tput setaf 9)
BGRN	= $(shell tput setaf 10)
BYEL	= $(shell tput setaf 11)
BBLU	= $(shell tput setaf 12)
BMAG	= $(shell tput setaf 13)
BCYA	= $(shell tput setaf 14)
BWHI	= $(shell tput setaf 15)

# Extended colors
ORG     = $(shell tput setaf 208)  # Orange
PINK    = $(shell tput setaf 205)  # Pink
PURP    = $(shell tput setaf 93)   # Purple
LIME    = $(shell tput setaf 154)  # Lime
AQUA    = $(shell tput setaf 87)   # Aqua
GOLD    = $(shell tput setaf 220)  # Gold
SILV    = $(shell tput setaf 250)  # Silver
NAVY    = $(shell tput setaf 17)   # Navy Blue
TEAL    = $(shell tput setaf 23)   # Teal
WINE    = $(shell tput setaf 52)   # Wine Red

# Reset and special
D       = $(shell tput sgr0)
BEL     = $(shell tput bel)
CLR     = $(shell tput el 1)

#blink
BLINK = $(shell tput blink)