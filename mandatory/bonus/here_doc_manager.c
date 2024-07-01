/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 10:25:55 by fli               #+#    #+#             */
/*   Updated: 2024/07/01 10:29:30 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

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

int	if_here_doc(char **argv)
{
	int		fd_hd;
	char	*next_line;
	char	*limiter;

	limiter = ft_strjoin(argv[2], "\n");
	if (limiter == NULL)
		return (-1);
	fd_hd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_hd == -1)
		return (-1);
	next_line = get_next_line(0);
	while (ft_strncmp_pipex(next_line, limiter, ft_strlen(limiter)) != 0)
	{
		write(fd_hd, next_line, ft_strlen(next_line));
		free(next_line);
		next_line = get_next_line(0);
	}
	free(limiter);
	free(next_line);
	get_next_line(-1);
	close(fd_hd);
	return (0);
}
