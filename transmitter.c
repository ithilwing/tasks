#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main () {
	int trans_pid = 0;
	int rec_pid = 0;
	trans_pid = getpid ();
	printf ("my pid is %d, i am a transmitter", trans_pid);
	scanf ("%d", &rec_pid);
        printf ("the reciever's pid id %d", rec_pid);
	
	


return 0;

}
