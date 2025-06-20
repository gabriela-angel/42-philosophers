/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:52:06 by acesar-m          #+#    #+#             */
/*   Updated: 2025/06/19 21:02:18 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_malloc	*get_malloc_item(void)
{
	static t_malloc	mlc;

	return (&mlc);
}

void	*ft_malloc(size_t size)
{
	t_malloc	*mlc;
	void		*ptr;

	mlc = get_malloc_item();
	while (mlc->next)
		mlc = mlc->next;
	ptr = ft_calloc(1, size);
	if (!ptr)
		return (NULL);
	mlc->ptr = ptr;
	mlc->next = ft_calloc(1, sizeof(t_malloc));
	if (!mlc->next)
	{
		free(ptr);
		mlc->ptr = NULL;
		return (NULL);
	}
	return (ptr);
}
