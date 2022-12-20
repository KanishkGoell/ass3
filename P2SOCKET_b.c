#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>
#include<time.h>
struct sockaddr_un servername;
#define SOCKET_NAME "CustomSocket"
int main(int argc, char* argv[]){
    socket(AF_UNIX, SOCK_SEQPACKET, 0);
    int socket_id, data_socket;
    memset(&servername, 0, sizeof(servername));
    servername.sun_family = AF_UNIX;
	strncpy(servername.sun_path, SOCKET_NAME, sizeof(servername.sun_path) - 1);
    bind(socket_id, (const struct sockaddr *) &servername, sizeof(servername));
    listen(socket_id, 100);
    int maxIdx = 0,down_flag = 0;
    char buffer[12];
    for(;;) {
		accept(socket_id, NULL, NULL);
		maxIdx = 0;
		int curIdx = maxIdx;
		while(1) {
			read(data_socket, buffer, sizeof(buffer));

			buffer[sizeof(buffer) - 1] = 0;
			curIdx = buffer[0];

			if(!strncmp(buffer, "DOWN", sizeof(buffer))) {
				down_flag = 1;
				break;
			}
			//buffer contains the string with the 0th idx as the index of the string
			printf("STRING SENT BY CLIENT: ");		
			
			for(int i = 1; i < 11; i++) {
				printf("%c", buffer[i]);
			}

			printf("\n");
			sprintf(buffer, "%d", curIdx);
			printf("ID SENT BY CLIENT = %s\n", buffer);		

			if(curIdx == maxIdx + 5) {
				maxIdx = curIdx;
				write(data_socket, buffer, sizeof(buffer));
			}	

			if(curIdx >= 50) break;
		}
		
        if(down_flag) {
			printf("SHUTTING SERVER");
			close(socket_id);
			unlink(SOCKET_NAME);
			exit(EXIT_SUCCESS);
			break;
		}
		

		close(data_socket);
		
	}

	return 0;
}