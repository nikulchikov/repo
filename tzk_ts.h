/*-------------------------------------------------------------------------
 *
 *   FILE
 *     tzkts.h
 *
 *   AUTHOR
 *     Pavel Nikulcihkov <nikulchikov@mail.ru> - mr
 *
 *   DATE
 *     06/03/2014
 *
 *   CHANGES
 *
 *-------------------------------------------------------------------------
 */

#ifndef TZKTS
#define TZKTS

#include "kasdu.h"

#include <vector>
#include <string>

using std::vector;
using std::string;

/**
 *      Class tzk_ts - для обработки информации ТЗК ТС
 *
 */
class tzk_ts {

  char *buff, ts_byte;

  float analog_value;

  static const char one = 1;

  public:

    tzk_ts( char *pack);

    string get_name( );

    short  get_signal( short group, short impl);
    float  get_analog( short group);
};

#endif
