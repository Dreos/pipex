/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <lloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 09:49:44 by lloisel           #+#    #+#             */
/*   Updated: 2022/08/13 17:42:16 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>

static long int	nbdigit(long int i)
{
	long int	size;

	size = 0;
	if (i == 0)
		return (1);
	if (i < 0)
	{
		size++;
	}
	while (i != 0)
	{
		size++;
		i = i / 10;
	}
	return (size);
}

static char	*convert(char *s, long int i)
{
	if (i / 10 == 0)
	{
		*s = i + '0';
		return (s + 1);
	}
	s = convert(s, i / 10);
	*s = i % 10 + '0';
	return (s + 1);
}

char	*ft_itoa(long int i)
{
	char		*s;
	int			size;
	long int	j;

	j = i;
	size = nbdigit(j);
	s = malloc(size + 1);
	if (!(s))
		return (0);
	s[size] = '\0';
	if (j < 0)
	{
		*s = '-';
		convert(s + 1, -j);
	}
	else
	{	
		convert(s, j);
	}
	return (s);
}

int	display_d(int nb)
{
	char	*str;
	int x;
	str = ft_itoa(nb);
	if (!(str))
		return (0);
	nb = 0;
	while (str[nb])
	{
		x = write(1, (str + nb), 1);
		nb++;
	}
	free(str);
	return (nb);
}

void error(char *s)
{
	int x;
	int l;
	
	l = ft_strlen(s);
	x = write(2,"Error : ",8); 
	x = write(2,s,l);
}
void	free_split(char **tab)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (tab[len])
		len++;
	while (i < len)
		free(tab[i++]);
	free(tab);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	long unsigned int	i;

	i = 0;
	while (i < n && s1[i])
	{
		if (s1[i] != s2[i])
			return (((unsigned char)s1[i] - (unsigned char)s2[i]));
		if (!(s2[i]))
			return (0);
		i++;
	}
	if (i != n)
		return (-s2[i]);
	return (0);
}
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}
static size_t	count_words(const char *s, char c)
{
	size_t	words;
	int		state;

	words = 0;
	state = 1;
	while (s && *s)
	{
		if (*s == c)
			state = 1;
		else if (state == 1)
		{
			words++;
			state = 0;
		}
		s++;
	}
	return (words);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*d;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	d = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (d == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		d[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		d[i + j] = s2[j];
		j++;
	}
	d[i + j] = 0;
	return (d);
}
static size_t	sizeof_word(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && (s[i] != c))
		i++;
	return (i);
}

static	char	**free_tab(char **tab, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		free(tab[i++]);
	free(tab);
	return (0);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	size_t	index;
	size_t	i;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!tab)
		return (NULL);
	index = 0;
	while (count_words(s, c))
	{
		while (*s == c)
			s++;
		tab[index] = malloc(sizeof(char) * (sizeof_word(s, c) + 1));
		if (!tab[index])
			return (free_tab(tab, index));
		i = 0;
		while (*s && (*s != c))
			tab[index][i++] = *s++;
		tab[index][i] = 0;
		index++;
	}
	tab[index] = 0;
	return (tab);
}
