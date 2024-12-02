# **************************************************************************** # # NAME & DIRS #
NAME        			:= minishell
SRC_DIR 				:= src
BUILD_DIR 				:= .build
DEPS_DIR 				:= .deps
# **************************************************************************** # # PATHS #
SOURCES 				:= 	$(SRC_DIR)/main.c									\
							$(SRC_DIR)/main_blocks.c							\
							$(SRC_DIR)/builtins/builtin_exe.c					\
							$(SRC_DIR)/builtins/builtins_get_args.c				\
							$(SRC_DIR)/builtins/cd.c							\
							$(SRC_DIR)/builtins/cd_canon.c						\
							$(SRC_DIR)/builtins/cd_utils.c						\
							$(SRC_DIR)/builtins/cd_cases.c						\
							$(SRC_DIR)/builtins/echo.c							\
							$(SRC_DIR)/builtins/env.c							\
							$(SRC_DIR)/builtins/exit.c							\
							$(SRC_DIR)/builtins/exit_fork.c						\
							$(SRC_DIR)/builtins/export_append.c					\
							$(SRC_DIR)/builtins/export_check.c					\
							$(SRC_DIR)/builtins/export_no_args.c				\
							$(SRC_DIR)/builtins/export_replace.c				\
							$(SRC_DIR)/builtins/export_valid.c					\
							$(SRC_DIR)/builtins/export.c						\
							$(SRC_DIR)/builtins/pwd.c							\
							$(SRC_DIR)/builtins/unset.c							\
							$(SRC_DIR)/exec/cmd_builtins.c						\
							$(SRC_DIR)/exec/close_files.c						\
							$(SRC_DIR)/exec/cmd_pipe.c							\
							$(SRC_DIR)/exec/cmd_redirections.c					\
							$(SRC_DIR)/exec/cmd_utils.c							\
							$(SRC_DIR)/exec/cmd.c								\
							$(SRC_DIR)/exec/dup2_files.c						\
							$(SRC_DIR)/exec/exec_add_struct.c					\
							$(SRC_DIR)/exec/execve.c							\
							$(SRC_DIR)/exec/free.c								\
							$(SRC_DIR)/exec/init.c								\
							$(SRC_DIR)/exec/init_env.c							\
							$(SRC_DIR)/exec/process.c							\
							$(SRC_DIR)/exec/struct_exec_utils.c					\
							$(SRC_DIR)/exec/struct_exec.c						\
							$(SRC_DIR)/exec/utils/cmd_builtins_utils.c			\
							$(SRC_DIR)/exec/utils/ll_utils_goto.c				\
							$(SRC_DIR)/exec/utils/ll_utils.c					\
							$(SRC_DIR)/exec/utils/utils.c						\
							$(SRC_DIR)/exec/utils/utils2.c						\
							$(SRC_DIR)/exec/utils/cmd_free.c					\
							$(SRC_DIR)/parsing/parsing/append_space.c 			\
							$(SRC_DIR)/parsing/parsing/check_quote.c 			\
							$(SRC_DIR)/parsing/parsing/check_synthax.c 			\
							$(SRC_DIR)/parsing/parsing/append_space_utils.c 	\
							$(SRC_DIR)/parsing/parsing/error_args.c 			\
							$(SRC_DIR)/parsing/expand/expand.c 					\
							$(SRC_DIR)/parsing/struct/fill_struct.c 			\
							$(SRC_DIR)/parsing/parsing/ft_split_shell.c 		\
							$(SRC_DIR)/parsing/utils/ft_strcpy.c 				\
							$(SRC_DIR)/parsing/parsing/get_input.c 				\
							$(SRC_DIR)/parsing/here_doc/here_doc.c 				\
							$(SRC_DIR)/parsing/struct/init_struct.c 			\
							$(SRC_DIR)/parsing/parsing/manage_quote.c 			\
							$(SRC_DIR)/parsing/struct/open_files.c 				\
							$(SRC_DIR)/parsing/struct/order_struct_out.c 		\
							$(SRC_DIR)/parsing/struct/order_struct_in.c 		\
							$(SRC_DIR)/parsing/struct/rm_file.c 				\
							$(SRC_DIR)/parsing/utils/signal.c 					\
							$(SRC_DIR)/parsing/utils/signal2.c 					\
							$(SRC_DIR)/parsing/struct/sort_operators.c 			\
							$(SRC_DIR)/parsing/expand/append_expand.c 			\
							$(SRC_DIR)/parsing/expand/find_path.c				\
							$(SRC_DIR)/parsing/parsing/remove_dollars_here.c	\
							$(SRC_DIR)/parsing/here_doc/remove_quote_here.c		\
							$(SRC_DIR)/parsing/struct/rm_chevron.c				\
							$(SRC_DIR)/parsing/struct/creat_file_here.c			\
							$(SRC_DIR)/parsing/struct/search_files.c			\
							$(SRC_DIR)/parsing/parsing/echo_n.c					\
							$(SRC_DIR)/parsing/parsing/split_shell_utils.c		\
							$(SRC_DIR)/parsing/parsing/manage_quote_utils.c


# **************************************************************************** # # SRCS #
SRCS 					:= $(SOURCES)	
OBJS 					:= $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS 					:= $(patsubst $(SRC_DIR)/%.c,$(DEPS_DIR)/%.d,$(SRCS))
# **************************************************************************** # # INCLUDES
INCS        			:= inc  												\
							inc/exec											\
						   $(LIBS)/inc				
						   
# **************************************************************************** # # LIBRARIES
LIBS       				:= libft
LIBS_TARGET 			:= libft/libft.a
# **************************************************************************** # # CC & FLAGS #
CC					    := cc -g3
CFLAGS					:= -Wall -Wextra -Werror 
CPPFLAGS 				:= -I inc -I libft/inc -I inc/exec/ -I inc/exec/builtins -Iinc/parsing -MMD -MP
LDFLAGS 				:= $(addprefix -L,$(dir $(LIBS_TARGET)))
LDLIBS  				:= -L$(LIBS) -lft -lreadline 
# **************************************************************************** # # UTILS #
RM          			:= rm -f

