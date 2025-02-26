/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:56:46 by mjuncker          #+#    #+#             */
/*   Updated: 2025/02/26 10:45:22 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#if SHOW_LEXER

char	*process_line(const char *cmd_line, char **env, int *code)
{
	t_list	*quotes_lst;
	t_list	*var_lst;
	char	*process_str;

	if (cmd_line[0] == '\0')
		return (ft_strdup(cmd_line));
	ft_printf("---------------------- lexer output ----------------------\n");
	quotes_lst = process_quotes(cmd_line);
	ft_lstprint("quotes lst: ", quotes_lst);
	var_lst = process_expanded_vars(quotes_lst, env, *code);
	ft_lstprint("var lst: ", var_lst);
	process_str = join_lst(var_lst);
	ft_printf("process str: [%s]\n", process_str);

	process_str = process_wildcard(process_str);
	printf("expanded wildcard: %s\n", process_str);
	ft_printf("----------------------------------------------------------\n");
	ft_lstclear(&quotes_lst, free);
	ft_lstclear(&var_lst, free);
	return (process_str);
}

#else

char	*process_line(const char *cmd_line, char **env, int *code)
{
	t_list	*quotes_lst;
	t_list	*var_lst;
	char	*process_str;

	if (cmd_line[0] == '\0')
		return (ft_strdup(cmd_line));
	quotes_lst = process_quotes(cmd_line);
	var_lst = process_expanded_vars(quotes_lst, env, *code);
	process_str = join_lst(var_lst);
	process_str = process_wildcard(process_str);
	ft_lstclear(&quotes_lst, free);
	ft_lstclear(&var_lst, free);
	if (process_str == NULL)
	{
		*code = MALLOC_ERR;
		return (NULL);
	}
	return (process_str);
}

#endif
