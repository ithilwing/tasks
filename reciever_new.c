#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define CHAR_NUMBER 1
#define BITS_PER_CHAR 8
//char recieved_msg[CHAR_NUMBER * BITS_PER_CHAR];
//char recieved_msg[CHAR_NUMBER];

int k = 0;

//0
void sig1_handler () {	
	k = 1;
	return;
}
//1
void sig2_handler (){
	k = 2;
	return;
}

int main() {
//	char recieved_msg[CHAR_NUMBER * BITS_PER_CHAR];
	int trans_pid, rec_pid;
    rec_pid = getpid();
    printf("my pid is %d, i am a reciever\n", rec_pid);
    scanf("%d", &trans_pid);
    printf("the transmitter's pid is %d\n", trans_pid);
	getchar();

 //   int i, j;
  //  int pow2 = 1;
 //   int msg_dec = 0;
   // int signo;
    int bit_pointer = 0;
    k = 0;
    int recieved_msg = 0;

	signal(SIGUSR1, sig1_handler);
	signal(SIGUSR2, sig2_handler);
    while(1) {	
	while(1) {
		switch(k) {
			case 0:
				 break;
			case 1:
				 printf("OK 0");
				 recieved_msg >>= 1;
                                 bit_pointer++;
				 k = 0;
			         printf("0");
      				kill(trans_pid, SIGUSR1);
				break;
			case 2:
				printf("OK 1");
				recieved_msg >>= 1;
				recieved_msg |= (1 << 7);
                                bit_pointer++;
				k = 0;
				printf("1");
				kill(trans_pid, SIGUSR1);
				break;

		}
	if (bit_pointer == 8) break;

	}
    printf("%c", (char)recieved_msg);
    recieved_msg = 0;
    bit_pointer = 0;
     }
   

/*	for (i = 0; i < CHAR_NUMBER * BITS_PER_CHAR; i++){
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

    }*/ // a nice function from bin to char//

    printf("\n");

    return 0;
}

