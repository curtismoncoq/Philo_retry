/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cumoncoq <cumoncoq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:39:04 by cumoncoq          #+#    #+#             */
/*   Updated: 2024/02/01 22:07:10 by cumoncoq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

sem_t	*init_sem(char *name, int value)
{
	sem_t	*sem;

	sem = sem_open(name, O_CREAT, 0644, value);
	if (sem == SEM_FAILED)
	{
		perror("sem_open");
		return (NULL);
	}
	return (sem);
}

int	end_semas_init(t_data *d, t_args args, int i)
{
	char	semas[8];

	semas[0] = 'e';
	semas[1] = 'n';
	semas[2] = 'd';
	semas[3] = '_';
	semas[4] = '0';
	semas[5] = '0';
	semas[6] = '0';
	semas[7] = 0;
	end_semas_unlink(args.phi);
	while (++i < args.phi)
	{
		semas[4] = '0' + (i / 100);
		semas[5] = '0' + ((i % 100) / 10);
		semas[6] = '0' + (i % 10);
		d->end[i] = init_sem(semas, 0);
		if (d->end[i] == NULL)
			end_semas_close(d, i, 1);
	}
	if (i == args.phi)
		return (0);
	else
		return (1);
}

void	end_semas_close(t_data *d, int last, int unlink)
{
	char	semas[8];
	int		i;

	semas[0] = 'e';
	semas[1] = 'n';
	semas[2] = 'd';
	semas[3] = '_';
	semas[4] = '0';
	semas[5] = '0';
	semas[6] = '0';
	semas[7] = 0;
	i = 0;
	while (i < last)
	{
		semas[4] = '0' + (i / 100);
		semas[5] = '0' + ((i % 100) / 10);
		semas[6] = '0' + (i % 10);
		sem_close(d->end[i]);
		if (unlink)
			sem_unlink(semas);
		i++;
	}
	free(d->end);
}

void	end_semas_unlink(int last)
{
	char	semas[8];
	int		i;

	semas[0] = 'e';
	semas[1] = 'n';
	semas[2] = 'd';
	semas[3] = '_';
	semas[4] = '0';
	semas[5] = '0';
	semas[6] = '0';
	semas[7] = 0;
	i = 0;
	while (i < last)
	{
		semas[4] = '0' + (i / 100);
		semas[5] = '0' + ((i % 100) / 10);
		semas[6] = '0' + (i % 10);
		sem_unlink(semas);
		i++;
	}
}

int	init_all_semas(t_data *d, t_args args)
{
	ft_init_named(d, args);
	if (!d->forks || !d->action || !d->knife || !d->first_dead)
		return (ft_error_named(d), 1);
	ft_init_mutex(d, args);
	if (!d->mutex_eat || !d->mutex_meals || !d->mutex_run)
		return (ft_error_named(d), ft_error_mutex(d), 1);
	d->end = (sem_t **)ft_calloc(args.phi, sizeof(*(d->end)));
	if (d->end == NULL || end_semas_init(d, args, -1))
	{
		ft_error_mutex(d);
		ft_error_named(d);
		return (1);
	}
	return (0);
}
