#include <philo.h>

static int	verifier_nombres(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		if (argv[i][0] == '-')
			return (1);
		else if (argv[i][0] == '+')
			j++;
		if (!ft_isdigit(argv[i][j + 1]))
			return (1);
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
		}
	}
	return (0);
}

static int	verifier_entier(char *s)
{
	size_t	len;

	len = ft_strlen(s);
	if (*s == '+' && s++)
		len--;
	while (*s == '0' && *s && len--)
		s++;
	if (len > 10)
		return (1);
	else if (len < 10)
		return (0);
	if (ft_strncmp(s, "2147483648", 10) >= 0)
		return (1);
	return (0);
}

static int	valider_args(int argc, char *argv[])
{
	int	i;

	if (verifier_nombres(argc, argv))
		return (1);
	i = 0;
	while (++i < argc)
	{
		if (verifier_entier(argv[i]))
			return (1);
	}
	return (0);
}

static void	initialisation(t_table *tab)
{
	int	i;

	tab->mort = 0;
	tab->satiete = 0;
	tab->philos = (t_philo *)malloc(tab->nombre_de_philos * sizeof(t_philo));
	i = -1;
	while (++i < tab->nombre_de_philos)
	{
		tab->philos[i].identifiant = i + 1;
		tab->philos[i].tab = tab;
		tab->philos[i].nombre_manger = 0;
		if (i + 1 == tab->nombre_de_philos)
			tab->philos[i].suivant = &tab->philos[0];
		else
			tab->philos[i].suivant = &tab->philos[i + 1];
		if (i == 0)
			tab->philos[i].precedent = &tab->philos[tab->nombre_de_philos - 1];
		else
			tab->philos[i].precedent = &tab->philos[i - 1];
		pthread_mutex_init(&tab->philos[i].fourchette, NULL);
	}
	pthread_mutex_init(&tab->afficher, NULL);
	pthread_mutex_init(&tab->verifier, NULL);
}

int	verifier_args(int argc, char *argv[], t_table *tab)
{
	if (valider_args(argc, argv))
		return (1);
	tab->nombre_de_philos = ft_atoi(argv[1]);
	tab->temps_de_famine = ft_atoi(argv[2]);
	tab->temps_de_manger = ft_atoi(argv[3]);
	tab->temps_de_sommeil = ft_atoi(argv[4]);
	tab->nombre_de_repas = -1;
	if (argc == 6)
		tab->nombre_de_repas = ft_atoi(argv[5]);
	initialisation(tab);
	return (0);
}
