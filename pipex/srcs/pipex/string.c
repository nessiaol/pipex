/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-luca <bde-luca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 19:15:10 by bde-luca          #+#    #+#             */
/*   Updated: 2021/07/06 13:55:47 by bde-luca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

char	*ft_strtoupper(char *str)
{
	char	*tmp;
	int		i;

	tmp = ft_strnew(ft_strlen(str));
	i = 0;
	while (*str)
	{
		tmp[i] = ft_toupper(*str);
		str++;
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	return (c);
}

char	*ft_strnew(size_t size)
{
	char	*ptr;

	ptr = (char*)ft_memalloc((size + 1) * sizeof(char));
	return (ptr);
}

int	get_nbwords(char const *s, char c)
{
	int	nb_words;
	int	i;

	i = 0;
	nb_words = 0;
	while (s && *(s + i))
	{
		while (*(s + i) && *(s + i) == c)
			i++;
		if (*(s + i))
			nb_words++;
		while (*(s + i) && *(s + i) != c)
			i++;
	}
	return (nb_words);
}

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = NULL;
	if (s && (ptr = (char *)malloc(sizeof(char) * (len + 1))))
	{
		while (i < len)
		{
			ptr[i] = s[start + i];
			i++;
		}
		ptr[i] = '\0';
	}
	return (ptr);
}
