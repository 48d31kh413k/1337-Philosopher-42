#include <philo_bonus.h>

void	*verifier_la_mort(void *arg)
{
	t_philo	*philo;
	t_table	*tab;

	philo = (t_philo *)arg;
	tab = philo->tab;
	while (1)
	{
		sem_wait(tab->verifier);
		if (temps_actuel() - philo->dernier_repas > (size_t)tab->temps_de_famine)
		{
			afficher_message(philo, MESSAGE_MORT);
			tab->mort = 1;
			exit (1);
		}
		sem_post(tab->verifier);
		if (tab->mort)
			break ;
		usleep(1000);
		if (tab->nombre_de_repas != -1 && philo->nombre_manger >= tab->nombre_de_repas)
			break ;
	}
	return (NULL);
}

void	la_sortie(t_table *tab)
{
	int	i;
	int	status;

	i = -1;
	while (++i < tab->nombre_de_philos)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 1)
		{
			i = -1;
			while (++i < tab->nombre_de_philos)
				kill(tab->philos[i].pid, SIGTERM);
			break ;
		}
	}
	sem_close(tab->afficher);
	sem_close(tab->verifier);
	sem_close(tab->fourchette);
	sem_unlink("/sem_afficher");
	sem_unlink("/sem_verifier");
	sem_unlink("/sem_fourchette");
	free(tab->philos);
}

size_t	temps_actuel(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	passe_temps(t_table *tab, size_t temps)
{
	size_t	t;

	t = temps_actuel();
	while (!(tab->mort))
	{
		if (temps_actuel() - t >= temps)
			break ;
		usleep(100);
	}
}
