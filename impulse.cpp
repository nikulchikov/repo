#include "impulse.h"

#include <iostream>
using std::cerr;
using std::endl;

void impulse::init( unsigned long _id, string _name, short _group, short _imp, bool _inversion) {

  this->id        = _id;
  this->name      = _name;
  this->group_num = _group;
  this->imp_num   = _imp;
  this->inversion = _inversion;
}

impulse::impulse( unsigned long _id, string _name, short _group, short _imp, bool _inversion) {

  init( _id, _name, _group, _imp, _inversion);

  nodes_imps.clear( );

  last_value = -1;
}

impulse::impulse( const impulse &e) {

  init( e.id, e.name, e.group_num, e.imp_num, e.inversion);

  for( short i = 0; i < e.nodes_imps.size( ); i++)
    this->nodes_imps.push_back( pair< short, node*> ( e.nodes_imps[ i].first, e.nodes_imps[ i].second));
}

impulse &impulse::operator=( const impulse &e) {

  init( e.id, e.name, e.group_num, e.imp_num, e.inversion);

  for( short i = 0; i < e.nodes_imps.size( ); i++)
    this->nodes_imps.push_back( pair< short, node*> ( e.nodes_imps[ i].first, e.nodes_imps[ i].second));
}

void impulse::add_node_imps_pair( short t, node *n) {

  nodes_imps.push_back( pair< short, node *> ( t, n));

//for( short i = 0; i < nodes_imps.size( ); i++)
//  cerr << "Imp: " << name << " has node_type: " << nodes_imps[ i].first << "  and node: " << nodes_imps[ i].second->get_name( ) << endl;
}

void impulse::set_value( short lv) {

  if( last_value != -1 && lv==1)

    for( short i = 0; i < nodes_imps.size( ); i++)

      switch( nodes_imps[ i].first) {

        case ImpulseTypeTS0:
          nodes_imps[ i].second->set_tS0( );
          break;

        case ImpulseRightPlus:
          nodes_imps[ i].second->set_right_plus( );
          break;

        case ImpulseRightMinus:
          nodes_imps[ i].second->set_right_minus( );
          break;

        case ImpulseLeftPlus:
          nodes_imps[ i].second->set_left_plus( );
          break;

        case ImpulseLeftMinus:
          nodes_imps[ i].second->set_left_minus( );
          break;
      }

  last_value = lv;
}

short impulse::get_value( ) {

  return last_value;
}

unsigned long impulse::get_id( ) {

  return id;
}

string impulse::get_name( ) {

  return name;
}

short impulse::get_group( ) {

  return group_num;
}

short impulse::get_impulse( ) {

  return imp_num;
}

bool impulse::is_inverse( ) {

  return inversion;
}
