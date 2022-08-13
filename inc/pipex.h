/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <lloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:38:04 by lloisel           #+#    #+#             */
/*   Updated: 2022/08/13 17:59:10 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

typedef struct Pipex{

	char **argv;
	char **envp;
	char **cmd1;
	char **cmd2;
	int fd[2];
	int pipe[2];
}	t_pip; 

int	display_d(int nb);
void	error(char *s);
void	free_split(char **tab);

void	last(t_pip *p);
void	first(t_pip *p);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(const char *s, char c);
size_t	ft_strlen(const char *s);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
#endif
