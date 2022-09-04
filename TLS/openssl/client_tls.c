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

int main(int argc, char *argv[])
{
    char *hostname;
    int version;
    int port;
    char *ca_cert;
    char *ciphersuite;
    
    SSL_CTX *ctx;
    int server;
    SSL *ssl;    
    struct hostent *host;
    struct sockaddr_in addr;	   
 
    if ( argc != 6 )
    {
        printf("Usage: %s <hostname> <version> <portnum> <ca_cert> <ciphersuite>\n", argv[0]);
        exit(-1);
    }
    
    hostname = argv[1];
    version = atoi(argv[2]);
    port = atoi(argv[3]);
    ca_cert = argv[4];
    ciphersuite = argv[5];
    
    SSL_library_init();
 
    OpenSSL_add_all_algorithms();  /* Load cryptos, et.al. */
    SSL_load_error_strings();   /* Bring in and register error messages */
    ctx = SSL_CTX_new(TLS_client_method());   /* Create new context */
    if ( ctx == NULL )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    
    if(version == 2){
    	SSL_CTX_set_max_proto_version(ctx, TLS1_2_VERSION);
    }
    else {
    	SSL_CTX_set_min_proto_version(ctx, TLS1_3_VERSION);
    }
    
 
    if ( (host = gethostbyname(hostname)) == NULL )
    {
        perror(hostname);
        abort();
    }
    server = socket(PF_INET, SOCK_STREAM, 0);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = *(long*)(host->h_addr);
    if ( connect(server, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
    {
        close(server);
        perror(hostname);
        abort();
    }
    
    if(SSL_CTX_load_verify_locations(ctx, ca_cert, NULL) == 0) {
    	printf("Error while loading certificates\n");
    	exit(-1);
    }
    
    //SSL_CTX_set_security_level(ctx, 0);
    
    ssl = SSL_new(ctx);      /* create new SSL connection state */
    SSL_set_fd(ssl, server);    /* attach the socket descriptor */
    
    if(version == 2){
	if(SSL_set_cipher_list(ssl, ciphersuite) == 0) {
		printf("Error while selecting ciphersuite\n");
	    	exit(-1);
	}
    }
    else {
    	if(SSL_set_ciphersuites(ssl, ciphersuite) == 0) {
		printf("Error while selecting ciphersuite\n");
	    	exit(-1);
	}	
    }
    
    clock_t before = clock();
    
    if ( SSL_connect(ssl) == -1 ) {  /* perform the connection */
        printf("Client error during connection\n");
    }
    else
    {  
 	clock_t difference = clock() - before;
  	float msec = (float) difference * 1000 / (float)CLOCKS_PER_SEC;
  	
  	printf("Client correctly connected in %f ms\n", msec);
        SSL_free(ssl);        /* release connection state */
    }
    close(server);         /* close socket */
    SSL_CTX_free(ctx);        /* release context */
    
    return 0;   
}
