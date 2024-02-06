/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cumoncoq <cumoncoq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:16:43 by cumoncoq          #+#    #+#             */
/*   Updated: 2024/02/01 23:33:25 by cumoncoq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_exit(int code, t_data *d)
{
	if (code == 1)
	{
		sem_wait(d->first_dead);
		if (!r_run(d))
			sem_post(d->first_dead);
	}
	if (!r_run(d))
		code = 0;
	w_run(d);
	sem_post(d->end[d->id - 1]);
	if (code)
		unlock_everyone(d);
	if (code == 1)
	{
		sem_wait(d->action);
		printf("%lld %d died\n", ft_time() - d->start, d->id);
		sem_post(d->action);
	}
	if (code != 2)
		pthread_join(d->routine, NULL);
	if (code != 2 && code != 3)
		pthread_join(d->exitor, NULL);
	ft_close_semas(d);
	exit(code);
}

void	ft_monitor(t_data *d)
{
	while (1)
	{
		if (r_meals(d) >= r_max(d) && r_max(d) >= 0)
			ft_exit (0, d);
		if (ft_time() - r_ate(d) > d->arg->die)
			ft_exit (1, d);
		usleep(10);
	}
}

void	*ft_one_died(void *data)
{
	t_data	*d;

	d = data;
	sem_wait(d->end[d->id - 1]);
	sem_post(d->end[d->id - 1]);
	w_run(d);
	w_max(d, 1);
	w_meals(d);
	w_meals(d);
	return (data);
}

void	*routine(void *data)
{
	t_data	*d;

	d = data;
	while (r_run(d))
	{
		eat(d);
		if (!r_run(d))
			break ;
		sleep_think(d);
	}
	return (data);
}

void	philo_process(t_data *d)
{
	sem_wait(d->action);
	sem_post(d->action);
	if (pthread_create(&(d->routine), NULL, routine, (void *)d))
		ft_exit (2, d);
	if (pthread_create(&(d->exitor), NULL, ft_one_died, (void *)d))
		ft_exit (3, d);
	w_ate(d, d->start);
	ft_monitor(d);
}
