/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:52:06 by acesar-m          #+#    #+#             */
/*   Updated: 2025/06/21 19:07:20 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_malloc	*get_malloc_item(void)
{
	static t_malloc	mlc;

	return (&mlc);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if ((nmemb * size) > (size_t)-1)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	memset(ptr, 0, nmemb * size);
	return (ptr);
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
