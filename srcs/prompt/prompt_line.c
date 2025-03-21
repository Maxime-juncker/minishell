/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:31:08 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/21 21:57:41 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#if CUSTOM_PROMPT

static char	*get_folder(void)
{
	char	*temp;
	char	buffer[1024];
	char	*folder;

	if (!getcwd(buffer, sizeof(buffer)))
	{
		temp = ft_strdup("");
		if (malloc_assert(temp, __FILE__, __LINE__, __FUNCTION__))
			return (NULL);
		return (temp);
	}
	folder = ft_strdup(buffer);
	if (malloc_assert(folder, __FILE__, __LINE__, __FUNCTION__))
		return (NULL);
	temp = folder;
	if (folder[1] != '\0')
		while (*folder && ft_strchr(folder, '/') != 0)
			folder++;
	folder = ft_strjoin(folder, ":");
	free(temp);
	if (malloc_assert(folder, __FILE__, __LINE__, __FUNCTION__))
		return (NULL);
	return (folder);
}

char	*new_prompt_txt(char **env)
{
	char	*txt;
	char	*folder;

	folder = get_folder();
	if (malloc_assert(folder, __FILE__, __LINE__, __FUNCTION__))
		return (NULL);
	txt = ft_strjoin_free(BLUE, folder, FREE2);
	if (malloc_assert(txt, __FILE__, __LINE__, __FUNCTION__))
		return (NULL);
	txt = ft_charjoin(txt, ' ');
	if (malloc_assert(txt, __FILE__, __LINE__, __FUNCTION__))
		return (NULL);
	txt = ft_strjoin_free(txt, GREEN, FREE1);
	if (malloc_assert(txt, __FILE__, __LINE__, __FUNCTION__))
		return (NULL);
	txt = ft_strjoin_free(txt, find_env_var(env, "USER", NULL), FREE1 | FREE2);
	if (malloc_assert(txt, __FILE__, __LINE__, __FUNCTION__))
		return (NULL);
	txt = ft_strjoin_free(txt, "$\033[0m ", FREE1);
	if (malloc_assert(txt, __FILE__, __LINE__, __FUNCTION__))
		return (NULL);
	return (txt);
}

#else

char	*new_prompt_txt(char **env)
{
	(void)env;
	return (ft_strdup("minishell $ "));
}

#endif
