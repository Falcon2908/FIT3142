#include <sys/socket.h>  
#include <netinet/in.h>  
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h> 
#include <arpa/inet.h> 
#include <unistd.h> 

int main() 
{  
    int sock_desc = socket(AF_INET, SOCK_STREAM, 0); /*Setting up socket for connection*/
    if (sock_desc == -1)
    {
        printf("cannot create socket!\n");
        return -1;
    }

    struct sockaddr_in client;  /*Connecting to localhost port*/
    memset(&client, 0, sizeof(client));  
    client.sin_family = AF_INET;  
    client.sin_addr.s_addr = inet_addr("127.0.0.1");  
    client.sin_port = htons(8080);  

    if (connect(sock_desc, (struct sockaddr*)&client, sizeof(client)) != 0) /*Error handling*/
    {
        printf("cannot connect to server!\n");
        close(sock_desc);
        return -1;
    }

    char buf[100]; /*Setting data limit to 100 caharacters*/
    char c = '\n'; /*Sending newline after every input*/
    char *p_buf; /*In order to set a proper pointer address instead of memory*/
    int ret_val, len;  /*Retrun Values and length*/

    while(!feof(stdin)) 
    {      
        scanf("%s", buf);

        len = strlen(buf);
        p_buf = buf;

        while (len > 0)
        {
            ret_val = send(sock_desc, p_buf, len, 0); /*Sending Byte by Byte*/     
            if (ret_val == -1)
            {
                printf("cannot write to server!\n");
                break;
            }

            p_buf += ret_val;
            len -= ret_val;
        }

        ret_val = send(sock_desc, &c, 1, 0);   /*Sending NewLine*/   
        if (ret_val == -1)
        {
            printf("cannot write to server!\n");
            break;
        }

        if (strcmp(buf, "exit") == 0) /*Exttting client*/     
            break;  
    }  

    close(sock_desc);  
    printf("client disconnected\n");

    return 0;  
} 