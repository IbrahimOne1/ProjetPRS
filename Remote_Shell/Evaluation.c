#include "Shell.h"
#include "Evaluation.h"
#include "Commandes_Internes.h"

#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
void internal_cmd_exit(){
  raise(9);//send signal to calling process
  //execlp("kill", "kill", "-9", getpid(), NULL);
}


 /*
  * Execute a sequence command 
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
  
  if (!strcmp (e->arguments[0], "hostname")){
    internal_cmd_host();
    return;}
  if (!strcmp (e->arguments[0], "echo")){
    internal_cmd_echo(e);
    return;}
    if (!strcmp (e->arguments[0], "kill")){
    internal_cmd_kill(e);
    return;}
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

void cmd (char **arguments)
{execvp(arguments[0],arguments);
  perror("exec");
  exit(1);}
/*execute redirection_o*/
void  execute_redirection_o(Expression *e)
{if (fork()==0)
	  {int fd=open(e->arguments[0],O_CREAT|O_WRONLY,0644);
	    dup2(fd,1);
	    close(fd);
	    cmd(e->gauche->arguments);}
  else wait(NULL);}
/*execute redirection_i*/
void  execute_redirection_i(Expression *e)
{if(fork()==0)
	  {int fd=open(e->arguments[0],O_CREAT|O_WRONLY,0644);
	    dup2(fd,0);
	    close(fd);
	    cmd(e->gauche->arguments);}
	else wait(NULL);}
/*execute redirection_a*/
void  execute_redirection_a(Expression *e)
{ if(fork()==0)
	  {int fd=open(e->arguments[0],O_CREAT|O_WRONLY|O_APPEND,0644);
	    dup2(fd,1);
	    close(fd);
	    cmd(e->gauche->arguments);}
	else wait(NULL);}
/*execute redirection_e*/
void  execute_redirection_e(Expression *e)
{ if(fork()==0)
	  {int fd=open(e->arguments[0],O_CREAT|O_WRONLY,0644);
	    dup2(fd,2);
	    close(fd);
	    cmd(e->gauche->arguments);}
	else wait(NULL);}


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
  case REDIRECTION_O:
    execute_redirection_o(e);
    break;
  case REDIRECTION_I:
    execute_redirection_i(e);
    break;
  case REDIRECTION_A:
    execute_redirection_a(e);
    break;
  case REDIRECTION_E:
    execute_redirection_e(e);
    break;  
  default:
    fprintf(stderr,"fonctionnalité non implémentée\n");
  }
  /*ELIMINATION ZOMBIE*/
  int status ;
  int pid ;
  while((pid=waitpid(-1,&status,WNOHANG))>0)
    printf("[%d] status %d \n",pid,status);

  return 1;
}
