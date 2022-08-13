/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <lloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 17:39:00 by lloisel           #+#    #+#             */
/*   Updated: 2022/08/13 18:02:04 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

char *path(t_pip *p,char *s)
{
	char *cmd;
	char **tab;
	int i;
	char *tmp;
	
		
	i = 0;
	while(ft_strncmp("PATH",p->envp[i], 4))
		i++;
	tmp = p->envp[i] + 5;
	tab  = ft_split(tmp,':');
	i = -1;
	while(tab[++i])
	{
		tmp = ft_strjoin(tab[i], "/");
		cmd = ft_strjoin(tmp, s);
		free(tmp);
		if(!access(cmd, F_OK))
		{
			free_split(tab);
			return(cmd);	
		}
		free(cmd);
	}
	free_split(tab);
	return("fail");
}
void first(t_pip *p)
{
	close(p->pipe[0]);
	dup2(p->fd[0], STDIN_FILENO);
	dup2(p->pipe[1], STDOUT_FILENO);
	if (p->cmd1[0] && path(p,p->cmd1[0]))
	{
		execve(path(p,p->cmd1[0]), p->cmd1, p->envp);
	}
	else
		printf("Command not found : %s\n",p->cmd1[0]); ;
}
void last(t_pip *p)
{
	close(p->pipe[1]);
	dup2(p->fd[1], STDOUT_FILENO);
	dup2(p->pipe[0], STDIN_FILENO);
	if (p->cmd2[0] && path(p,p->cmd2[0]))
	{
		execve(path(p,p->cmd2[0]),p->cmd2, p->envp);
	}
	else
		printf("Command not found : %s\n",p->cmd2[0]); ;
		
}
