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
  int num_remote_shell = num_args - 2;

  pid_t myShell = getpid();
  int tube1[num_remote_shell]; //tubes btw myShell and listeners
  pid_t pid[num_remote_shell]; //myShell: pid of each son
  
  for (int i = 0; i < num_remote_shell; ++i)
    pipe (tube[i]);

  //ACTION MY SHELL
  for (int i = 0; i < num_remote_shell; ++i){
    if ((pid[i] = fork()) == 0){
      //ACTION FILS LISTENER
      //i am a listener
      //i will create a son to execute  >>ssh name_i

      pid_t pid_remoteShell_i;

      if ((pid_remoteShell_i = fork()) == 0){
	//i am remoteShell_i
	execlp("ssh", "ssh", 
	
      

    }
  }

  for (int i = 0; i < num_remote_shell; ++i){
    wait(NULL);
  }
  return 0;
    
}

void internal_cmd_remote(Expression *e){

  if (!strcmp (e->arguments[1], "add"))
    remote_add(e);
    if (!strcmp (e->arguments[1], "all"))
    remote_all(e);
}

