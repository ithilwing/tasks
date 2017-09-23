#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main () {
        int trans_pid = 0;
        int rec_pid = 0;
        rec_pid = getpid ();
        printf ("my pid is %d, i am a reciever", rec_pid);
        scanf ("%d", &trans_pid);
        printf ("the transmitter's pid id %d", trans_pid);

        


return 0;

}

