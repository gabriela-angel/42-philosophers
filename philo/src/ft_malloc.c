/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:26:01 by gangel-a          #+#    #+#             */
/*   Updated: 2025/03/25 17:28:27 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_malloc	*get_malloc_item(void)
{
	static t_malloc	mlc;

	return (&mlc);
}

void	*ft_malloc(size_t size)
{
	t_malloc	*mlc;
	void		*ptr;

	mlc = get_malloc_item();
	ptr = ft_calloc(1, size);
	if (!ptr)
		return (NULL);
	mlc->list[mlc->i] = ptr;
	mlc->i++;
	return (ptr);
}

void	ft_free_all(void)
{
	t_malloc	*mlc;

	mlc = get_malloc_item();
	while (mlc->i > 0)
	{
		mlc->i--;
		free(mlc->list[mlc->i]);
		mlc->list[mlc->i] = NULL;
	}
}
