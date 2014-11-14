/*-------------------------------------------------------------------------
 *
 *   FILE
 *     channel.h
 *
 *   AUTHOR
 *     Pavel Nikulcihkov <nikulchikov@mail.ru> - mr
 *
 *   DATE
 *     01/07/2014
 *
 *   CHANGES
 *
 *-------------------------------------------------------------------------
 */

#ifndef CHANNEL_H
#define CHANNEL_H

#include <vector>
#include <string>

#include "impulse.h"

using std::vector;
using std::pair;
using std::string;

/**
 *      Class channel - хранит информацию о канале ТС
 *
 */
class channel: public vector<impulse *> {

  string name;
  short type, id;

  public:

    static const short TypeKASDU = 0;
    static const short TypeSKC   = 1;

    channel( string name, short type, short id);
    channel( const channel &e);
    channel &operator=( const channel &e);

    string get_name( );
    short get_id( );
};

#endif
