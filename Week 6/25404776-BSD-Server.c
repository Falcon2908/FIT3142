#include <sys/socket.h>  
#include <netinet/in.h>  
#include <stdio.h>  
#include <string.h> 
#include <stdlib.h>  
#include <arpa/inet.h> 
#include <unistd.h> 

int main() 
{  
    int sock_desc = socket(AF_INET, SOCK_STREAM, 0); /*Creating Socet connection*/

    if (sock_desc == -1) /* Error Handling*/
    {
        printf("cannot create socket!\n");
        return 0;
    }

    struct sockaddr_in server;  /*Initializing socket address*/
    memset(&server, 0, sizeof(server));  /*Allocation memory*/

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;  
    server.sin_port = htons(8080);  /*Allocating Port and Ip address*/

    if (bind(sock_desc, (struct sockaddr*)&server, sizeof(server)) != 0) /*Binding Socket to server*/
    {
        printf("cannot bind socket!\n");
        close(sock_desc);  
        return 1;
    }

    if (listen(sock_desc, 20) != 0) /*Error Handling on socket*/
    {
        printf("cannot listen on socket!\n");
        close(sock_desc);  
        return 1;
    }

    struct sockaddr_in client;  /*Creating Client Input*/
    memset(&client, 0, sizeof(client));  
    socklen_t len = sizeof(client); 
    int temp_sock_desc = accept(sock_desc, (struct sockaddr*)&client, &len);

    if (temp_sock_desc == -1)
    {
        printf("Cannot accept client!\n");
        close(sock_desc);  
        return 1;
    }

    char buf[100];  
    int ret_val;  

    while(1) 
    {      
        ret_val = recv(temp_sock_desc, buf, 100, 0);   /*Getting data*/    
        if (ret_val == -1)
        {
            printf("Cannot read from client!\n");
            break;
        }

        if (ret_val == 0)
        {
            printf("Client disconnected.\n");
            break;
        }

        if (ret_val > 0)          
            printf("%*.*s", ret_val, ret_val, buf);  

        if (strcmp(buf, "exit") == 0)   
        {
            printf("Client Closing Server.\n");      
            break;     
        } 
    }

    close(temp_sock_desc);  
    close(sock_desc);  

    printf("server disconnected\n");
    return 0;  
} 