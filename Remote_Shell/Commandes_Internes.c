#include "Commandes_Internes.h"
#include <stdio.h>

#include <string.h>
#include <unistd.h>



void internal_cmd_exit(){
  raise(9);//send signal to calling process
  //execlp("kill", "kill", "-9", getpid(), NULL);
}

void internal_cmd_host(){
  char hostname[1024];
  hostname[1023] = '\0';
  gethostname(hostname, 1023);
  printf("Hostname: %s\n", hostname);
}

void internal_cmd_echo(Expression *e)
{
  size_t i;
  if (num_elements(e->arguments) > 1)
    printf("%s",(e->arguments[1]));
  for (i = 2; i < num_elements(e->arguments); i++)
    printf(" %s",(e->arguments[i]));
  printf("\n");
}


//////////////////////////remote_shell////////////////////////////////////////

void remote_add (Expression *e){
  
  int num_args = num_elements(e->arguments);
  for (int i = 2; i < num_args; ++i){
    
}

void internal_cmd_remote(Expression *e){

  if (!strcmp (e->arguments[1], "add"))
    remote_add(e);

