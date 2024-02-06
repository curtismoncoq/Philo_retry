/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rw_mutex_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cumoncoq <cumoncoq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:11:47 by cumoncoq          #+#    #+#             */
/*   Updated: 2024/01/17 18:28:42 by cumoncoq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	r_ended(t_data *d)
{
	int	res;

	res = 0;
	pthread_mutex_lock(d->end_mutex);
	if (*(d->ended))
		res = 1;
	pthread_mutex_unlock(d->end_mutex);
	return (res);
}

void	w_ended(t_data *d, int value)
{
	pthread_mutex_lock(d->end_mutex);
	*(d->ended) = value;
	pthread_mutex_unlock(d->end_mutex);
}

int	r_start(t_data *d)
{
	int	res;

	pthread_mutex_lock(d->start_mutex);
	res = *(d->start_lock);
	pthread_mutex_unlock(d->start_mutex);
	return (res);
}

void	w_start(t_data *d, int value)
{
	pthread_mutex_lock(d->start_mutex);
	*(d->start_lock) = value;
	pthread_mutex_unlock(d->start_mutex);
}
