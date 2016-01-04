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
  
  int num_args = num_elements(e->arguments);
  for (int i = 2; i < num_args; ++i){
    
}

void internal_cmd_remote(Expression *e){

  if (!strcmp (e->arguments[1], "add"))
    remote_add(e);
 
}
