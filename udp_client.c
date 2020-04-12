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


//------------------------------------------

fillBuf(buf,size)
register char *buf;
register int size;
{
	register int i;

	for ( i = 0; i < size; i++)
		*buf++ = bufval;
	bufval++;
}



fillBuf(mbuf.buf, BUFSIZE);

	for ( i = 0; i < count; i++) {

		printf("client msg no [%d]\n", i);

		mbuf.count = i;

		/* write msg to remote system
		 * sock
		 * buf
		 * sizeof (union msg)
		 * 0,
		 * client
		 * sizeof (client)
		 */
		if( rc = sendto(sock,&mbuf,sizeof (struct msgbuf),0,
			 &client,sizeof (client)) < 0 ) {
			/* buffers aren't available locally at the moment,
			 * try again.
			 */
			if (errno == ENOBUFS)
				continue;
			perror("sending datagram");
			exit(1);
		}

		fromlen = sizeof (struct sockaddr_in);

		/* read acknowledgement from remote system
		*/
		if (recvfrom(sock, &ackvar, sizeof(long), 0, &from, &fromlen) < 0 ) {
			printf("server error: errno %d\n",errno);
			perror("reading datagram");
			exit(1);
		}
    
    //	struct sockaddr_in from;
