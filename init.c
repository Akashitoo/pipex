/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalasub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 22:36:53 by abalasub          #+#    #+#             */
/*   Updated: 2024/05/14 16:06:12 by abalasub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	init_var(t_data *pipex, char **argv, char **envp)
{
	pipex->envp = envp;
	pipex->args1 = ft_split(argv[2], ' ');
	pipex->args2 = ft_split(argv[3], ' ');
	pipex->infile = open(argv[1], O_RDWR);
	pipex->outfile = open(argv[4], O_RDWR | O_TRUNC);
	if (pipe(pipex->pipefd) == -1)
	{
		perror("Pipe");
		exit(1);
	}
}

void	check_files(t_data *pipex, char **argv)
{
	if (pipex->infile == -1)
	{
		perror(
			"Le fichier 1 n'existe pas ou vous n'avez pas les permissions");
	}
	if (pipex->outfile == -1)
	{
		pipex->outfile = open(argv[4], O_WRONLY
				| O_CREAT | O_EXCL, 0644);
		if (pipex->outfile == -1)
			perror("Vous n'avez pas les permissions pour fichier 2");
	}
}
