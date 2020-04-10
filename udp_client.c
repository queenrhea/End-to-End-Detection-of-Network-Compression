
struct sockaddr_in serv_addr; // Server address data structure.
struct hostent *server;      // Server data structure.

sockfd = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP ); // Create a UDP socket.

if ( sockfd < 0 )
  error( "ERROR opening socket" );

server = gethostbyname( host_name ); // Convert URL to IP.

if ( server == NULL )
  error( "ERROR, no such host" );

// Zero out the server address structure.

bzero( ( char* ) &serv_addr, sizeof( serv_addr ) );

serv_addr.sin_family = AF_INET;

// Copy the server's IP address to the server address structure.

bcopy( ( char* )server->h_addr, ( char* ) &serv_addr.sin_addr.s_addr, server->h_length );

// Convert the port number integer to network big-endian style and save it to the server address structure.

serv_addr.sin_port = htons( portno );



int sendto(int sockfd, const void *msg, int len, unsigned int flags,
const struct sockaddr *to, socklen_t tolen);
