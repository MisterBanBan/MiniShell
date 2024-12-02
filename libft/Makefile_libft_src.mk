# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile_libft_src.mk                              :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/07 11:30:56 by nkermani          #+#    #+#              #
#    Updated: 2024/01/13 00:02:54 by nkermani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** # # START #
# **************************************************************************** #
# **************************************************************************** # # NAME & DIRS #
NAME        			:= 	libft.a
SRC_DIR 				:= 	src
BUILD_DIR 				:= 	.build
DEPS_DIR 				:= 	.deps
# **************************************************************************** # # PATHS #
# **************************************************************************** # # LIBFT/FT_IS #
LIBFT_FT_IS				:= 	$(SRC_DIR)/ft_is/ft_isalnum.c						\
						   	$(SRC_DIR)/ft_is/ft_isalpha.c						\
						   	$(SRC_DIR)/ft_is/ft_isascii.c						\
						   	$(SRC_DIR)/ft_is/ft_isdigit.c						\
						   	$(SRC_DIR)/ft_is/ft_isprint.c
# **************************************************************************** # # LIBFT/FT_LST #
LIBFT_FT_LST			:= 	$(SRC_DIR)/ft_lst/ft_lstadd_back.c					\
						   	$(SRC_DIR)/ft_lst/ft_lstadd_front.c					\
						   	$(SRC_DIR)/ft_lst/ft_lstclear.c						\
						   	$(SRC_DIR)/ft_lst/ft_lstdelone.c					\
						   	$(SRC_DIR)/ft_lst/ft_lstiter.c						\
						   	$(SRC_DIR)/ft_lst/ft_lstlast.c						\
						   	$(SRC_DIR)/ft_lst/ft_lstmap.c						\
						  	$(SRC_DIR)/ft_lst/ft_lstnew.c						\
						  	$(SRC_DIR)/ft_lst/ft_lstsize.c
# **************************************************************************** # # LIBFT/FT_MEM #
LIBFT_FT_MEM			:= 	$(SRC_DIR)/ft_mem/ft_bzero.c						\
							$(SRC_DIR)/ft_mem/ft_calloc.c						\
							$(SRC_DIR)/ft_mem/ft_memchr.c						\
							$(SRC_DIR)/ft_mem/ft_memcmp.c						\
							$(SRC_DIR)/ft_mem/ft_memcpy.c						\
							$(SRC_DIR)/ft_mem/ft_memmove.c						\
							$(SRC_DIR)/ft_mem/ft_memset.c
# **************************************************************************** # # LIBFT/FT_PRINTF #
LIBFT_FT_PRINTF 		:= 	$(SRC_DIR)/ft_printf/ft_printf.c					\
							$(SRC_DIR)/ft_printf/ft_printf_utils.c
# **************************************************************************** # # LIBFT/FT_PRINTF_FD #
LIBFT_FT_PRINTF_FD 		:= 	$(SRC_DIR)/ft_printf_fd/ft_printf_fd.c				\
							$(SRC_DIR)/ft_printf_fd/ft_printf_utils_fd.c
# **************************************************************************** # # LIBFT/FT_PUT #
LIBFT_FT_PUT			:= 	$(SRC_DIR)/ft_put/ft_putchar_fd.c					\
							$(SRC_DIR)/ft_put/ft_putendl_fd.c					\
							$(SRC_DIR)/ft_put/ft_putnbr_fd.c					\
							$(SRC_DIR)/ft_put/ft_putstr_fd.c
# **************************************************************************** # # LIBFT/FT_STR #
LIBFT_FT_STR			:= 	$(SRC_DIR)/ft_str/ft_split.c 						\
							$(SRC_DIR)/ft_str/ft_strchr.c 						\
							$(SRC_DIR)/ft_str/ft_strcmp.c 						\
							$(SRC_DIR)/ft_str/ft_strdup.c 						\
							$(SRC_DIR)/ft_str/ft_striteri.c 					\
							$(SRC_DIR)/ft_str/ft_strjoin.c 						\
							$(SRC_DIR)/ft_str/ft_strlcat.c 						\
							$(SRC_DIR)/ft_str/ft_strlcpy.c 						\
							$(SRC_DIR)/ft_str/ft_strlen.c 						\
							$(SRC_DIR)/ft_str/ft_strmapi.c 						\
							$(SRC_DIR)/ft_str/ft_strncmp.c 						\
							$(SRC_DIR)/ft_str/ft_strnstr.c 						\
							$(SRC_DIR)/ft_str/ft_strrchr.c 						\
							$(SRC_DIR)/ft_str/ft_strtrim.c 						\
							$(SRC_DIR)/ft_str/ft_substr.c
# **************************************************************************** # # LIBFT/FT_TO #
LIBFT_FT_TO				:= 	$(SRC_DIR)/ft_to/ft_atoi.c	 						\
							$(SRC_DIR)/ft_to/ft_itoa.c	 						\
							$(SRC_DIR)/ft_to/ft_tolower.c	 					\
							$(SRC_DIR)/ft_to/ft_toupper.c
# **************************************************************************** # # LIBFT/GET_NEXT_LINE #
LIBFT_GET_NEXT_LINE		:= 	$(SRC_DIR)/get_next_line/get_next_line.c	 		\
							$(SRC_DIR)/get_next_line/get_next_line_utils.c
# **************************************************************************** # # SRCS #
SRCS 					:= 	$(LIBFT_FT_IS)										\
							$(LIBFT_FT_LST)										\
							$(LIBFT_FT_MEM)										\
							$(LIBFT_FT_PRINTF)									\
							$(LIBFT_FT_PRINTF_FD)								\
							$(LIBFT_FT_PUT)										\
							$(LIBFT_FT_STR)										\
							$(LIBFT_FT_TO)										\
							$(LIBFT_GET_NEXT_LINE)
OBJS 					:= $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS 					:= $(patsubst $(SRC_DIR)/%.c,$(DEPS_DIR)/%.d,$(SRCS))
# **************************************************************************** # # CC & FLAGS #
CC          			:= cc
CFLAGS      			:= -Wall -Wextra -Werror
CPPFLAGS    			:= -MMD -MP -I include
AR          			:= ar
ARFLAGS     			:= -rcs
# **************************************************************************** # # UTILS #
RM          			:= rm -f
# **************************************************************************** # # COLORS #
SUCCESS_COLOR 			:= \033[92m
RESET_COLOR 			:= \033[0m
# **************************************************************************** # # CUSTOM MSG #
COMPILING_MSG  			:= $(SUCCESS_COLOR)Compiling... $(RESET_COLOR)
BUILD_DONE_MSG  		:= $(SUCCESS_COLOR)Libft got built!$(RESET_COLOR)
CLEAN_OBJ_MSG   		:= $(SUCCESS_COLOR)Cleaning objects...$(RESET_COLOR)
CLEAN_ARCHIVE_MSG 		:= $(SUCCESS_COLOR)Cleaning archive...$(RESET_COLOR)
NAME_BUILT_MSG  		:= $(SUCCESS_COLOR)$(NAME) archive already built successfully.$(RESET_COLOR)
CLEAR_LINE_SEQ			:= \r\033[K
SUCCESSFUL_BUILD		:= 0
# **************************************************************************** # 