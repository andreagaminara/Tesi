#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <sys/socket.h>
#include <resolv.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <time.h>
#include <pthread.h>

float *results;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
 
struct args {
    char *hostname;
    int version;
    int port;
    char *ca_cert;
    char *ciphersuite;
    int i;
};
 
void *thread_tls(void* args)
{   
    SSL_CTX *ctx;
    int server;
    SSL *ssl;    
    struct hostent *host;
    struct sockaddr_in addr;
 
    struct args* a = (struct args*)args;
 
    SSL_library_init();
 
    OpenSSL_add_all_algorithms();  /* Load cryptos, et.al. */
    SSL_load_error_strings();   /* Bring in and register error messages */
    ctx = SSL_CTX_new(TLS_client_method());   /* Create new context */
    if ( ctx == NULL )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    
    if(a->version == 2){
    	SSL_CTX_set_max_proto_version(ctx, TLS1_2_VERSION);
    }
    else {
    	SSL_CTX_set_min_proto_version(ctx, TLS1_3_VERSION);
    }
    
 
    if ( (host = gethostbyname(a->hostname)) == NULL )
    {
        perror(a->hostname);
        abort();
    }
    server = socket(PF_INET, SOCK_STREAM, 0);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(a->port);
    addr.sin_addr.s_addr = *(long*)(host->h_addr);
    if ( connect(server, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
    {
        close(server);
        perror(a->hostname);
        abort();
    }
    
    if(SSL_CTX_load_verify_locations(ctx, a->ca_cert, NULL) == 0) {
    	printf("Error while loading certificates\n");
    	exit(-1);
    }
    
    //SSL_CTX_set_security_level(ctx, 0);
    
    ssl = SSL_new(ctx);      /* create new SSL connection state */
    SSL_set_fd(ssl, server);    /* attach the socket descriptor */
    
    if(a->version == 2){
	if(SSL_set_cipher_list(ssl, a->ciphersuite) == 0) {
		printf("Error while selecting ciphersuite\n");
	    	exit(-1);
	}
    }
    else {
    	if(SSL_set_ciphersuites(ssl, a->ciphersuite) == 0) {
		printf("Error while selecting ciphersuite\n");
	    	exit(-1);
	}	
    }
    
    clock_t before = clock();
    
    if ( SSL_connect(ssl) == -1 ) {  /* perform the connection */
        printf("Client %d error during connection\n", a->i);
        pthread_mutex_lock(&lock);
        results[a->i] = 0.0;
        pthread_mutex_unlock(&lock);
    }
    else
    {  
 	clock_t difference = clock() - before;
  	float msec = (float) difference * 1000 / (float)CLOCKS_PER_SEC;
  	
  	printf("Client %d correctly connected in %f ms\n", a->i, msec);
  	pthread_mutex_lock(&lock);
        results[a->i] = msec;
        pthread_mutex_unlock(&lock);
        SSL_free(ssl);        /* release connection state */
    }
    close(server);         /* close socket */
    SSL_CTX_free(ctx);        /* release context */
    
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
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
 
    if ( argc != 7 )
    {
        printf("Usage: %s <hostname> <version> <portnum> <ca_cert> <ciphersuite> <num_thread>\n", argv[0]);
        exit(-1);
    }
    
    num_thread = atoi(argv[6]);
    threads = malloc(num_thread*sizeof(pthread_t));
    results = malloc(num_thread*sizeof(float));
    
    
    for(i=0; i<num_thread; i++) {
        struct args *a = (struct args*)malloc(sizeof(struct args));
        a->hostname = argv[1];
        a->version = atoi(argv[2]);
        a->port = atoi(argv[3]);
        a->ca_cert = argv[4];
        a->ciphersuite = argv[5];
    	a->i = i;
     	rc = pthread_create(&threads[i], NULL, thread_tls, (void *)a);
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
    strcat(filename, "results/tls1_");
    strcat(filename, argv[2]);
    strcat(filename,"_results_");
    strcat(filename, argv[5]);
    strcat(filename, "_");
    strcat(filename, argv[6]);
    
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
