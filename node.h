/*-------------------------------------------------------------------------
 *
 *   FILE
 *     node.h
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

#ifndef NODE_H
#define NODE_H

#include "message_sndr.h"

#include <vector>
#include <string>

using std::vector;
using std::string;

/**
 *      Класс node - хранит информацию об объектах РЦ и блок-участков. Содержит текущий системный номер поезда. Ведёт ИГ
 *
 */
class node {

  static const short PriorityTime     = 300;  /// seconds
  static const short RightWayPriority = 1580; /// seconds

  static const short EvenDirection = 0;
  static const short OddDirection  = 1;

  static const short Arrived  = 0;
  static const short Departed = 1;

  message_sndr *sndr;

  long latest_busy_time;

  short station, way;

  short new_busy_interval, search_deep;

  unsigned long id, srn;

  string name;

  node *right_node, *left_node, *right_plus_node, *right_minus_node, *left_plus_node, *left_minus_node;

  void init( unsigned long id, string name, short w, unsigned long srn, node *right_node, node *left_node,
             node *right_plus_node, node *right_minus_node, node *left_plus_node, node *left_minus_node, message_sndr *sndr);
  public:

    node( unsigned long id, string name, short w, message_sndr *s);
    node( const node &e);
    node &operator=( const node &e);
    bool operator==( short id);

    void set_right_node( node *n);
    void set_left_node( node *n);

    void set_right_plus_node( node *n);
    void set_left_plus_node( node *n);

    void set_right_minus_node( node *n);
    void set_left_minus_node( node *n);

    node *get_lefter( );
    node *get_righter( );

    void set_new_busy_interval( short nby);
    void set_search_deep( short sd);

    string get_name( );

    unsigned long get_id( );

    unsigned long check_srn( );
    unsigned long take_srn( short direction);

    void set_tS0( );

    void set_right_plus( );
    void set_left_plus( );

    void set_right_minus( );
    void set_left_minus( );

    long get_latest_busy_time( );
};

#endif
