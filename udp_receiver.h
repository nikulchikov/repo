/*-------------------------------------------------------------------------
 *
 *   FILE
 *	udp_receiver.h
 *
 *   AUTHOR	
 * 	Arkadi Kozlov <arkashamain@mail.ru>
 *
 *   DATE
 *	19/10/2003
 *
 *   CHANGES
 *
 *-------------------------------------------------------------------------
 */

#ifndef UDP_RECEIVER
#define UDP_RECEIVER

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <string.h>

#include <exception>
#include <string>
#include <vector>

using std::exception;
using std::string;
using std::vector;

class udp_receiver {

  int socket_num;

  bool inited;

  struct sockaddr_in client_addr;

  short len;

  unsigned long port;

  public:

    class udp_receiver_exception: public exception {

      string what_str;

      public:

        udp_receiver_exception( string whats );
        virtual const char* what() const throw();
        virtual ~udp_receiver_exception( ) throw ( );
    };

    class received_zero_bytes_pack: public exception {

      public:
        virtual const char* what() const throw();
    };

  private:

    void init( ) throw ( udp_receiver_exception );

  public:

    udp_receiver( );

    udp_receiver( const udp_receiver& rcv );

    udp_receiver( unsigned long port ) throw ( udp_receiver_exception);

    ~udp_receiver( );

    static const int mtu = 1500; // maximum transfer unit

    udp_receiver &operator>>( vector<unsigned char> &in_buff ) throw ( received_zero_bytes_pack );

    udp_receiver &operator>>( char *in_buff ) throw ( received_zero_bytes_pack );

    udp_receiver &operator=( const udp_receiver &rcv );

    long get_length( );

    string get_last_pack_sender_ip( );
};

#endif
