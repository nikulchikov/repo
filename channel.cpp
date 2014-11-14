#include "channel.h"

#include <iostream>
using std::cerr;
using std::endl;

channel::channel( string name, short type, short id) {

  this->name = name;
  this->type = type;
  this->id   = id;
  clear( );
}

channel::channel( const channel &e) {

  this->name = e.name;
  this->type = e.type;
  this->id   = e.id;

  for( short i = 0; i < e.size( ); i++)
    this->push_back( e[ i]);
}

channel &channel::operator=( const channel &e) {

  this->name = e.name;
  this->type = e.type;
  this->id   = e.id;

  for( short i = 0; i < e.size( ); i++)
    this->push_back( e[ i]);
}

string channel::get_name( ) {

  return name;
}

short channel::get_id( ) {

  return id;
}
