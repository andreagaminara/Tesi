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

float *results;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

struct args {
    char *hostname;
    int port;
    char *ca_cert;
    char* ciphersuite;
    int i;
};

void* thread_dtls(void* args) {
    /* standard variables used in a dtls client*/
    int sockfd = 0;
    struct sockaddr_in servAddr;
    WOLFSSL* ssl = 0;
    WOLFSSL_CTX* ctx = 0;
    
    struct args* a = (struct args*)args;
	
    /* Initialize wolfSSL before assigning ctx */
    wolfSSL_Init();
  
    /* wolfSSL_Debugging_ON(); */

    if ( (ctx = wolfSSL_CTX_new(wolfDTLSv1_2_client_method())) == NULL) {
        fprintf(stderr, "wolfSSL_CTX_new error.\n");
        pthread_exit(NULL);
    }

    /* Load certificates into ctx variable */
    if (wolfSSL_CTX_load_verify_locations(ctx, a->ca_cert, 0)
	    != SSL_SUCCESS) {
        fprintf(stderr, "Error loading %s, please check the file.\n", a->ca_cert);
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
    servAddr.sin_port = htons(a->port);
    if (inet_pton(AF_INET, a->hostname, &servAddr.sin_addr) < 1) {
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
    
    if(wolfSSL_set_cipher_list(ssl, a->ciphersuite) != SSL_SUCCESS){
        printf("Error while selecting ciphersuite\n");
        exit(-1);
    }
    
    clock_t before = clock();
    
    if (wolfSSL_connect(ssl) != SSL_SUCCESS){
	    printf("wolfSSL_connect failed for client %d\n", a->i);
	    pthread_mutex_lock(&lock);
            results[a->i] = 0.0;
            pthread_mutex_unlock(&lock);
    }
    
    else {
    	    clock_t difference = clock() - before;
    	    float msec = (float) difference * 1000 / (float)CLOCKS_PER_SEC;
  	
     	    printf("Client %d correctly connected in %f ms\n", a->i, msec);
    	    pthread_mutex_lock(&lock);
    	    results[a->i] = msec;
    	    pthread_mutex_unlock(&lock);
    	    wolfSSL_free(ssl);
    }

    /* Housekeeping */
    //wolfSSL_shutdown(ssl);
    close(sockfd);
    wolfSSL_CTX_free(ctx);
    //wolfSSL_Cleanup();

    pthread_exit(NULL);
}

int main (int argc, char* argv[])
{
    pthread_t *threads;
    int num_thread;
    int rc;
    int i;
    int nc = 0;
    int nf = 0;
    float total_time = 0.0;
    float min_time;
    float max_time;
    float mean_time;
    float conn_per_sec;
    FILE *fp;
    
    /* Program argument checking */
    if (argc != 6) {
        printf("Usage: %s <hostname> <portnum> <ca_cert> <ciphersuite> <num_thread>\n", argv[0]);
        exit(-1);
    }
    
    num_thread = atoi(argv[5]);
    threads = malloc(num_thread*sizeof(pthread_t));
    results = malloc(num_thread*sizeof(float));
    
    for(i=0; i<num_thread; i++) {
     	struct args *a = (struct args*)malloc(sizeof(struct args));
        a->hostname = argv[1];
        a->port = atoi(argv[2]);
        a->ca_cert = argv[3];
        a->ciphersuite = argv[4];
    	a->i = i;
     	rc = pthread_create(&threads[i], NULL, thread_dtls, (void *)a);
     	if(rc) {
     	     printf("Error: unable to create thread %d\n", rc);
     	     exit(-1);
     	}
    }
    
    for(i=0; i<num_thread; i++) {
     	rc = pthread_join(threads[i], NULL);
     	if(rc) {
     	     printf("Error: unable to join thread %d\n", rc);
     	     exit(-1);
     	}
    }
    
    char filename[100] = "";
    strcat(filename, "dtls1_2_results_");
    strcat(filename, argv[4]);
    strcat(filename, "_");
    strcat(filename, argv[5]);
    
    fp = fopen(filename, "w");
    
    min_time = results[0];
    max_time = results[0];
    
    for(i=0; i<num_thread; i++) {
        if(results[i]==0.0){
       	    fprintf(fp, "ERROR: Thread %d didn't complete the handshake\n", i);
       	    nf++;
        }
        else {
            fprintf(fp, "Thread %d completed the handshake in %f msec\n", i, results[i]);
            nc++;
            total_time += results[i];
            if(results[i] > max_time){
               max_time = results[i];
            }
            if(results[i] < min_time){
               min_time = results[i];
            }
        }
    }
    
    mean_time = total_time / (float) nc;
    conn_per_sec = (float) nc / (total_time/1000);
    
    fprintf(fp, "\nNumber of completed connections: %d\n", nc);
    fprintf(fp, "Number of failed connections: %d\n", nf);
    fprintf(fp, "The minimum handshake time is : %f ms\n", min_time);
    fprintf(fp, "The maximum handshake time is : %f ms\n", max_time);
    fprintf(fp, "The mean handshake time is : %f ms\n", mean_time);
    fprintf(fp, "The server is able to manage %f connections per second\n", conn_per_sec);
       
    fclose(fp);
    
    return 0;   
}

