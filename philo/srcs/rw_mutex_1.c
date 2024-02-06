/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rw_mutex_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cumoncoq <cumoncoq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:13:09 by cumoncoq          #+#    #+#             */
/*   Updated: 2024/02/06 17:36:41 by cumoncoq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	r_ate(t_data *d)
{
	long long	res;

	pthread_mutex_lock(d->ate_mutex);
	res = d->ate;
	pthread_mutex_unlock(d->ate_mutex);
	return (res);
}

void	w_ate(t_data *d, long long value)
{
	pthread_mutex_lock(d->ate_mutex);
	d->ate = value;
	pthread_mutex_unlock(d->ate_mutex);
}

int	r_meals(t_data *d)
{
	int	res;

	pthread_mutex_lock(d->ate_mutex);
	res = d->meals;
	pthread_mutex_unlock(d->ate_mutex);
	return (res);
}

void	w_meals(t_data *d)
{
	pthread_mutex_lock(d->ate_mutex);
	d->meals++;
	pthread_mutex_unlock(d->ate_mutex);
}

void	w_min(t_data *d, int value)
{
	pthread_mutex_lock(d->end_mutex);
	*(d->min_meals) = value;
	pthread_mutex_unlock(d->end_mutex);
}
