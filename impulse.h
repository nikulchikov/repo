/*-------------------------------------------------------------------------
 *
 *   FILE
 *     impulse.h
 *
 *   AUTHOR
 *     Pavel Nikulcihkov <nikulchikov@mail.ru> - mr
 *
 *   DATE
 *     30/06/2014
 *
 *   CHANGES
 *
 *-------------------------------------------------------------------------
 */

#ifndef IMPULSE_H
#define IMPULSE_H

#include <vector>
#include <string>

#include "node.h"

using std::vector;
using std::pair;
using std::string;

/**
 *      Class impulse - хранит информацию о ожидаемых импульсах ТЗК ТС и указатели
 *   на объекты классов node
 */
class impulse {

  unsigned long id;
  short group_num, imp_num;
  string name;
  bool inversion;

  short last_value; // -1 - not defined( default), 0 - false, 1 - true

  /// vector of nodes interesting in this impulse and type of this imp in this node
  vector< pair< short, node *> > nodes_imps;

  void init( unsigned long id, string name, short group, short imp, bool inversion);

  public:

    static const short ImpulseTypeTS0    = 0;
    static const short ImpulseRightPlus  = 1;
    static const short ImpulseRightMinus = 2;
    static const short ImpulseLeftPlus   = 3;
    static const short ImpulseLeftMinus  = 4;

    impulse( unsigned long id, string name, short group, short imp, bool inversion = false);
    impulse( const impulse &e);
    impulse &operator=( const impulse &e);

    unsigned long get_id( );
    string get_name( );
    short get_group( );
    short get_impulse( );
    bool is_inverse( );  /// инверсный бит

    void add_node_imps_pair( short t, node *n);

    void set_value( short lv);
    short get_value( );
};

#endif
