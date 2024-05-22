/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalasub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 22:36:53 by abalasub          #+#    #+#             */
/*   Updated: 2024/05/22 12:54:55 by abalasub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	init_var(t_data *pipex, char **argv, char **envp)
{
	pipex->envp = envp;
	pipex->argv = argv;
	pipex->args1 = ft_split(argv[2], ' ');
	pipex->args2 = ft_split(argv[3], ' ');
	pipex->infile = open(argv[1], O_RDWR);
	pipex->outfile = open(argv[4], O_RDWR | O_TRUNC);
	if (pipex->outfile == -1)
	{
		pipex->outfile = open(argv[4], O_WRONLY
				| O_CREAT | O_EXCL, 0644);
	}
	if (pipe(pipex->pipefd) == -1)
	{
		perror("Pipe");
		exit(1);
	}
}

void	error_cmd_exit(t_data *pipex, char *file, int status)
{
	if (access(file, F_OK) == -1)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (access(file, X_OK) == -1)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	free_close(pipex);
	exit(status);
}

void	error_file_exit(t_data *pipex, char *file, int status)
{
	if (access(file, F_OK) == -1)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (!status && access(file, R_OK) == -1)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else if (status && access(file, W_OK) == -1)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	free_close(pipex);
	exit(status);
}
