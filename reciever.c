#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define CHAR_NUMBER 1
#define BITS_PER_CHAR 8
char recieved_msg[CHAR_NUMBER * BITS_PER_CHAR];
//char recieved_msg[CHAR_NUMBER];
int bit_pointer = 0;
int k = 1;
int trans_pid, rec_pid;



//1
void sig1_handler () {	
	recieved_msg[bit_pointer] = '1';
	bit_pointer++;
	printf("bit_pointer ++");
	kill(trans_pid, SIGUSR1);
	if (bit_pointer = CHAR_NUMBER * BITS_PER_CHAR - 1)
		k = 0;
}
//0
void sig2_handler (){
	recieved_msg[bit_pointer] = '0';
	bit_pointer++;
        printf("bit_pointer ++");
	kill(trans_pid, SIGUSR1);
        if (bit_pointer = CHAR_NUMBER * BITS_PER_CHAR - 1)
	        k = 0;

}



int main() {
//	char recieved_msg[CHAR_NUMBER * BITS_PER_CHAR];

    rec_pid = getpid();
    printf("my pid is %d, i am a reciever\n", rec_pid);
    scanf("%d", &trans_pid);
    printf("the transmitter's pid is %d\n", trans_pid);
	getchar();


    int i, j;
    int pow2 = 1;
    int msg_dec = 0;
    int signo;


	signal(SIGUSR1, sig1_handler);
	signal(SIGUSR2, sig2_handler);
		
	while (k != 0){
	}
	for (i = 0; i < CHAR_NUMBER * BITS_PER_CHAR; i++){
		printf("OK %c\n", recieved_msg[i]);
	}
  
    for (i = 0; i < CHAR_NUMBER; i++){
//	    int current_msg = (int) recieved_msg[i];
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

