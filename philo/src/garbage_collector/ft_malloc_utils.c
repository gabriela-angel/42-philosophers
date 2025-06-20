/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 23:09:40 by gangel-a          #+#    #+#             */
/*   Updated: 2025/06/15 23:09:40 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_gc_free(void *ptr)
{
	t_malloc	*mlc;
	t_malloc	*tmp;

	if (!ptr)
		return ;
	mlc = get_malloc_item();
	while (mlc->next)
	{
		if (mlc->ptr == ptr)
		{
			free(mlc->ptr);
			tmp = mlc->next;
			mlc->ptr = tmp->ptr;
			mlc->next = tmp->next;
			free(tmp);
			return ;
		}
		mlc = mlc->next;
	}
}

void	ft_gc_exit(void)
{
	t_malloc	*mlc;
	t_malloc	*tmp;

	mlc = get_malloc_item();
	while (mlc->next)
	{
		if (mlc->ptr)
			free(mlc->ptr);
		tmp = mlc->next;
		mlc->ptr = tmp->ptr;
		mlc->next = tmp->next;
		free(tmp);
	}
	mlc->ptr = NULL;
	mlc->next = NULL;
}

t_bool	ft_gc_add(void *ptr)
{
	t_malloc	*mlc;

	if (!ptr)
		return (FALSE);
	mlc = get_malloc_item();
	while (mlc->next)
	{
		if (mlc->ptr == ptr)
			return (TRUE);
		mlc = mlc->next;
	}
	mlc->next = ft_calloc(1, sizeof(t_malloc));
	if (!mlc->next)
		return (FALSE);
	mlc->ptr = ptr;
	return (TRUE);
}

void	ft_gc_free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		ft_gc_free(matrix[i]);
		i++;
	}
	ft_gc_free(matrix);
	return ;
}
