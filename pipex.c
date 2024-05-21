/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalasub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:12:12 by abalasub          #+#    #+#             */
/*   Updated: 2024/05/15 15:22:31 by abalasub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	execute_cmd1(t_data pipex)
{
	if (!pipex.args1)
		error_exit(&pipex, "command 1 not defined", 0);
	dup2(pipex.pipefd[1], 1);
	close(pipex.pipefd[0]);
	if (dup2(pipex.infile, 0) < 0)

	if (execve(get_path(pipex.args1[0], pipex.envp, &pipex, 0),
			pipex.args1, pipex.envp) == -1)
		error_exit(&pipex, "execve 1 failed", 0);
}

void	execute_cmd2(t_data pipex)
{
	if (!pipex.args2)
		error_exit(&pipex, "command 2 not defined", 1);
	dup2(pipex.pipefd[0], 0);
	close(pipex.pipefd[1]);
	if (dup2(pipex.outfile, 1) < 0)
		error_exit(&pipex, "outfile dup failed", 1);
	if (execve(get_path(pipex.args2[0], pipex.envp, &pipex, 127),
			pipex.args2, pipex.envp) == -1)
		error_exit(&pipex, "execve 2 failed", 0);
}

void	exit_status(int status, int status2)
{
	if (WEXITSTATUS(status) > 0)
		exit(WEXITSTATUS(status));
	else if (WEXITSTATUS(status2) > 0)
		exit(WEXITSTATUS(status2));
	exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	pid_t	pid2;
	t_data	pipex;
	int		status;
	int		status2;

	if (argc != 5)
		return (ft_putstr_fd("Bad argument(s)\n", 2), 1);
	init_var(&pipex, argv, envp);
	pid = fork();
	if (pid == -1)
		error_exit(&pipex, "procces 1 failed", 1);
	if (pid == 0)
		execute_cmd1(pipex);
	pid2 = fork();
	if (pid2 == -1)
		error_exit(&pipex, "procces 2 failed", 1);
	if (pid2 == 0)
		execute_cmd2(pipex);
	free_close(&pipex);
	waitpid(pid, &status, 0);
	waitpid(pid2, &status2, 0);
	exit_status(status, status2);
}
