#include <wolfssl/options.h>
#include <stdio.h>                  /* standard in/out procedures */
#include <stdlib.h>                 /* defines system calls */
#include <string.h>                 /* necessary for memset */
#include <netdb.h>
#include <sys/socket.h>             /* used for all socket calls */
#include <netinet/in.h>             /* used for sockaddr_in */
#include <arpa/inet.h>
#include <wolfssl/ssl.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

static int cleanup = 0;                 /* To handle shutdown */
struct sockaddr_in servAddr;        /* our server's address */
struct sockaddr_in cliaddr;         /* the client's address */

#define MSGLEN 4096 

int main(int argc, char** argv)
{
    
    WOLFSSL_CTX* ctx;
    /* Variables for awaiting datagram */
    int on = 1;
    int res = 1;
    int connfd = 0;
    int listenfd = 0;   /* Initialize our socket */
    WOLFSSL* ssl = NULL;
    socklen_t cliLen;
    socklen_t len = sizeof(int);
     unsigned char b[MSGLEN];      /* watch for incoming messages */

    int portnum;
    char *cert_file;
    char *key_file; 
    
    
    if ( argc != 4 )
    {
        printf("Usage: %s <portnum> <cert_file> <key_file>\n", argv[0]);
        exit(-1);
    }
    
    portnum = atoi(argv[1]);
    cert_file = argv[2];
    key_file = argv[3];  


    /* Initialize wolfSSL */
    wolfSSL_Init();

    /* Set ctx to DTLS 1.2 */
    if ((ctx = wolfSSL_CTX_new(wolfDTLSv1_2_server_method())) == NULL) {
        printf("wolfSSL_CTX_new error.\n");
        exit(-1);
    }
    
    /*Load server certificates */
    if (wolfSSL_CTX_use_certificate_file(ctx, cert_file, SSL_FILETYPE_PEM) != 
                                                                 SSL_SUCCESS) {
        printf("Error loading %s, please check the file.\n", cert_file);
        exit(-1);
    }
    
    /* Load server Keys */
    if (wolfSSL_CTX_use_PrivateKey_file(ctx, key_file,
                SSL_FILETYPE_PEM) != SSL_SUCCESS) {
        printf("Error loading %s, please check the file.\n", key_file);
        exit(-1);
    }

    /*WOLFSSL_DH *dh_2048 = NULL;
    FILE *paramfile = fopen("dh_param_2048.pem", "r");

    if (paramfile) {
    	dh_2048 = wolfSSL_PEM_read_DHparams(paramfile, NULL, NULL, NULL);
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
    
    if (wolfSSL_CTX_set_tmp_dh(ctx, dh_2048) != 1) {
        printf("Impossible to set dh parameters.\n");
        exit(-1);
    }*/
    if(wolfSSL_CTX_SetTmpDH_file(ctx, "dh_param_2048.pem", SSL_FILETYPE_PEM) != SSL_SUCCESS) {
     	printf("Impossible to set dh parameters.\n");
        exit(-1);
    }
    
   

    while (cleanup != 1) {
        /* Create a UDP/IP socket */
        if ((listenfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
            printf("Cannot create socket.\n");
            exit(-1);
        }
        //printf("Socket allocated\n");

        /* clear servAddr each loop */
        memset((char *)&servAddr, 0, sizeof(servAddr));

        /* host-to-network-long conversion (htonl) */
        /* host-to-network-short conversion (htons) */
        servAddr.sin_family = AF_INET;
        servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servAddr.sin_port = htons(portnum);

        /* Eliminate socket already in use error */
        res = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, len);
        if (res < 0) {
            printf("Setsockopt SO_REUSEADDR failed.\n");
            break;
        }

        /*Bind Socket*/
        if (bind(listenfd, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
            printf("Bind failed.\n");
            break;
        }

        printf("Awaiting client connection on port %d\n", portnum);

        cliLen = sizeof(cliaddr);
        connfd = (int)recvfrom(listenfd, (char *)&b, sizeof(b), MSG_PEEK,
                (struct sockaddr*)&cliaddr, &cliLen);

        if (connfd < 0) {
            printf("No clients in que, enter idle state\n");
            close(listenfd);
            continue;
        }
        else if (connfd > 0) {
            if (connect(listenfd, (const struct sockaddr *)&cliaddr,
                        sizeof(cliaddr)) != 0) {
                printf("Udp connect failed.\n");
                break;
            }
        }
        else {
            printf("Recvfrom failed.\n");
            break;
        }
        printf("Connected!\n");

        /* Create the WOLFSSL Object */
        if ((ssl = wolfSSL_new(ctx)) == NULL) {
            printf("wolfSSL_new error.\n");
            exit(-1);
        }

#ifdef WOLFSSL_DTLS_SET_PEER
        /* Alternative to UDP connect */
        wolfSSL_dtls_set_peer(ssl, &cliaddr, cliLen);
#endif

        /* set the session ssl to client connection port */
        wolfSSL_set_fd(ssl, listenfd);

        if (wolfSSL_accept(ssl) != SSL_SUCCESS) {
            printf("wolfSSL_accept failed.\n");
        }
        else {
            printf("Client successfully connected\n");
        }

        //wolfSSL_set_fd(ssl, 0);
        //wolfSSL_shutdown(ssl);
        int sd = wolfSSL_get_fd(ssl);
        wolfSSL_free(ssl);
        close(sd);
        cleanup = 0;
    }
    
    if (cleanup == 1) {
        wolfSSL_set_fd(ssl, 0);
        wolfSSL_shutdown(ssl);
        wolfSSL_free(ssl);
        close(listenfd);
    }

    wolfSSL_CTX_free(ctx);
    wolfSSL_Cleanup();

    return 0;
}