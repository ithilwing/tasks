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
//#include <conio.h>

#define NMAX 300

char buffer_from_server[NMAX];

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
			printf("Connection lost\n");
			exit(0);
			}		 // прочитали всё что есть в буфере
		printf("%s\n", buffer_from_server); // вывели
		if (n < 0) {
			error("ERROR reading from socket");
		}
	}
}

int find_in_base(int found, char user_input[128]){
	FILE *input = NULL;
	char nickname[128];
	char password[128];
	char buffer[512];
	int i = 0;
	int length;

//	printf("%d", found);
	
	input = fopen("/home/tatkirkar/tasks/tasks/clients_base.txt", "r");
	if (input == NULL){
		printf("ERROR opening file\n");
	//	_getch();
		exit(-2);
	}

	found = 0;
	while(!feof(input)){
		fgets(buffer, 511, input);
//		printf("%s!\n", buffer);
		length = strlen(buffer);
		for (i = 0; i < length; i++){
			if (buffer[i] == '\t'){
				buffer[i] = '\0';
				break;
			}
		}
		strcpy(nickname, buffer);
		strcpy(password, &buffer[i+1]);
	
//		printf("%s!\n", nickname);
//		printf("%s!\n", password);
//		printf("%s!\n", user_input);
		if(!strcmp(nickname, user_input)){
			found = 1;
			break;
		}
		else found = 0;
//		printf("%d\n", found);

	}

	return found; // если совпали, 1, если не совпали, 0
}

void add_to_base(char user_nickname[128], char user_password[128]){

}

int check_password(char user_nickname[128], char user_password[128]){
	FILE *input = NULL;
	char buffer[512];
	char nickname[128];
	char password[128];
	char input_password[128];
	int i = 0;
	int f = 0;
	int length;

	input = fopen("/home/tatkirkar/tasks/tasks/clients_base.txt", "r");
	if (input == NULL){
		printf("ERROR opening file");
		exit(-2);
	}

	while(!feof(input)){
		fgets(buffer, 511, input);
		length = strlen(buffer);
		for (i = 0; i < length; i++){
			if(buffer[i] == '\t'){
				buffer[i] = '\0';
			}
		}

		strcpy(nickname, buffer);
		strcpy(password, &buffer[i+1]);
//		sprintf(input_password, "%s\n", user_password);
		
		printf("%s and %s and %s and %s\n", nickname, password, user_nickname, user_password);
		
		if((!strcmp(password, user_password)) && (!strcmp(nickname, user_nickname))){
			f = 1;
			break;
		}
		else{
			f = 0;
			printf("Invalid password!\n");
		}

	}
	return f;	
}

int main(int argc, char *argv[]){
	int portno, n;
	int sockfd;

	struct sockaddr_in serv_addr;
	struct hostent *server;

	char buffer[NMAX];
	char nickname[128];
	char password[128];
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

        printf("Enter your nickname: ");
	scanf("%s", nickname);

	
	int found = 0;
	int f = find_in_base(found, nickname);
	int counter = 0;

	printf("%d\n", f);

	if(f == 0){
		printf("Oh, it seems you are new here... Enter your password:");
		scanf("%s", password);
		add_to_base(nickname, password);
	}

	else if(f == 1){
		printf("got it\n");
		int success = 0;
		while(success == 0){
			printf("Enter your password: ");
			scanf("%s", password);
			success = check_password(nickname, password);
		}
	}

        n = write(sockfd, nickname, strlen(nickname) + 1);

	if (n < 0)
		error("ERROR writing to socket");
	

	bzero(buffer, 256);


/*Вот тут короче надо просто повозиься с корректным отображением pls enter ur msg */

        while(1){
		sleep(1);
		printf("Please enter the message: ");
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

