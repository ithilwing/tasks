//SERVER//
//ЗАПУСК СЕРВЕРА: gcc chat_server.c -o server -lpthread
//                ./server nnnn - номер хоста. 5000, например

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
#define NMAX 300

char buffer_in[NMAX];
char buffer_out[NMAX];


/* структура со всем хозяйством клиента */
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

/*добавление нового клиента в чат */

void add_client (thread_args_t *added_client){
	int i;
	for(i = 0; i < N_CLIENTS; i++){
		if(!thread_args[i]){
			thread_args[i] = added_client;
			return;
		}
	}
}

/*всё взаимодействие с клиентом */

void* client( void* void_thread_args) {
	thread_args_t *my_client = (thread_args_t *)void_thread_args; // приводим типа, чтобы далее использовать my_client->
	int n, j;
//	char buffer_in[256];
//	char buffer_out[256];
	sprintf(buffer_out, "Client %d has connected", my_client->client_number);// закидываем строку о том что клиент подключился
	for (j = 0; j < N_CLIENTS; j++){ // кидаем её по всем серверам
		if (thread_args[j]){
			n  = write(thread_args[j]->client_fd, buffer_out, strlen(buffer_out)+1);
		}
	}

	bzero(buffer_out, 256);

	while(1){
		n = read(my_client->client_fd, buffer_in, 255); //читаем из буфера клиента
		buffer_in[n] = 0;
		printf("Client %d: %s\n",my_client->client_number, buffer_in); // печатаем это всё

		if (n < 0)
			error("ERROR reading from socket");

//		printf( "%s\n", buffer);
		sprintf(buffer_out, "[%d] %s",my_client->client_number, buffer_in); // в буфер на отправку забиваем эту строку (потом там будет имя приславшего клиента)

		int k;
		for (k = 0; k < N_CLIENTS; k++){
			if (thread_args[k]){ //thread_args[] - массив указателей на структуру с аргументами, передаваемыми в тред
				printf("sending to client [%d]...\n", thread_args[k]->client_number);
				n = write(thread_args[k]->client_fd, buffer_out, strlen(buffer_out) + 1);	// печатаем в буферы всех клиентов сообщение 
			}
		}


		if (n < 0)
			error ("ERROR writing to socket");
	}
}


int main(int argc, char *argv[]){


	int sockfd, newsockfd, portno, clilen;
	struct sockaddr_in serv_addr, cli_addr; // contains internet-address
	int thread_result;

	if (argc < 2){
		fprintf(stderr, "No port provided\n");
		exit(-1);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0){
		error("Can't open socket");
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));

	portno = atoi(argv[1]);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR on binding");

	listen(sockfd,5);
	clilen = sizeof(cli_addr);

	


	int i = 0;

		while(1){
	
			newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		        if (newsockfd < 0)
			         error("ERROR on accept");

			thread_args_t *my_client = (thread_args_t *)malloc(sizeof(thread_args_t));

			my_client->client_number = i;
	   	    	my_client->client_fd = newsockfd;
			add_client(my_client);

			thread_result = pthread_create(&threadID[i], NULL, &client, (void*)my_client);
			i++;

		}

	if(thread_result){
		printf("Cannot create thread\n");
		exit(-1);
	}


	return 0;

}
