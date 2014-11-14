#include "node.h"

#include <iostream>
using std::cerr;
using std::endl;

void node::init( unsigned long id, string name, short w, unsigned long srn, node *right_node, node *left_node,
                 node *right_plus_node, node *right_minus_node, node *left_plus_node, node *left_minus_node, message_sndr *msgr) {

  this->id  = id;
  this->srn = srn;
  this->way = w;

  this->name = name;

  this->station = 0;

  short np = name.find( "n", 0);
  if( np != std::string::npos)
    this->station = atoi( name.substr( np + 1, name.length( ) - 1).c_str( ));

  this->right_node = right_node;
  this->left_node  = left_node;

  this->right_plus_node  = right_plus_node;
  this->left_plus_node   = left_plus_node;

  this->right_minus_node = right_minus_node;
  this->left_minus_node  = left_minus_node;

  this->sndr = msgr;
}

node::node( unsigned long id, string name, short w, message_sndr *msgr) {

  init( id, name, w, 0, 0, 0, 0, 0, 0, 0, msgr);

  latest_busy_time  = 0;
  new_busy_interval = 15;
  search_deep       = 3;
}

node::node( const node &e) {

  init( e.id, e.name, e.way, e.srn, e.right_node, e.left_node, e.right_plus_node, e.right_minus_node, e.left_plus_node, e.left_minus_node, e.sndr);

  latest_busy_time  = e.latest_busy_time;
  new_busy_interval = e.new_busy_interval;
  search_deep       = e.search_deep;
}

node &node::operator=( const node &e) {

  init( e.id, e.name, e.way, e.srn, e.right_node, e.left_node, e.right_plus_node, e.right_minus_node, e.left_plus_node, e.left_minus_node, e.sndr);

  latest_busy_time  = e.latest_busy_time;
  new_busy_interval = e.new_busy_interval;
  search_deep       = e.search_deep;
}

bool node::operator==( short id) {

  return ( this->id == id);
}

string node::get_name( ) {

  return name;
}

unsigned long node::get_id( ) {

  return id;
}

unsigned long node::check_srn( ) {

  return srn;
}

unsigned long node::take_srn( short direction) {

  if( station)
    sndr->send( time( 0), srn, way, station, direction, Departed);

  unsigned long retval = srn;
  srn = 0;
  return retval;
}

/// получение номера поезда
void node::set_tS0( ) {

  long curr_time = time( 0);

  /// проверка слишком частого повторного занятия - дребезг контактов и прочее отфильтруем
  if( srn && ( curr_time - latest_busy_time) < new_busy_interval)
    return;

  short deep = search_deep;
  if( !right_node || !left_node)
    deep = 2;

  short direction = -1;

  long event_time_left, event_time_right;
  long src_node_event_time = 0;

  node *temp_left_node  = left_node;
  node *temp_right_node = right_node;
  node *srn_src_node = 0;

  for( short i = 0; i < deep; i++) {

    if( temp_right_node && temp_right_node->check_srn( ) &&
        temp_right_node->get_latest_busy_time( ) > ( src_node_event_time + PriorityTime * i)) {

      src_node_event_time = temp_right_node->get_latest_busy_time( );
      srn_src_node = temp_right_node;
      direction = EvenDirection;

      if( way == 2)
        src_node_event_time += RightWayPriority;
    }

    if( temp_left_node && temp_left_node->check_srn( ) &&
        temp_left_node->get_latest_busy_time( ) > ( src_node_event_time + PriorityTime * i)) {

      src_node_event_time = temp_left_node->get_latest_busy_time( );
      srn_src_node = temp_left_node;
      direction = OddDirection;

      if( way == 1)
        src_node_event_time += RightWayPriority;
    }

    if( temp_left_node)
      temp_left_node  = left_node->get_lefter( );

    if( temp_right_node)
      temp_right_node = right_node->get_righter( );
  }

  if( srn_src_node)
    srn = srn_src_node->take_srn( direction);

  latest_busy_time = curr_time;

  if( station)
    sndr->send( curr_time, srn, way, station, direction, Arrived);
}

void node::set_right_plus( ) {

  if( right_plus_node)
    right_node = right_plus_node;
}

void node::set_left_plus( ) {

  if( left_plus_node)
    left_node = left_plus_node;
}

void node::set_right_minus( ) {

  if( right_minus_node)
    right_node = right_minus_node;
}

void node::set_left_minus( ) {

  if( left_minus_node)
    left_node = left_minus_node;
}

void node::set_right_node( node *n) {

  right_node = n;
}

void node::set_left_node( node *n) {

  left_node = n;
}

void node::set_right_plus_node( node *n) {

  right_plus_node = n;
}

void node::set_left_plus_node( node *n) {

  left_plus_node = n;

//if( n)
//  cerr << "Node: " << name << " lefter plus node " << n->get_name( ) << endl;
}

node *node::get_lefter( ) {

  return left_node;
}

node *node::get_righter( ) {

  return right_node;
}

void node::set_right_minus_node( node *n) {

  right_minus_node = n;
}

void node::set_left_minus_node( node *n) {

  left_minus_node = n;
}

void node::set_new_busy_interval( short nby) {

  new_busy_interval = nby;
}

void node::set_search_deep( short sd) {

  search_deep = sd;
}

long node::get_latest_busy_time( ) {

  return latest_busy_time;
}
