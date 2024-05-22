/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalasub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:12:12 by abalasub          #+#    #+#             */
/*   Updated: 2024/05/22 12:37:10 by abalasub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	execute_cmd1(t_data pipex)
{
	dup2(pipex.pipefd[1], 1);
	close(pipex.pipefd[0]);
	if (dup2(pipex.infile, 0) < 0)
		error_file_exit(&pipex, pipex.argv[1], 0);
	if (execve(get_path(pipex.args1[0], pipex.envp, &pipex, 0),
			pipex.args1, pipex.envp) == -1)
		error_cmd_exit(&pipex, pipex.argv[2], 0);
}

void	execute_cmd2(t_data pipex)
{
	dup2(pipex.pipefd[0], 0);
	close(pipex.pipefd[1]);
	if (dup2(pipex.outfile, 1) < 0)
		error_file_exit(&pipex, pipex.argv[4], 1);
	if (execve(get_path(pipex.args2[0], pipex.envp, &pipex, 127),
			pipex.args2, pipex.envp) == -1)
		error_cmd_exit(&pipex, pipex.argv[3], 0);
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
		ft_putstr_fd("process failed", 1);
	if (pid == 0)
		execute_cmd1(pipex);
	pid2 = fork();
	if (pid2 == -1)
		ft_putstr_fd("process failed", 1);
	if (pid2 == 0)
		execute_cmd2(pipex);
	free_close(&pipex);
	waitpid(pid, &status, 0);
	waitpid(pid2, &status2, 0);
	exit_status(status, status2);
}
