#include "Commandes_Internes.h"

#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>


void internal_cmd_exit(){
  raise(9);//send signal to calling process
  //execlp("kill", "kill", "-9", getpid(), NULL);
}

//////////////////////////remote_shell////////////////////////////////////////

void remote_add (Expression *e){
  printf("size of args: %d\n", num_elements(e->arguments));
  printf("arg0: %s\n", e->arguments[0]);
  printf("arg1: %s\n", e->arguments[1]);
  printf("arg2: %s\n", e->arguments[2]);
  printf("arg9: %s\n", e->arguments[9]);
}

void internal_cmd_remote(Expression *e){

  if (!strcmp (e->arguments[1], "add"))
    remote_add(e);
 
}
