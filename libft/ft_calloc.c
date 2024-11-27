/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:43:08 by mgarsaul          #+#    #+#             */
/*   Updated: 2024/10/16 10:43:11 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_memalloc(size_t size)
{
	void	*new;
	size_t	i;

	new = (void *) malloc(size);
	if (!new)
		return (NULL);
	i = 0;
	while (i < size)
	{
		*(unsigned char *)(new + i) = 0;
		i++;
	}
	return (new);
}

void	*ft_calloc(size_t count, size_t size)
{
	if (size != 0 && count > ((size_t) -1 / size))
		return (NULL);
	return (ft_memalloc(count * size));
}
/*
int	main(void)
{
	int	*arr;
	size_t	n = 5;
	size_t	i;

	i = 0;
	arr = (int *)ft_calloc(5, 1);
	if (!arr)
	{
		printf("Erreur : echec de l'allocation memoire\n");
		return (1);
	}
	printf("Contenu du tableau alloue :\n");
	while (i < n)
	{
		printf("arr[%zu] = %d\n", i, arr[i]);
		i++;
	}
	free(arr);

	return (0);
}*/
