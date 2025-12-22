# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: francesca <francesca@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/01 10:19:10 by francesca         #+#    #+#              #
#    Updated: 2025/12/18 09:30:53 by francesca        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# –––––––––––––––––––––––––––––
# Colors for Output
# –––––––––––––––––––––––––––––
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
RED			=	\033[0;31m
BLUE		=	\033[0;34m
MAGENTA		=	\033[0;35m
CYAN		=	\033[0;36m
RESET		=	\033[0m

#–––––––––––––––––––––––––––––
# Directories and Files
#–––––––––––––––––––––––––––––
SRCS_DIR	=	./src
OBJS_DIR	=	./obj
INC_DIR		=	./inc

# Trova automaticamente tutti i file .cpp nella directory src/
SRCS		:=	$(wildcard $(SRCS_DIR)/*.cpp)
# Trasforma src/xxx.cpp -> obj/xxx.o
OBJS		:=	$(patsubst $(SRCS_DIR)/%.cpp,$(OBJS_DIR)/%.o,$(SRCS))

#–––––––––––––––––––––––––––––
# Compiler and Flags
#–––––––––––––––––––––––––––––
NAME		=	Fixed
CXX			=	c++
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98 -I$(INC_DIR)
RM			=	rm -f

#–––––––––––––––––––––––––––––
# Rules
#–––––––––––––––––––––––––––––

# Default rule: Build the executable
all:			$(NAME)

# Create the object directory
$(OBJS_DIR):
			@echo "$(YELLOW)📁 Creating object directory...$(RESET)"
			@mkdir -p $(OBJS_DIR)

# Compile source files into object files
$(OBJS_DIR)/%.o: 	$(SRCS_DIR)/%.cpp | $(OBJS_DIR)
			@echo "$(BLUE)🔨 Compiling $<...$(RESET)"
			@$(CXX) $(CXXFLAGS) -c $< -o $@

# Link object files to create the executable
$(NAME):		$(OBJS)
				@echo "$(GREEN)🔗 Linking objects and creating $(NAME)...$(RESET)"
				@$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)
				@echo "$(RED)┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓$(RESET)"
				@echo "$(RED)┃  ███████╗██╗██╗  ██╗███████╗██████╗   ┃$(RESET)"
				@echo "$(RED)┃  ██╔════╝██║╚██╗██╔╝██╔════╝██╔══██╗  ┃$(RESET)"
				@echo "$(RED)┃  █████╗  ██║ ╚███╔╝ █████╗  ██║  ██║  ┃$(RESET)"
				@echo "$(RED)┃  ██╔══╝  ██║ ██╔██╗ ██╔══╝  ██║  ██║  ┃$(RESET)"
				@echo "$(RED)┃  ██║     ██║██╔╝ ██╗███████╗██████╔╝  ┃$(RESET)"
				@echo "$(RED)┃  ╚═╝     ╚═╝╚═╝  ╚═╝╚══════╝╚═════╝   ┃$(RESET)"
				@echo "$(RED)┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫$(RESET)"
				@echo "\n$(MAGENTA)╔══════════════════════════════════════════╗$(RESET)"
				@echo "$(MAGENTA)║                                          ║$(RESET)"
				@echo "$(MAGENTA)║$(RED)                  FIXED                   $(MAGENTA)║$(RESET)"
				@echo "$(MAGENTA)║                                          ║$(RESET)"
				@echo "$(MAGENTA)╚══════════════════════════════════════════╝$(RESET)"
				@echo ""
				@echo "$(CYAN)→ Executable: $(NAME)$(RESET)"
				@echo "$(CYAN)→ Run with: ./$(NAME)$(RESET)\n"

# Clean object files
clean:
				@echo "$(RED)🧹 Cleaning object files...$(RESET)"
				@$(RM) $(OBJS)
				@$(RM) -r $(OBJS_DIR)
				@echo "$(GREEN)✓ Clean complete!$(RESET)"

# Clean object files and remove the executable
fclean:			clean
				@echo "$(RED)🗑️  Removing executable...$(RESET)"
				@$(RM) $(NAME)
				@echo "$(GREEN)✓ Full clean complete!$(RESET)"

# Rebuild the project from scratch
re:				fclean all

# Show compilation info
info:
				@echo "$(CYAN)╔════════════════════════════════════════╗$(RESET)"
				@echo "$(CYAN)║         COMPILATION INFO               ║$(RESET)"
				@echo "$(CYAN)╚════════════════════════════════════════╝$(RESET)"
				@echo "$(YELLOW)Executable:$(RESET)  $(NAME)"
				@echo "$(YELLOW)Compiler:$(RESET)    $(CXX)"
				@echo "$(YELLOW)Flags:$(RESET)       $(CXXFLAGS)"
				@echo "$(YELLOW)Sources:$(RESET)     $(SRCS)"
				@echo "$(YELLOW)Objects:$(RESET)     $(OBJS)"
				@echo ""

#–––––––––––––––––––––––––––––
# Phony Targets
#–––––––––––––––––––––––––––––
.PHONY:			all clean fclean re info
