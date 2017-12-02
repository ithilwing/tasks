//CLIENT// 
//
//ЗАПУСК КЛИЕНТА: gcc chat_client.c -o client -lpthread
//                ./client localhost nnnn - номер хоста, на котором запустили сервер. 5000, например


#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define NMAX 300

char buffer_from_server[NMAX];
/*пыталась сделать одновременно с посылом сообщений (в мейне) отдельным параллельным тредом тупо чтение всего, что приходит от сервера. Получается криво, но сообщения в тредах все появляются. Если не обращать внимания на please enter ur msg в неожиданных местах и мусора. Но надо исправлять */

/* НАСЧЁТ МУСОРА - это должно исправиться, если учитывать как символы то ли пробел, то ли энтер. Но у меня уже нет времени */

void error (char *msg){
	perror(msg);
	exit(0);
}

/*функция от треда, тупо чтение и вывод всего */

void* message_reading (void *args){ // закинули аргументом файлдескриптор слиента

	while(1){
		int * new_args = (int*)args;
		int newsockfd = *new_args;
//		char buffer_from_server[256];
		int n;
		if((n = read(newsockfd, buffer_from_server, 255)) <= 0){
			printf("connection lost\n");
			exit(0);
			}		 // прочитали всё что есть в буфере
		printf("%s\n", buffer_from_server); // вывели
		if (n < 0) {
			error("ERROR reading from socket");
		}
	}
}


int main(int argc, char *argv[]){
	int portno, n;
	int sockfd;

	struct sockaddr_in serv_addr;
	struct hostent *server;

	char buffer[NMAX];
	if (argc < 3){
		fprintf(stderr, "usage %s hostname port\n", argv[0]);
		exit(0);
	}

	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)
		error("ERROR opening socket");

	server = gethostbyname(argv[1]);

	if (server == NULL){
		fprintf(stderr, "ERROR, no such host\n");
		exit(0);
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));


	serv_addr.sin_family = AF_INET;
	bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);

	if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR connecting");
	
	pthread_t thread;
	int thread_result;
	thread_result = pthread_create(&thread, NULL, &message_reading, &sockfd);

/*Вот тут короче надо просто повозиься с корректным отображением pls enter ur msg */

        while(1){
		sleep(1);
		printf("Please enter the message: \n");
		scanf("%s", buffer);

		//bzero(buffer, 256);
		//fgets(buffer, 255, stdin);

		n = write(sockfd, buffer, strlen(buffer)+1);


		if (n < 0)
			error("ERROR writing to socket");

		bzero(buffer, 256);
	}
	return 0;
}

