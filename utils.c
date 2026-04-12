#include "philo.h"

// num of philo ,  >0
// time to sleep > 60ms , >0
// time to die > 60ms, >0 
// time to eat >60 ms, >0
// but what type of interger ?

int ft_atoi (char *str)
{
    int i; 
    int nbr;
    int sign;

    nbr=0;
    sign=1;
    i=0;

    // skip spaces 
    while(str[i]==32|| (str[i]>=9 && str[i]<=13))
        i++;
    if(str[i]=='-'||str[i]=='+')
    {
        if(str[i]=='-')
            sign=-1;
        i++;
    }

    while(str[i]>='0'&& str[i]<='9')
    {
        nbr= (str[i]-'0')+nbr*10;
        i++;
    }
    return (nbr*sign);
}