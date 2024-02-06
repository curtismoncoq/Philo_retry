/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cumoncoq <cumoncoq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:20:19 by cumoncoq          #+#    #+#             */
/*   Updated: 2024/01/17 18:32:58 by cumoncoq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_issign(char c)
{
	if (c == '-' || c == '+' || c == ' ')
		return (1);
	return (0);
}

int	ft_verif_atoi(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-')
		return (ft_putstr_fd("Negative argument is invalid.\n", 1), -1);
	if (str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (ft_putstr_fd("Invalid format argument.\n", 1), -1);
	return (ft_atoi(str));
}

int	ft_parsing(int ac, char **av, t_args *arg)
{
	arg->phi = ft_verif_atoi(av[1]);
	arg->die = ft_verif_atoi(av[2]);
	arg->eat = ft_verif_atoi(av[3]);
	arg->sleep = ft_verif_atoi(av[4]);
	if (ac == 6)
	{
		arg->max_eat = ft_verif_atoi(av[5]);
		if (arg->max_eat < 0)
			return (1);
	}
	else
		arg->max_eat = -1;
	if (arg->phi < 0 || arg->die < 0)
		return (1);
	if (arg->eat < 0 || arg->sleep < 0)
		return (1);
	if (arg->phi == 1)
	{
		printf("0 1 has taken a fork\n%d 1 died\n", arg->die + 1);
		return (1);
	}
	return (0);
}
