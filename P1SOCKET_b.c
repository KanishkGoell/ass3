#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>
#include<time.h>

#define SOCKET_NAME "CustomSocket"
#define BUFFER_SIZE 10


void getRandStr(char [][12]);
int main(int argc, char* argv[]) {
	struct sockaddr_un addr;
	int ret;
	int data_socket;
	char buffer[BUFFER_SIZE];

	//Creating data socket
    socket(AF_UNIX, SOCK_SEQPACKET, 0);
	memset(&addr, 0, sizeof(addr));

	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SOCKET_NAME, sizeof(addr.sun_path) - 1);
	connect(data_socket, (const struct sockaddr *) &addr, sizeof(addr));

	char randStr[51][12] = {{0}};
	getRandStr(randStr);
	
	for(int i = 1; i <= 50; i++) {
		for(int j = 0; j < 12; j++) {
			if(j == 0) {
				printf("%d ", randStr[i][j]);
			}
			else printf("%c", randStr[i][j]);
		}
		printf("\n");
	}

	if(argc > 1) {
		strncpy(buffer, "DOWN", sizeof("DOWN"));
		write(data_socket, buffer, sizeof(buffer));
		close(data_socket);
		exit(EXIT_SUCCESS);
	}
	else {
		int lastIdx = 1;
		while(1) {
			printf("sending Strings Indexed from %d to %d\n", lastIdx, lastIdx + 4);
			for(int i = lastIdx; i < lastIdx + 5; i++) {
			    write(data_socket, randStr[i], strlen(randStr[i]) + 1);
				
			}

			//Reading Acknowledgements
			read(data_socket, buffer, sizeof(buffer));

			buffer[sizeof(buffer) - 1] = 0;
			int finalIdx = atoi(buffer);
			
			printf("MAX ID SENT BACK BY SERVER = %s\n\n", buffer);
			if(finalIdx == 50) {
				printf("Successfully sent all Strings\n");
				strncpy(buffer, "DOWN", sizeof("DOWN"));
				write(data_socket, buffer, sizeof(buffer));
				close(data_socket);
				exit(EXIT_SUCCESS);
				break;
			}
			else {
				lastIdx = finalIdx + 1;
			}
		}
	}
}
void getRandStr(char randstrs[][12]) {        
    srand (time(NULL));                            
    for (int j = 0; j <= 50; j++) {
        randstrs[j][0] = j;
    }
    
    for(int i = 0; i <= 50; i++) {
		for(int j = 1; j <= 10; j++) {
			randstrs[i][j] = rand() % 26 + 65;
		}
	}
}
