#include <wolfssl/options.h>
#include <unistd.h>
#include <wolfssl/ssl.h>
#include <netdb.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


int main (int argc, char* argv[])
{
    char *hostname;
    int port;
    char *ca_cert;
    char* ciphersuite;
    
    /* standard variables used in a dtls client*/
    int sockfd = 0;
    struct sockaddr_in servAddr;
    WOLFSSL* ssl = 0;
    WOLFSSL_CTX* ctx = 0;
    
    /* Program argument checking */
    if (argc != 5) {
        printf("Usage: %s <hostname> <portnum> <ca_cert> <ciphersuite>\n", argv[0]);
        exit(-1);
    }
    
    hostname = argv[1];
    port = atoi(argv[2]);
    ca_cert = argv[3];
    ciphersuite = argv[4];
    
    /* Initialize wolfSSL before assigning ctx */
    wolfSSL_Init();
  
    /* wolfSSL_Debugging_ON(); */

    if ( (ctx = wolfSSL_CTX_new(wolfDTLSv1_2_client_method())) == NULL) {
        fprintf(stderr, "wolfSSL_CTX_new error.\n");
        pthread_exit(NULL);
    }

    /* Load certificates into ctx variable */
    if (wolfSSL_CTX_load_verify_locations(ctx, ca_cert, 0)
	    != SSL_SUCCESS) {
        fprintf(stderr, "Error loading %s, please check the file.\n", ca_cert);
        pthread_exit(NULL);
    }

    /* Assign ssl variable */
    ssl = wolfSSL_new(ctx);
    if (ssl == NULL) {
        printf("Unable to get ssl object\n");
        pthread_exit(NULL);
    }

    /* servAddr setup */
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
    if (inet_pton(AF_INET, hostname, &servAddr.sin_addr) < 1) {
        printf("Error and/or invalid IP address\n");
        pthread_exit(NULL);
    }

    wolfSSL_dtls_set_peer(ssl, &servAddr, sizeof(servAddr));

    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
       printf("Cannot create a socket.\n");
       pthread_exit(NULL);;
    }

    /* Set the file descriptor for ssl and connect with ssl variable */
    wolfSSL_set_fd(ssl, sockfd);
    
    if(wolfSSL_set_cipher_list(ssl, ciphersuite) != SSL_SUCCESS){
        printf("Error while selecting ciphersuite\n");
        exit(-1);
    }
    
    clock_t before = clock();
    
    if (wolfSSL_connect(ssl) != SSL_SUCCESS){
	    printf("wolfSSL_connect failed\n");
	    
    }
    
    else {
    	    clock_t difference = clock() - before;
    	    float msec = (float) difference * 1000 / (float)CLOCKS_PER_SEC;  	
     	    printf("Client correctly connected in %f ms\n", msec);
    	    wolfSSL_free(ssl);
    }

    /* Housekeeping */
    //wolfSSL_shutdown(ssl);
    close(sockfd);
    wolfSSL_CTX_free(ctx);
    //wolfSSL_Cleanup();
    
    
    return 0;   
}

