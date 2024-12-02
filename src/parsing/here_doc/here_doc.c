/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkermani <nkermani@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:19:45 by afavier           #+#    #+#             */
/*   Updated: 2024/07/16 00:30:18 by nkermani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <readline/history.h>
#include <readline/readline.h>

static int	remove_quote_here(char **doc, size_t *quote);
static int	expand_here(size_t quote, char **input_doc, char ***env);
static int	read_here(int fd, char **doc, size_t quote, char ***env);

int	here_doc(t_cmd **cmd, char **doc, char ***env)
{
	size_t	quote;
	char	*name_fd;
	int		fd;

	quote = 0;
	if (remove_quote_here(doc, &quote) == -1)
		return (-1);
	name_fd = malloc(sizeof(char) * 6);
	if (!name_fd)
		return (-1);
	fd = create_file(name_fd);
	if (fd < 0)
		return (free(name_fd), -1);
	if (read_here(fd, doc, quote, env) == -1)
		return (unlink(name_fd), close(fd), free(name_fd), -1);
	if (append_cmd(cmd, name_fd) == -1)
		return (unlink(name_fd), close(fd), free(name_fd), -1);
	close(fd);
	fd = open(name_fd, O_RDONLY);
	if (fd < 0)
		return (free(name_fd), -1);
	unlink(name_fd);
	append_fd(fd, cmd);
	append_type_ope_built(NO_BUILTINS, IN_FILE, HERE_DOC, cmd);
	return (free(name_fd), 0);
}

static int	expand_here(size_t quote, char **input_doc, char ***env)
{
	size_t	i;
	char	*temp;

	i = 0;
	while ((*input_doc) != NULL && (*input_doc)[i] != '\0' && quote == 0)
	{
		if ((*input_doc)[i] == '$')
		{
			temp = expand_var((*input_doc), env);
			if (!temp)
				return (-1);
			free(*input_doc);
			*input_doc = temp;
			if (ft_strlen((*input_doc)) == 0)
			{
				free(*input_doc);
				(*input_doc) = ft_strdup("\n");
				if (!*input_doc)
					return (-1);
			}
		}
		i++;
	}
	return (0);
}

static int	read_here(int fd, char **doc, size_t quote, char ***env)
{
	char	*input_doc;

	while (1)
	{
		if (g_sig != 0)
			return (-1);
		input_doc = readline(">");
		if (!input_doc)
			break ;
		if (ft_strcmp(input_doc, *doc) == 0)
		{
			free(input_doc);
			break ;
		}
		if (expand_here(quote, &input_doc, env) == -1)
			return (close(fd), free(input_doc), -1);
		write_fd(fd, input_doc);
		free(input_doc);
	}
	return (0);
}

static int	remove_quote_here(char **doc, size_t *quote)
{
	int	i;

	i = -1;
	while ((*doc)[++i] != '\0')
	{
		if ((*doc)[i] == '$' && ((*doc)[i + 1] != '\0' && !(((*doc)[i
						+ 1] >= 'a' && (*doc)[i + 1] <= 'z') || ((*doc)[i
						+ 1] >= 'A' && (*doc)[i + 1] <= 'Z')) && (*doc)[i
				+ 1] != '_' && (*doc)[i + 1] != '$'))
			remove_dollars(doc, i);
		if ((*doc)[i] != '"' && (*doc)[i] != '\'')
			continue ;
		(*quote)++;
		if ((*doc)[i] == '"')
			i = remove_quote_char(doc, '"');
		else if ((*doc)[i] == '\'')
			i = remove_quote_char(doc, '\'');
		if (i == -1)
			return (-1);
		i--;
	}
	return (0);
}
