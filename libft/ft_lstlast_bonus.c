/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 16:55:55 by zqadiri           #+#    #+#             */
/*   Updated: 2021/06/05 15:55:04 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list		*lst_last;

	lst_last = lst;
	if (lst == 0)
		return (0);
	while (lst_last->next)
		lst_last = lst_last->next;
	return (lst_last);
}
