#include "Commandes_Internes.h"
#include <stdio.h>

#include <string.h>
#include <unistd.h>

void internal_cmd_host()
{char hostname[1024];
hostname[1023] = '\0';
gethostname(hostname, 1023);
printf("Hostname: %s\n", hostname);
}
void internal_cmd_echo(Expression *e)
{ int nb=num_elements(e->arguments);
    int i;
     if (nb > 1)
       printf("%s",(e->arguments[1]));
     for (i = 2; i < nb; i++)
       printf(" %s",(e->arguments[i]));
    printf("\n");
    }
void internal_cmd_kill(Expression *e)
{}
