/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 10:43:52 by zqadiri           #+#    #+#             */
/*   Updated: 2021/05/17 10:31:28 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**  Change the working directoy and updates the environment variable
**  accordingly while handling errors
**  cases : cd ~ | cd --> home dir
**  cd . leave the user in the same directory
**  cd ..
*/

void    set_env_var(char *id, char *cur_dir)
{
    
}

int change_dir(char *path)
{
    char *current_dir;
    char *buf;
    int size;

    buf = (char *)malloc((size_t)size);
    if (buf != NULL)
        current_dir = getcwd(buf, (size_t)size);
    if (!chdir(path))
    {
        set_env_var("OLDPWD", current_dir);
        return (1);
    }
    else
    {
        printf("cd: %s: %s\n", path, strerror(errno));
        return (1);
    }
}

int cd_builtin(char **arg)
{
    char *home_path;

    // home_path = get_env_var_by_key("HOME");
    change_dir(arg[1]);
	return (1);
}
