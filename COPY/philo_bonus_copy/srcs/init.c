/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cumoncoq <cumoncoq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:21:35 by cumoncoq          #+#    #+#             */
/*   Updated: 2024/01/24 16:01:54 by cumoncoq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_data(t_data *d, t_args *args)
{
	d->arg = args;
	d->ate = 0;
	d->start = ft_time();
	d->meals = 0;
	d->running = 1;
	return (0);
}
