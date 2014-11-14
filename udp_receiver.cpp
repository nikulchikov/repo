
#include "udp_receiver.h"

#include <unistd.h>

#include <sstream>

#include <iostream>
using namespace std;

udp_receiver::udp_receiver_exception::udp_receiver_exception( string whats ) {

  this->what_str = whats;
}

const char* udp_receiver::udp_receiver_exception::what() const throw( ) {

  return this->what_str.c_str();
}

udp_receiver::udp_receiver_exception::~udp_receiver_exception( ) throw ( ) {
}

const char* udp_receiver::received_zero_bytes_pack::what() const throw( ) {

  return " Received zero-lenght UDP pack/Получен UDP пакет нулевой длины ";
}

udp_receiver::udp_receiver( unsigned long port ) throw ( udp_receiver_exception )

  : port( port ) {

  init( );
}

udp_receiver &udp_receiver::operator>>( vector<unsigned char> &in_buff ) throw ( received_zero_bytes_pack ) {

  if( !inited )

    return *this;

  bzero( &client_addr, sizeof( client_addr ) );

  int leng = sizeof( client_addr );

  char buff[ mtu ];

  len = recvfrom( socket_num, buff, mtu, 0, (struct sockaddr *) &client_addr, ( socklen_t * ) &leng );

  if( !len ) {

    received_zero_bytes_pack rzbp;

    throw rzbp;
  }

  for( short i=0; i<len; i++)

    in_buff.push_back( *( buff + i ));

  return *this;
}

udp_receiver &udp_receiver::operator>>( char *in_buff ) throw ( received_zero_bytes_pack ) {

  if( !inited )

    return *this;

  len = recv( socket_num, in_buff, mtu, 0);

  if( !len ) {

    received_zero_bytes_pack rzbp;

    throw rzbp;
  }

  return *this;
}

udp_receiver::udp_receiver( ) {

  inited = false;
}

udp_receiver::udp_receiver( const udp_receiver& rcv ) {

  this->port      = rcv.port;

  init( );
}

udp_receiver &udp_receiver::operator=( const udp_receiver& rcv ) {

  this->port      = rcv.port;

  init( );

  return *this;
}

void udp_receiver::init( ) throw ( udp_receiver_exception ) {

  socket_num = socket( AF_INET, SOCK_DGRAM, 0 );

  if( socket_num==-1 ) {

    udp_receiver_exception ure( " Create socket failed/Не могу создать сокет. " );

    throw ure;
  }

  int optval = 1;
  if( setsockopt ( socket_num, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof (int)) != 0 ) {

    close( socket_num );

    udp_receiver_exception ure(" Catch port failed/Не могу захватить порт. ");

    throw ure;
  }

  struct sockaddr_in receiver_addr;

  bzero( &receiver_addr, sizeof( receiver_addr ) );

  receiver_addr.sin_addr.s_addr = INADDR_ANY;
  receiver_addr.sin_family = AF_INET;
  receiver_addr.sin_port = htons( port );

  int sb = bind( socket_num, (struct sockaddr *) &receiver_addr,
                 sizeof(receiver_addr) );
  if( sb==-1 ) {

    close( socket_num );

    udp_receiver_exception ure(" Bind socket failed/Не могу связать сокет. ");

    throw ure;
  }

  inited = true;
}

long udp_receiver::get_length( ) {

  return len;
}

string udp_receiver::get_last_pack_sender_ip( ) {

  struct sockaddr_in tmp_sock_addr;

  memcpy ( &tmp_sock_addr, &client_addr, sizeof ( struct sockaddr_in ) );

  return ( inet_ntoa( tmp_sock_addr.sin_addr ) );
}

udp_receiver::~udp_receiver() {

  close(socket_num);
}
