#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const int CHAR_NUMBER = 1;
const int BITS_PER_CHAR = 8;

int main() {
    int trans_pid, rec_pid;
	char recieved_msg[CHAR_NUMBER * BITS_PER_CHAR];

    rec_pid = getpid();
    printf("my pid is %d, i am a reciever\n", rec_pid);
    scanf("%d", &trans_pid);
    printf("the transmitter's pid is %d\n", trans_pid);
	getchar();

    int i, j;
    int pow2 = 1;
    int msg_dec = 0;

    for (i = 0; i < (CHAR_NUMBER * BITS_PER_CHAR); i++) {
	        scanf("%c", &recieved_msg[i]);
	}
  
    for (i = 0; i < CHAR_NUMBER; i++){
	    int current_msg = (int) recieved_msg[i];
	    for (j = BITS_PER_CHAR * (i + 1) - 1; j >= BITS_PER_CHAR * i; j--){
		    if (recieved_msg[j] == '1'){
			msg_dec = msg_dec + pow2;
		    }
		    pow2 = pow2 * 2;
	    }
	    printf("%c", msg_dec);
	    msg_dec = 0;
	    pow2 = 1;

    }

    printf("\n");

    return 0;
}

