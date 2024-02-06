/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cumoncoq <cumoncoq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:19:27 by cumoncoq          #+#    #+#             */
/*   Updated: 2024/01/17 18:23:13 by cumoncoq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_join(pthread_t *thread, t_data *d, t_time *t, pthread_t *monitor)
{
	int	i;

	i = -1;
	pthread_join(monitor[0], NULL);
	pthread_join(monitor[1], NULL);
	while (++i < d->arg->phi)
		pthread_join(thread[i], NULL);
	i = -1;
	while (++i < d->arg->phi)
	{
		pthread_mutex_destroy((d + i)->mutex);
		pthread_mutex_destroy((d + i)->ate_mutex);
	}
	pthread_mutex_destroy(&(t->start_mutex));
	pthread_mutex_destroy(&(t->end_mutex));
}

int	ft_fail(pthread_t *thread, t_data *d, int th, int mut)
{
	int	i;

	i = -1;
	w_start(d, -1);
	while (++i < th)
		pthread_join(thread[i], NULL);
	i = -1;
	while (++i < mut)
	{
		pthread_mutex_destroy((d + i)->mutex);
		pthread_mutex_destroy((d + i)->ate_mutex);
	}
	return (1);
}

void	ft_free_alloc(pthread_t *threads, pthread_mutex_t *mutex, t_data *d)
{
	int	i;

	i = 0;
	while (d && i < d->arg->phi)
	{
		if (d[i].ate_mutex)
			free(d[i].ate_mutex);
		i++;
	}
	if (threads)
		free(threads);
	if (mutex)
		free(mutex);
	if (d)
		free(d);
}
