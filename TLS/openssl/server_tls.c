#include <errno.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <resolv.h>
#include "openssl/ssl.h"
#include "openssl/err.h"
 

 
int main(int argc, char *argv[])
{   
    SSL_CTX *ctx;
    int server;
    struct sockaddr_in addr;
    
    int portnum;
    char *cert_file;
    char *key_file;
    int version; 
    
    
    if ( argc != 5 )
    {
        printf("Usage: %s <version> <portnum> <cert_file> <key_file>\n", argv[0]);
        exit(-1);
    }
    
    version = atoi(argv[1]);
    portnum = atoi(argv[2]);
    cert_file = argv[3];
    key_file = argv[4];    
 
 // Initialize the SSL library
    SSL_library_init();
 
    OpenSSL_add_all_algorithms();  /* load & register all cryptos, etc. */
    SSL_load_error_strings();   /* load all error messages */
    ctx = SSL_CTX_new(TLS_server_method());   /* create new context from method */
    
    if ( ctx == NULL )
    {
        ERR_print_errors_fp(stderr);
        exit(-1);
    }   
    
    if(version == 2){
    	SSL_CTX_set_max_proto_version(ctx, TLS1_2_VERSION);
    }
    else {
    	SSL_CTX_set_min_proto_version(ctx, TLS1_3_VERSION);
    }
    
    /* set the local certificate from CertFile */
    if ( SSL_CTX_use_certificate_file(ctx, cert_file, SSL_FILETYPE_PEM) <= 0 )
    {
        ERR_print_errors_fp(stderr);
        exit(-1);
    }
    /* set the private key from KeyFile (may be the same as CertFile) */
    if ( SSL_CTX_use_PrivateKey_file(ctx, key_file, SSL_FILETYPE_PEM) <= 0 )
    {
        ERR_print_errors_fp(stderr);
        exit(-1);
    }
    /* verify private key */
    if ( !SSL_CTX_check_private_key(ctx) )
    {
        fprintf(stderr, "Private key does not match the public certificate\n");
        exit(-1);
    }
    
    DH *dh_2048 = NULL;
    FILE *paramfile = fopen("dh_param_2048.pem", "r");

    if (paramfile) {
    	dh_2048 = PEM_read_DHparams(paramfile, NULL, NULL, NULL);
    	fclose(paramfile);
    } 
    else {
        printf("Impossible to open dh parameters file.\n");
        exit(-1);
    }
 
    if (dh_2048 == NULL) {
        printf("Impossible to read dh parameters.\n");
        exit(-1);
    
    }
    
    if (SSL_CTX_set_tmp_dh(ctx, dh_2048) != 1) {
        printf("Impossible to set dh parameters.\n");
        exit(-1);
    }
    
    
    server = socket(PF_INET, SOCK_STREAM, 0);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(portnum);
    addr.sin_addr.s_addr = INADDR_ANY;
    
    if (bind(server, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
    {
        printf("Can't bind port\n");
        exit(-1);
    }
    
    if ( listen(server, 10) != 0 )
    {
        printf("Can't configure listening port\n");
        exit(-1);
    }
    
    while (1)
    {   
        struct sockaddr_in addr;
        socklen_t len = sizeof(addr);
        SSL *ssl;
        int sd;
 
        int client = accept(server, (struct sockaddr*)&addr, &len);  /* accept connection as usual */
        printf("Connection: %s:%d\n",inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
        ssl = SSL_new(ctx);              /* get new SSL state with context */
        SSL_set_fd(ssl, client);      /* set connection socket to SSL state */
        
        if ( SSL_accept(ssl) == -1 )     /* do SSL-protocol accept */
             ERR_print_errors_fp(stderr);
    	else
    	{
    	     printf("Client correctly connected\n");
    	}
    	
    	sd = SSL_get_fd(ssl);       /* get socket connection */
    	SSL_free(ssl);         /* release SSL state */
    	close(sd);          /* close connection */ 	
    }
    
    close(server);          /* close server socket */
    SSL_CTX_free(ctx);         /* release context */
}
