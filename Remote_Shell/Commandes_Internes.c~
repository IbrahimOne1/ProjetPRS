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
{
     size_t i;
     if (sizeof(e->arguments[1]) > 1)
       printf("%s",(e->arguments[1]));
     for (i = 2; i < sizeof(e->arguments); i++)
       printf(" %s",(e->arguments[i]));
    printf("\n");
    }
