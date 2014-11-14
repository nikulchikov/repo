#include "kasdu.h"
#include "tzk_ts.h"

#include <string.h>

#include <iostream>
using std::cerr;
using std::endl;

tzk_ts::tzk_ts( char *pack) {

  buff = pack;
}

string tzk_ts::get_name( ) {

  string channel_name( buff + sizeof( PacketHead) - 1);
  return channel_name;
}

short tzk_ts::get_signal( short group, short impl) {

  string channel_name( buff + sizeof( PacketHead) - 1);
  short  buff_head_size = sizeof( PacketHead) + channel_name.size( ) + 1 + sizeof( short) * 2;

  memcpy( &ts_byte, ( buff + buff_head_size + ( group - 1) * 2 - 1), 1);

  ts_byte >>= ( impl - 1);
  ts_byte &= one;

  return ( short) ts_byte;
}

float tzk_ts::get_analog( short group) {

  string channel_name( buff + sizeof( PacketHead) - 1);
  short  buff_head_size = sizeof( PacketHead) + channel_name.size( ) + sizeof( short) * 2;

  memcpy( &analog_value, ( buff + buff_head_size + ( group - 1) * 4), 4);

  return analog_value;
}
