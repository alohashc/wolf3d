/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alohashc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 15:02:24 by alohashc          #+#    #+#             */
/*   Updated: 2016/12/01 12:43:40 by alohashc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putendl(const char *s)
{
	char	*s1;
	int		i;

	i = 0;
	s1 = (char*)s;
	if (s1)
	{
		while (s1[i])
		{
			write(1, &s1[i], 1);
			i++;
		}
		write(1, "\n", 1);
	}
}