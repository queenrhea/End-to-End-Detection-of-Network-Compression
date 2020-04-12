#define PCKT_LEN 8192


struct sockaddr_in serv_addr; // Server address data structure.
struct hostent *server;      // Server data structure.

sockfd = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP ); // Create a UDP socket.

if ( sockfd < 0 )
  error( "ERROR opening socket" );

server = gethostbyname( host_name ); // Convert URL to IP.

if ( server == NULL )
  error( "ERROR, no such host" );


serv_addr.sin_family = AF_INET;




int sendto(int sockfd, const void *msg, int len, unsigned int flags,
const struct sockaddr *to, socklen_t tolen);


// buffer to hold the packet
    char buffer[PCKT_LEN];

// set the buffer to 0 for all bytes
    memset(buffer, 0, PCKT_LEN);
