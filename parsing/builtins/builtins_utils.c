/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrunho- <tgrunho-@student.42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:02:52 by tgrunho-          #+#    #+#             */
/*   Updated: 2024/06/28 21:07:13 by tgrunho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	strln(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

int	check_equal(char *value)
{
	int	i;

	i = 0;
	while (value[i] && i < (int)ft_strlen(value))
	{
		if (value[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	handle_status_case(t_main *main, char *arg)
{
	int	i;

	i = 1;
	printf("%i", main->status);
	while (arg[i] && arg[i] != ' ')
	{
		printf("%c", arg[i]);
		i++;
	}
}
