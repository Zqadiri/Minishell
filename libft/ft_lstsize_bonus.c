/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 16:54:56 by zqadiri           #+#    #+#             */
/*   Updated: 2021/06/05 15:55:11 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*count_lst;

	count_lst = lst;
	i = 0;
	while (count_lst)
	{
		i++;
		count_lst = count_lst->next;
	}
	return (i);
}
