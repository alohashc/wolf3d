/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alohashc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 14:23:47 by alohashc          #+#    #+#             */
/*   Updated: 2016/12/04 14:58:33 by alohashc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr(const char *s)
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
	}
}