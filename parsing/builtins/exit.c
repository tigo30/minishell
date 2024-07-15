/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrunho- <tgrunho-@student.42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:04:19 by macampos          #+#    #+#             */
/*   Updated: 2024/07/15 20:07:26 by tgrunho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_args(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
}

void	free_cmd(t_cmd *cmd)
{
	free_cmd_args(cmd);
}

t_main *exitt(t_cmd *cmd, char **envp, t_main *main)
{
    char *truearg;
    int exit_status;

    (void)envp;
    if (cmd->args[1])
        truearg = ft_itoa(ft_atoi(cmd->args[1]));
    if (!cmd->args[1] || ft_strncmp(truearg, cmd->args[1], ft_strlen(cmd->args[1])) == 0)
    {
        if (cmd->args[1] && cmd->args[2] && ft_strncmp(truearg, cmd->args[1], ft_strlen(cmd->args[1])) == 0)
        {
            main->status = 1;
            write(2, "too many arguments\n", 20);
            free(truearg);
            return (main);
        }
        if (cmd->args[1])
            free(truearg);
        free_env_and_export(main);
        if (cmd->args[1])
            exit_status = (unsigned char)ft_atoi(cmd->args[1]);
        else
            exit_status = 0;
        free(main);
        free_cmd(cmd);
        exit(exit_status);
    }
    else if (ft_strncmp(truearg, cmd->args[1], ft_strlen(cmd->args[1])) != 0)
    {
        free(truearg);
        if (!ft_atoi(cmd->args[1]) && !cmd->args[2])
        {
            main->status = 2;
            write(2, "numeric argument required\n", 27);
        }
		else if (cmd->args[1] && ft_strchr(cmd->args[1], '-'))
		{
   			main->status = -100;
    		write(2, "numeric argument required\n", 27);
		}
        else if (cmd->args[1])
        {
            main->status = 100;
            write(2, "numeric argument required\n", 27);
        }
        exit_status = main->status;
        free_env_and_export(main);
        free(main);
        free_cmd(cmd);
        exit(exit_status);
    }
    return (main);
}
