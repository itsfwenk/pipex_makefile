/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_pipex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:31:25 by fli               #+#    #+#             */
/*   Updated: 2024/07/02 10:11:18 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_strjoin_pipex(char const *s1, char const *s2)
{
	int		tot;
	char	*joined;

	tot = ft_strlen(s1) + ft_strlen(s2) + 2;
	joined = malloc((tot) * sizeof(char));
	if (joined == NULL)
		return (NULL);
	ft_strlcpy(joined, s1, ft_strlen(s1) + 1);
	joined[ft_strlen(joined) + 1] = '\0';
	joined[ft_strlen(joined)] = '/';
	ft_strlcat(joined, s2, tot);
	return (joined);
}

/* #include <stdio.h>
int	main()
{
	char const s1[500] = "lorem ipsum";
	char const s2[200] = "dolor sit amet";
	char *res = ft_strjoin(s1, s2);
	printf("%s\n", res);
}*/
