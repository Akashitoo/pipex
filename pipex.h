/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalasub <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:56:16 by abalasub          #+#    #+#             */
/*   Updated: 2024/05/14 16:57:02 by abalasub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

typedef struct s_data {
	int		infile;
	int		outfile;
	int		pipefd[2];
	int		status;
	char	**args1;
	char	**args2;
	char	**envp;
}			t_data;

void	init_var(t_data *pipex, char **argv, char **envp);
void	check_files(t_data *pipex, char **argv);
void	check_args(t_data *pipex);
void	free_tab(char **tab);
char	*get_path(char *cmd, char **envp, t_data *pipex, int last_cmd);
void	free_close(t_data *pipex);
void	error_exit(t_data *pipex, char *error, int status);

#endif
