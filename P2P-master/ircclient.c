/*   COMPILE:    gcc -o client client.c -lnsl                           */ 
/*   TO RUN:     client  server-machine-name                            */ 
 
#include <stdio.h> 
#include <sys/types.h> 
#include <sys/socket.h>  /* define socket */ 
#include <netinet/in.h>  /* define internet socket */ 
#include <netdb.h>       /* define internet socket */ 
 
#define SERVER_PORT 7777     /* define a server port number */ 
 
int main( int argc, char* argv[] ) 
{ 
    int sd; 
    struct sockaddr_in server_addr = { AF_INET, htons( SERVER_PORT ) }; 
    char buf[1024]; 
    struct hostent *hp; 
 
    if( argc != 2 ) 
    { 
      printf( "Usage: %s hostname\n", argv[0] ); 
      exit(1); 
    } 
 
    /* get the host */ 
    if( ( hp = gethostbyname( argv[1] ) ) == NULL ) 
    { 
      printf( "%s: %s unknown host\n", argv[0], argv[1] ); 
      exit( 1 ); 
    } 
    bcopy( hp->h_addr_list[0], (char*)&server_addr.sin_addr, hp->h_length ); 
 
    /* create a socket */ 
    if( ( sd = socket( AF_INET, SOCK_STREAM, 0 ) ) == -1 ) 
    { 
      perror( "client: socket failed" ); 
      exit( 1 ); 
    } 
 
    /* connect a socket */ 
    if( connect( sd, (struct sockaddr*)&server_addr, 
		 sizeof(server_addr) ) == -1 ) 
    { 
      perror( "client: connect FAILED:" ); 
      exit( 1 ); 
    } 
 
    printf("connect() successful!\n"); 
    printf("Input get file command\n" ); 
 
    while( scanf( "%s", buf) != EOF) 
    { 
      write(sd, buf, sizeof(buf)); 

      read(sd, buf, sizeof(buf)); 
      
      printf("Download Successful"); 
    } 
 
    close(sd); 
    return(0); 
} 
