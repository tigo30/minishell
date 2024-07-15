/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrunho- <tgrunho-@student.42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:03:45 by macampos          #+#    #+#             */
/*   Updated: 2024/07/15 20:53:16 by tgrunho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *get_home_path(void)
{
	char *home = getenv("HOME");
	if (!home)
		home = "/home";
	return home;
}

void	cd(t_cmd *cmd, char **envp, t_main *main)
{
	char *dir;
	(void)envp;

	if (cmd->args[2])
	{
		write(2, "too many arguments\n", 20);
		main->status = 1;
		return;
	}
	else if (!cmd->args[1] || ft_strncmp(cmd->args[1], "~", 1) == 0)
		dir = get_home_path();
	else if (cmd->args[1][0] == '$')
	{
		dir = getenv(cmd->args[1] + 1);  // Expande a variável de ambiente
		if (!dir)
		{
			write(2, "no such file or directory\n", 27);
			main->status = 1;
			return;
		}
	}
	else
		dir = cmd->args[1];
	if (chdir(dir) == -1)
	{
		main->status = 1;
		write(2, "no such file or directory\n", 27);
	}
	else
	{
		main->status = 0;
		char cwd[1024];
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			int i = 0;
			while (main->env[i])
			{
				if (strncmp(main->env[i], "PWD=", 4) == 0)
				{
					free(main->env[i]);
					main->env[i] = malloc(strlen("PWD=") + strlen(cwd) + 1);
					sprintf(main->env[i], "PWD=%s", cwd);
					break;
				}
				i++;
			}
		}
	}
}
