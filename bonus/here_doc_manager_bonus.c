/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_manager_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 10:25:55 by fli               #+#    #+#             */
/*   Updated: 2024/07/05 14:08:16 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	check_heredoc(char **argv, t_pids	*new_nod)
{
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		if (if_here_doc(new_nod, argv) == -1)
		{
			free(new_nod);
			exit(EXIT_FAILURE);
		}
	}
	return ;
}

int	ft_strncmp_pipex(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n < 1 || !s1)
		return (0);
	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	if_here_doc(t_pids	*new_nod, char **argv)
{
	int		fd_hd;
	char	*next_line;
	char	*limiter;

	limiter = ft_strjoin(argv[2], "\n");
	if (limiter == NULL)
		return (-1);
	fd_hd = heredoc_creator(new_nod);
	if (fd_hd == -1)
		return (free(limiter), -1);
	next_line = get_next_line(0);
	while (ft_strncmp_pipex(next_line, limiter, ft_strlen(limiter)) != 0)
	{
		if (next_line == NULL)
			break ;
		write(fd_hd, next_line, ft_strlen(next_line));
		free(next_line);
		next_line = get_next_line(0);
	}
	free(limiter);
	free(next_line);
	close(fd_hd);
	return (get_next_line(-1), 0);
}

int	heredoc_creator(t_pids	*new_nod)
{
	int		i;
	int		fd_hd;
	char	*i_to_a;
	char	*hd_name;

	i = 0;
	fd_hd = open("here_doc0", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (fd_hd == -1)
	{
		i++;
		i_to_a = ft_itoa(i);
		if (i_to_a == NULL)
			return (-1);
		hd_name = ft_strjoin("here_doc", i_to_a);
		if (hd_name == NULL)
			return (free(i_to_a), -1);
		fd_hd = open(hd_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		free(i_to_a);
		free(hd_name);
	}
	new_nod->here_doc = i;
	return (fd_hd);
}
