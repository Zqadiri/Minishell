/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 18:40:10 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/05 16:17:15 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
t_cmdlist *create(t_token *cmd, int pipe)
{
	t_cmdlist *l;

	if (!(l = malloc(sizeof(t_cmdlist))))
		return (NULL);
	l->tokens = cmd;
	l->pipe = pipe;
	l->next_cmd = NULL;
	return (l);
}

// insert an element at the end of the list
void add_back(t_cmdlist **l, t_token *cmd, int pipe)
{
	t_cmdlist *new;
	t_cmdlist *last;

	new = malloc(sizeof(t_cmdlist));
	new->tokens = cmd; 
	new->pipe = pipe;
	new->next_cmd = NULL;
	last = *l;
	if ((*l) == NULL)
		(*l) = new;
	else
	{
		while (last->next_cmd != NULL)
			last = last->next_cmd;
		last->next_cmd = new;
	}
}

// insert an element to the top of list --> history
void push(t_cmdlist **l, t_token *cmd, int pipe)
{
	t_cmdlist *new;
	
	if (l && cmd)
	{
		new = malloc(sizeof(t_cmdlist));
		new->tokens = cmd;
		new->pipe = pipe;
		new->next_cmd = *l;
		*l = new;
	}
}

void print_cmd(t_cmdlist *l)
{
	t_cmdlist *temp;
	int i;

	i = 0;
	temp = l;
	while(temp)
	{
		printf("pipe = %d\n", temp->pipe);
		while(temp->tokens[i])
		{
			printf("token[%d]={type:%s, value:%s}\n", i, temp->tokens[i]->type, temp->tokens[i]->value);
			i++;
		}
	}
	printf("\n");
}
