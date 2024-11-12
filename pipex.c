/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:36:46 by kgiraud           #+#    #+#             */
/*   Updated: 2024/11/12 17:36:23 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char **av, char **envp, int *fd)
{
	int	filein;

	filein = open(av[1], O_RDONLY);
	if (filein == -1)
		error_exit();
	close(fd[0]);
	dup2(filein, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	exec(av[2], envp);
}

void	parent_process(char **av, char **envp, int *fd)
{
	int	fileout;

	fileout = open(av[4], O_WRONLY);
	if (fileout == -1)
		error_exit();
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	exec(av[3], envp);
}

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (ac != 5)
	{
		write(1, "Erreur...\n", 10);
		write(1, "Essaye dans ce format : './pipex file1 cmd1 cmd2 file2'\n",
			56);
		return (0);
	}
	if (pipe(fd) == -1)
		error_exit();
	pid = fork();
	if (pid == -1)
		error_exit();
	if (pid == 0)
		child_process(av, envp, fd);
	wait(&pid);
	parent_process(av, envp, fd);
}
