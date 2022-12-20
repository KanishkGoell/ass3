#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>
#include<time.h>
struct sockaddr_un addr;
#define SOCKET_NAME "CustomSocket"

char ** generateRandomString();

int main(int argc, char* argv[]){
    char ** randStr = generateRandomString();
    int data_socket;
    char buffer[10];
	socket(AF_UNIX, SOCK_SEQPACKET, 0) ;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCKET_NAME);
    connect(data_socket, (const struct sockaddr *) &addr, sizeof(addr)) ; 

    
    int k = 0, p = 1;
    while(k<=50) {
		while(p<12) {
			if(p == 0) {
				printf("%d ", randStr[k][p]);
			}
			else printf("%c", randStr[k][p]);
            p++;
		}
        k++;
		printf("\n");
	}
		int lastIdx = 1;
		for(;;) {
			printf("sending Strings Indexed from %d to %d\n", lastIdx, lastIdx + 4);
            int i = lastIdx;
			while( i < lastIdx + 5) {
				write(data_socket, randStr[i], strlen(randStr[i]) + 1);
                i++;
			}
			read(data_socket, buffer, sizeof(buffer)) ; 

			buffer[sizeof(buffer) - 1] = 0;
			int finalIdx = atoi(buffer);
			
			printf("ID sent back: %s\n\n", buffer);
			if(finalIdx == 50) {
				printf("Successfully sent all Strings\n");
				close(data_socket);
				exit(EXIT_SUCCESS);
				break;
			}
			else {
				lastIdx = finalIdx + 1;
			}
		}
}

char ** generateRandomString(){
    char** str;
    int i =0;
    while(i<=50) {
        int j = 1;
		while(j<=10){
			str[i][j] = 0;
            j++;
		}
        i++;
	}
    i = 0 ;
    
    while(i<=50) {
        int j = 1;
		while(j<=10) {
			str[i][j] = rand() % 26 + 65;
            str[i][0] = i;
            j++;
		}
        i++;
	}
    return str;
}