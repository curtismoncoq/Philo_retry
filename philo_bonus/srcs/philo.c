/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cumoncoq <cumoncoq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:40:56 by cumoncoq          #+#    #+#             */
/*   Updated: 2024/01/26 18:36:21 by cumoncoq         ###   ########.fr       */
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

void	ft_wait(t_data *d, t_args args, int *pids)
{
	int	child_left;
	int	child_finish;
	int	status;
	int	i;

	child_left = 1;
	child_finish = 0;
	while (child_left)
	{
		i = -1;
		child_left = 0;
		while (++i < args.phi)
		{
			child_finish = waitpid(pids[i], &status, WNOHANG);
			if (child_finish && WIFEXITED(status) && WEXITSTATUS(status) == 1)
			{
				sem_post(d->first_dead);
				child_left = 0;
				break ;
			}
			if (!child_finish)
				child_left = 1;
		}
	}
	usleep(1000);
}

void	send_philos(int *pids, t_args args, t_data*d)
{
	int	i;

	i = -1;
	while (++i < args.phi)
	{
		pids[i] = fork();
		d->id = i + 1;
		if (!pids[i])
		{
			free(pids);
			philo_process(d);
			exit(2);
		}
	}
	usleep(1000);
	if (check_threads(pids, d))
		exit_cleanly(pids, d, 1);
}

int	main(int ac, char **av)
{
	t_data			data;
	t_data			*d;
	t_args			args;
	int				*pids;

	d = &data;
	if (ft_parsing(ac, av, &args))
		return (0);
	pids = (int *)ft_calloc(sizeof(int), args.phi);
	if (!pids)
		return (perror("malloc"), 1);
	if (init_all_semas(d, args))
		return (free(pids), 1);
	ft_init_data(d, &args);
	sem_wait(d->action);
	send_philos(pids, args, d);
	sem_post(d->action);
	ft_wait(d, args, pids);
	exit_cleanly(pids, d, 0);
}
