/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rw_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cumoncoq <cumoncoq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:19:25 by cumoncoq          #+#    #+#             */
/*   Updated: 2024/02/02 01:42:09 by cumoncoq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	r_ate(t_data *d)
{
	long long	res;

	sem_wait(d->mutex_eat);
	res = d->ate;
	sem_post(d->mutex_eat);
	return (res);
}

void	w_ate(t_data *d, long long value)
{
	sem_wait(d->mutex_eat);
	d->ate = value;
	sem_post(d->mutex_eat);
}

long long	r_meals(t_data *d)
{
	long long	res;

	sem_wait(d->mutex_meals);
	res = d->meals;
	sem_post(d->mutex_meals);
	return (res);
}

void	w_meals(t_data *d)
{
	sem_wait(d->mutex_meals);
	d->meals++;
	sem_post(d->mutex_meals);
}
