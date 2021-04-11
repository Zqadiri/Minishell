/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 18:40:10 by iidzim            #+#    #+#             */
/*   Updated: 2021/04/11 12:27:28 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int list_size(t_cmdlist *l)
{
    int i;

    i = 0;
    while(l != NULL)
    {
        l = l->next_cmd++;
        i++;
    }
    return (i);
}

//insert if the list is empty
t_cmdlist *create(void *cmd)
{
    t_cmdlist *l;

    if (!(l = malloc(sizeof(t_cmdlist))))
        return (NULL);
    l->cmd = &cmd;
    l->next_cmd = NULL;
    return (l);
}

// insert an element to the top of list
void *push(t_cmdlist *l, char *cmd)
{
    t_cmdlist *temp;
    
    temp = malloc(sizeof(t_cmdlist));
    if (l)
    {
        temp->cmd = &cmd;
        temp->next_cmd = l->next_cmd;
        temp->next_cmd = NULL;
    }
}

void ft_freelst(t_cmdlist *l)
{
	t_cmdlist *temp;

	while(l != NULL)
	{
		temp = l;
		l = l->next_cmd;
		free(temp);
	}
	// print_err();
}

void print_cmdlist(t_cmdlist *l)
{
	t_cmdlist *temp;

	temp = l;
	while(temp)
	{
		printf("%s - ", temp->cmd);
		temp = temp->next_cmd;
	}
	printf("\n");
}
