/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <lloisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:36:11 by lloisel           #+#    #+#             */
/*   Updated: 2022/08/13 18:18:29 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"


/*cmd = ft_split(argv[1],' ');
	int i;
	i = 0;
	
	while(cmd[i])
	{
		printf("%s\n",cmd[i]);
		i++;
	}
	path = ft_strjoin("/bin/",cmd[0]);
	printf("%s\n",argv[1]);		
	execve(path,cmd,envp);
*/

int get_files(t_pip *p,char *infile,char *outfile)
{
	
	p->fd[0] = open(infile,O_DIRECTORY);
	if (p->fd[0] >= 0)
		return (error("infile is a directory\n"), 1);
	p->fd[1] = open(outfile,O_DIRECTORY);
	if (p->fd[1] >= 0)
		return (error("outfile is a directory\n"), 1);
	p->fd[0] = open(infile,O_RDONLY);
	if (p->fd[0] < 0)
		return (error("infile is not valid\n"), 1);
	p->fd[1] = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(p->fd[1] < 0)
		return (error("outfile is not valid"), 1);
	return (0);
}

int init_pipex(t_pip *p,char **argv,char **envp)
{
	p->argv = argv;
	p->envp = envp;
	p->cmd1 = ft_split(argv[2], ' ');
	p->cmd2 = ft_split(argv[3], ' ');
	if (get_files(p,argv[1],argv[4]))
		return (1);
	return(0);
}

int main(int argc, char **argv,char **envp)
{	
	t_pip p;
	int pid[2];

	//char **cmd;
	//cmd = ft_split(argv[2],' ');
	
	if(argc != 5)
		return(1);
	if (init_pipex(&p,argv,envp))
		return(1);
	//char *s = path(&p,cmd[0]);
	//printf("cmd : %s path :%s \n",cmd[0],s);
	//free_split(cmd);
	if (pipe(p.pipe) < 0)
		return(1);
	pid[0] = fork();
	if(pid[0] == 0)	
		first(&p);
	pid[1] = fork();
	if(pid[1] == 0)
		last(&p);
	close(p.pipe[0]);
	close(p.pipe[1]);
	waitpid(pid[0],NULL,0);
	waitpid(pid[1],NULL,0);
	/*execve(path(&p,cmd[0]),cmd,envp);*/
	free_split(p.cmd1);
	free_split(p.cmd2);
	return (0);
}
