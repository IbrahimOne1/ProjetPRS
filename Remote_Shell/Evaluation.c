#include "Shell.h"
#include "Evaluation.h"
#include "Commandes_Internes.h"

#include <string.h>
#include <unistd.h>
#include <signal.h>

#include <time.h>

void internal_cmd_exit(){
  raise(9);//send signal to calling process
  //execlp("kill", "kill", "-9", getpid(), NULL);
}

void internal_cmd_date(Expression *e){
  time_t current_time;
  char* c_time_string;
  
  current_time = time(NULL);
  c_time_string = ctime (&current_time);
  
  printf("%s\n", c_time_string);
}


 /*
  * Executer une commande dans un sous-shell ( () )
  * */
void execute_sous_shell_command(Expression *e){
  //--version utlisant "|" aussi possible --//
  int tube[2];
  pipe(tube);
  
  int status;
  pid_t pid = fork();

  if (pid){
    write (tube[1], *e->gauche->arguments, sizeof(*e->gauche->arguments));
    close (tube[1]);
    wait(&status);
    
  }else{

    close (tube[1]);
    dup2 (tube[0], STDIN_FILENO);
    execlp ("./Shell", "./Shell", NULL);
  }
     
}
   


 /*
  * Execute a SEQUENCE command ( ; )
  * */
void execute_sequence_command(Expression *e){
  //-- --//
  int status;
  pid_t pid = fork();

  if (pid){
    wait(&status);
    evaluer_expr(e->droite);
  }else{
    evaluer_expr(e->gauche);
    exit(0);
  }
  
}
   
    
    
  
 /*
  * Execute a simple command 
  * */
void execute_simple_command(Expression *e){

  if (!strcmp (e->arguments[0], "exit"))
    internal_cmd_exit();
  else if (!strcmp (e->arguments[0], "date")){
    internal_cmd_date(e);
    return;
  }
  
  int tmp;
  int pid = fork();
  if(pid<0)// Send an error if the fork fails
    printf("Fork failed");
		
  else if(pid==0){ //The son execute the command with the exec function
    execvp(e->arguments[0],&e->arguments[0]);
    perror("exec Faild");
    exit(0);
  }
  else{ // The father wait for his son
    wait(&tmp);
  }
}


/*
 * Execute or sequence ( || )
 * */	
 void execute_sequence_ou_command(Expression *e){
	 int pid = fork();
	 int tmp;
	 if(pid<0)
		perror("Fork failed");
	 else if(pid>0) //the father wait his son
			 wait(&tmp);
	 else{
		 execvp(e->gauche->arguments[0],e->gauche->arguments);//First exec
		 /*if the first exec failed => execute the secend */
		 execvp(e->droite->arguments[0],e->droite->arguments);//secend exec
		 perror("Exec failed");
		 exit(0);
		 
		 }
}

/*
 * execute and sequence ( && )
 * */			
 void execute_sequence_and_command (Expression *e){
	 int pid= fork();
	 int tmp;
	 if(pid<0)
	 perror("Fork failed");
	 
	 else if(pid==0){ //the son excutes the first command
		 execvp(e->gauche->arguments[0],e->gauche->arguments);
		 
		 return;
	 }
	 else{//the father excutes the second
		 wait(&tmp);
		 execvp(e->droite->arguments[0],e->droite->arguments);
		exit(0);
		 }
}
 /*
  * Execute a command in background (&)
 * */
 void execute_background(Expression *e){
	 int pid = fork();
	 int tmp;
	 if(pid<0)
		perror("fork failed ");
	else if(pid==0){
		execvp(e->gauche->arguments[0],e->gauche->arguments);
		perror("exec failed");
		exit(0);
		}
		else{
			waitpid(pid,&tmp,WNOHANG);
		}
}
	
 /*Execute a command */




int
evaluer_expr(Expression *e)
{
  
  //fprintf(stderr,"fonctionnalité non implémentée\n");

  switch(e->type){
  case VIDE:
    return 0;
  case SIMPLE:
    execute_simple_command(e);
    break;	
  case SEQUENCE_OU:
    execute_sequence_ou_command(e);
    break;
  case SEQUENCE_ET:
    execute_sequence_and_command(e);
    break;
  case BG:
    execute_background(e);
    break;
  case SEQUENCE:
    execute_sequence_command(e);
    break;
  case SOUS_SHELL:
    execute_sous_shell_command(e);
    break;
   
  }
  
  return 1;
}
