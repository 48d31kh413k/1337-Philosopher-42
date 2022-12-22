#include <philo_bonus.h>

static void	philo_mange(t_philo *philo)
{
	t_table	*tab;

	tab = philo->tab;
	sem_wait(philo->tab->fourchette);
	afficher_message(philo, MESSAGE_FOURCHETTE);
	if (philo->tab->nombre_de_philos == 1)
	{
		passe_temps(tab, tab->temps_de_famine);
		afficher_message(philo, MESSAGE_MORT);
		tab->mort = 1;
		return ;
	}
	sem_wait(philo->tab->fourchette);
	afficher_message(philo, MESSAGE_FOURCHETTE);
	sem_wait(philo->tab->verifier);
	philo->nombre_manger++;
	afficher_message(philo, MESSAGE_MANGER);
	philo->dernier_repas = temps_actuel();
	sem_post(philo->tab->verifier);
	passe_temps(tab, tab->temps_de_manger);
	sem_post(philo->tab->fourchette);
	sem_post(philo->tab->fourchette);
}

void	*la_vie(void *arg)
{
	t_philo	*philo;
	t_table	*tab;

	philo = (t_philo *)arg;
	tab = philo->tab;
	philo->dernier_repas = tab->t_0;
	pthread_create(&philo->verifier_dead, NULL, verifier_la_mort, (void *)philo);
	if (philo->identifiant % 2 == 0)
		usleep(1000);
	while (!tab->mort)
	{
		philo_mange(philo);
		if (tab->nombre_de_repas != -1 && philo->nombre_manger >= tab->nombre_de_repas)
			break ;
		afficher_message(philo, MESSAGE_SOMMEIL);
		passe_temps(tab, tab->temps_de_sommeil);
		afficher_message(philo, MESSAGE_PENSER);
	}
	pthread_join(philo->verifier_dead, NULL);
	exit (0);
}
