#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> 

#define STDIN 0
#define STDOUT 1
#define PIPE_RD 0 
#define PIPE_WR 1



int main(){

	int pid, child_status;

	if ((pid = fork()) == 0) {
    	printf("I am the child and I see the PID %d\n", pid);
 	} else { 
 		wait(&child_status); // Wait for child
 		printf("I am the parent, I see the child's PID (%d) and the statud (%d)\n", pid, child_status);
	}
}