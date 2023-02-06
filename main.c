#include "philo.h"

int main(int argc, char **argv)
{
    t_var   *var;
    
    if (argc == 5 || argc == 6)
    {
        var = NULL;
        if(ft_error(argv) != 1)
            return (0);
       // if (init_base(&var, &philo, argc, argv) != 1)
          //  return (0);
        //printf("mais?\n");
        var = (init_base(var, argc, argv));
        if (!var)
            return (0);
        //printf("nbr 2 = %d\n", var.nb_philo);
        if (init_thread(var) != 1)
            return (0);
        if (join_thread(var) != 1)
            return (0);
        free_all(var);
        //printf("thread = %d\n", init_thread(&var));
        // if (dinner(&data, &philo) != 1)
        //     return (0);
    }
    else
    {
        printf("You should use 5 args like : ./philo nbr1 nbr2 nbr3 nbr4\n");
        printf("Or\n");
        printf("You should use 6 args like : ./philo nbr1 nbr2 nbr3 nbr4 nbr5\n");
    }
    return (0);
}