/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrunho- <tgrunho-@student.42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 00:59:17 by macampos          #+#    #+#             */
/*   Updated: 2024/06/28 21:10:55 by tgrunho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	configure_env(t_main *mainn, char **envp, int *place, char *exported)
{
	int	j;

	j = 0;
	while (envp[j])
	{
		if (j != place[0] || find_equal(exported) == -1)
			mainn->env[j] = envp[j];
		else if (j == place[0] && find_equal(exported) > 0)
			mainn->env[j] = ft_strdup(exported);
		j++;
	}
	if (find_equal(exported) > 0 && place[0] == -1)
		mainn->env[j] = ft_strdup(exported);
}

void	config_export(t_main *mainn, char **envp2, int *place, char *exported)
{
	int	j;

	j = 0;
	while (envp2[j])
	{
		if (j != place[1])
			mainn->export[j] = envp2[j];
		else
			mainn->export[j] = ft_strdup(exported);
		j++;
	}
	if (place[1] == -1)
		mainn->export[j] = ft_strdup(exported);
}

t_main	*set_main2(t_main *main, char **envp, char **envp2, char *exported)
{
	int		*place;
	t_main	*mainn;

	place = check_paired(exported, envp, envp2, strln(exported));
	mainn = calloc(1, sizeof(t_main));
	mainn->env = calloc(matrixlen(envp) + 2, sizeof(char *));
	mainn->export = calloc(matrixlen(envp2) + 2, sizeof(char *));
	configure_env(mainn, envp, place, exported);
	config_export(mainn, envp2, place, exported);
	free(main->env);
	free(main->export);
	free(main);
	free(place);
	return (mainn);
}

t_main	*set_main3(t_main *main, char **envp, char **envp2, char *exported)
{
	int		*place;
	t_main	*mainn;

	place = check_paired(exported, envp, envp2, strln(exported));
	mainn = calloc(1, sizeof(t_main));
	mainn->env = calloc(matrixlen(envp) + 2, sizeof(char *));
	mainn->export = calloc(matrixlen(envp2) + 2, sizeof(char *));
	configure_env(mainn, envp, place, exported);
	config_export(mainn, envp2, place, exported);
	if (place[0] != -1)
		free(main->env[place[0]]);
	if (place[1] != -1)
		free(main->export[place[1]]);
	free(main->env);
	free(main->export);
	free(main);
	free(place);
	return (mainn);
}
