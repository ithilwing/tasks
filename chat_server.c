//SERVER//


#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define N_CLIENTS 50

typedef struct{
       	int client_number;
	int client_fd;
}thread_args_t;

pthread_t threadID[N_CLIENTS];
thread_args_t *thread_args[N_CLIENTS];

void error(char *msg){
	perror(msg);
	exit(-1);
}

void add_client (thread_args_t *added_client){
	int i;
	for(i = 0; i < N_CLIENTS; i++){
		if(thread_args[i]){
			thread_args[i] = added_client;
			return;
		}
	}
}

/*void send_message (char *s){
	int i;
	for (i = 0; i < N_CLIENTS; i++){
		if(thread_args[i]){
			write(thread_args[i]->client_fd, s, strlen(s));
		}
	}
}*/
	

void* client( void* void_thread_args) {
//	printf("Thread has been created\n");
//	thread_args_t my_client = *(thread_args_t *)void_thread_args;
	thread_args_t *my_client = (thread_args_t *)void_thread_args;
	int n;
	char buffer_in[256];
	char buffer_out[256];
//	printf("%d\n", my_client->client_number);
//
	while(1){
		n = read(my_client->client_fd, buffer_in, 255); //читаем из буфера клиента
		printf("Client %d: %s\n",my_client->client_number, buffer_in); // печатаем это всё

		if (n < 0)
			error("ERROR reading from socket");

//		printf( "%s\n", buffer);
		sprintf(buffer_out, "%s", buffer_in); // в буфер на отправку забиваем эту строку (потом там будет имя приславшего клиента)

		int k;
		for (k = 0; k < N_CLIENTS; k++){
			if (thread_args[k]){ //thread_args[] - массив указателей на структуру с аргументами, передаваемыми в тред
				printf("sending...\n");
				n = write(thread_args[k]->client_fd, buffer_out, 256);	// печатаем в буферы всех клиентов сообщение 
			}
		}

//		n = write(my_client->client_fd, buffer, 255);

		if (n < 0)
			error ("ERROR writing to socket");
	}
}


//int main(int argc, char *argv[]){
int main(){

	int sockfd, newsockfd, portno, clilen;
//	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr; // contains internet-address
	int thread_result;

/*	if (argc < 2){
		fprintf(stderr, "No port provided\n");
		exit(-1);
	}*/

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0){
		error("Can't open socket");
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));

//	portno = atoi(argv[1]);
	portno = 8005;

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR on binding");

	listen(sockfd,5);
	clilen = sizeof(cli_addr);

//	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	


	int i = 0;

		while(1){
//			thread_args[i]->client_number = i;	
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	        if (newsockfd < 0)
		         error("ERROR on accept");

		thread_args_t *my_client = (thread_args_t *)malloc(sizeof(thread_args_t));
//		thread_args_t my_client = &my_client_pointer;
		my_client->client_number = i;
	       	my_client->client_fd = newsockfd;
		add_client(my_client);
//		printf("%d\n", my_client->client_number);
		thread_result = pthread_create(&threadID[i], NULL, &client, (void*)my_client);
		i++;

	}

	if(thread_result){
		printf("Cannot create thread\n");
		exit(-1);
	}


	return 0;

}
