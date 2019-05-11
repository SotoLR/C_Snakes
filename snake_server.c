#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/poll.h>

#include "sockets.h"
#include "snake.h"
#include "fatal_error.h"

#define CLIENT_MSG_LEN 4
#define SERVER_MSG_LEN 32

#define MAX_QUEUE 5
#define BUFFER_SIZE 200
#define DEFAULT_PORT 8989

// Data that will be sent to each structure
typedef struct data_struct {
    // The file descriptor for the socket
    int connection_fd;
    
} thread_data_t;

void usage(char * program);
void waitForConnections(int server_fd);
void* attentionThread(void* arg);


int interrupt_exit = 0;
int clients[2];
int client_count = 0;

int main(int argc, char * argv[])
{
    if (argc != 2)
    {
        usage(argv[0]);
    }
    
    int server_fd;
    
    // Initialize the random seed
    srand(time(NULL));
    
    server_fd = initServer(argv[1], MAX_QUEUE);
    
    // Start waiting for incoming connections
    waitForConnections(server_fd);
    
    return 0;
}

void usage(char * program)
{
    printf("Usage: %s {port_number}\n", program);
    exit(EXIT_SUCCESS);
}

void waitForConnections(int server_fd)
{
    struct sockaddr_in client_address;
    socklen_t client_address_size;
    char client_presentation[INET_ADDRSTRLEN];
    int client_fd;
    pthread_t new_tid;
    thread_data_t * connection_data = NULL;
    int poll_response;
    int timeout = 500;		// Time in milliseconds (0.5 seconds)
    int i = 0;

    // Get the size of the structure to store client information
    client_address_size = sizeof(client_address);

    while (client_count < 2)
    {
        // Create a structure array to hold the file descriptors to poll
        struct pollfd test_fds[1];
        // Fill in the structure
        test_fds[0].fd = server_fd;
        test_fds[0].events = POLLIN;    // Check for incomming data

        poll_response = poll(test_fds, 1, timeout);
        //Interruption (system call)
        if (poll_response == -1)
        {
            /*if (errno == EINTR)
             {
             break;
             }*/
            break;
        }
        //Check for interruptions
        if (poll_response == 0)
        {
            if (interrupt_exit)
                break;
        }
        //Continue bank operations
        if (poll_response > 0)
        {
            if (test_fds[0].revents & POLLIN)
            {
                // ACCEPT
                // Wait for a client connection
                client_fd = accept(server_fd, (struct sockaddr *)&client_address, &client_address_size);
                clients[i] = client_fd;
                i++;
                if (client_fd == -1)
                {
                    fatalError("ERROR: accept");
                }

                // Get the data from the client
                inet_ntop(client_address.sin_family, &client_address.sin_addr, client_presentation, sizeof client_presentation);
                printf("Received incomming connection from %s on port %d\n", client_presentation, client_address.sin_port);
                connection_data = malloc(sizeof(thread_data_t));
                connection_data->connection_fd = client_fd;

                // CREATE A THREAD
                if (pthread_create(&new_tid, NULL, attentionThread, connection_data) == 0){
                    printf("Thread created\n");
                    client_count++;
                }

            }
        }
    }
}

void* attentionThread(void* arg)
{
    int poll_response;
    int timeout = 500;
    thread_data_t * data = (thread_data_t*)arg;
    char buffer[BUFFER_SIZE];
    int response;
    recvString(data->connection_fd, buffer, BUFFER_SIZE);

    while (!interrupt_exit)
    {
        // Create a structure array to hold the file descriptors to poll
        struct pollfd test_fds[1];
        // Fill in the structure
        test_fds[0].fd = data->connection_fd;
        test_fds[0].events = POLLIN;    // Check for incomming data
        poll_response = poll(test_fds, 1, timeout);

        if (poll_response == -1)
        {
            /*if (errno == EINTR)
            {
                break;
            }*/
            break;
        }
        // Receive the request
        else if (poll_response > 0)
        {
            if (recvString(data->connection_fd, buffer, BUFFER_SIZE) == 0)
            {
                printf("Client disconnected\n");
                break;
            }
            else
            {
                /*printf("Client1: %d\n", clients[0]);
                printf("Client2: %d\n", clients[1]);
                printf("Connection_fd %d\n", data->connection_fd);*/
                if(data->connection_fd == clients[0])
                {
                    /*
                    response = atoi(buffer);
                    printf("Player 1 said: %d\n", response);
                    sprintf(buffer, "%d", response);
                    send(data->connection_fd, buffer, BUFFER_SIZE, 0);
                    */
                }
                else
                {
                    /*
                    response = atoi(buffer);
                    printf("Player 2 said: %d\n", response);
                    sprintf(buffer, "%d", response);
                    send(data->connection_fd, buffer, BUFFER_SIZE, 0);
                    */
                }
            }

        }
    }
    client_count--;
    pthread_exit(NULL);
}