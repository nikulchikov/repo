
#include "ts_listener.h"
#include "pgdatabase.h"
#include "tzk_ts.h"

#include <unistd.h>

#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

ts_listener::ts_listener( string db_host, string db_name, string db_user, short line, message_sndr *messendger)

  : udp_receiver( 14451) {

  this->db_host = db_host;
  this->db_name = db_name;
  this->db_user = db_user;

  char query[ 1024];

  pgdatabase *database = new pgdatabase( db_host, db_name, db_user);
  try {

    database->activate_connection( );

    /// init channels
    sprintf( query, "SELECT * FROM channels WHERE line = %d", line);
    database->exec_tuples_ok( query);
    if( !database->tuples( )) {

      cerr << " There is not found any TS info. Programm stoped." << endl;
      return;
    }

    for( short i = 0; i < database->tuples( ); i++)

      channels.push_back( new channel( database->get_value( i, "name"),
                                       database->get_long_value( i, "type"),
                                       database->get_long_value( i, "id")));
    /// init impulses
    for( short i = 0; i < channels.size( ); i++) {

      sprintf( query, "SELECT * FROM imps WHERE id_channel = %d", channels[ i]->get_id( ));
      database->exec_tuples_ok( query);
      if( !database->tuples( )) {

        cerr << " There is not found any impulces in channel. Programm stoped." << endl;
        return;
      }

      for( short j = 0; j < database->tuples( ); j++)

        channels[ i]->push_back( new impulse( database->get_long_value( j, "id"), database->get_value( j, "name"), database->get_long_value( j, "group_num"),
                                              database->get_long_value( j, "imp_num"), database->get_bool_value( j, "invertion")));
    }

    /// init nodes
    sprintf( query, "SELECT * FROM nodes WHERE line = %d", line);
    database->exec_tuples_ok( query);
    if( !database->tuples( )) {

      cerr << " There is not found any TS info. Programm stoped." << endl;
      return;
    }

    for( short i = 0; i < database->tuples( ); i++)
      nodes.push_back( new node( database->get_long_value( i, "id"), database->get_value( i, "name"), database->get_long_value( i, "way"), messendger));

    /// set nodes links
    for( short i = 0; i < database->tuples( ); i++) {

      /// find src node
      node *node_src_ptr = find_node( database->get_long_value( i, "id"));
      if( !node_src_ptr) {

        cerr << "Node id = " << database->get_long_value( i, "id") << " not found" << endl;
        continue;
      }

      node_src_ptr->set_right_node( find_node( database->get_long_value( i, "id_righter_node")));
      node_src_ptr->set_left_node( find_node( database->get_long_value( i, "id_lefter_node")));

      node_src_ptr->set_right_plus_node( find_node( database->get_long_value( i, "id_righter_plus_node")));
      node_src_ptr->set_left_plus_node( find_node( database->get_long_value( i, "id_lefter_minus_node")));

      node_src_ptr->set_right_minus_node( find_node( database->get_long_value( i, "id_righter_minus_node")));
      node_src_ptr->set_left_minus_node( find_node( database->get_long_value( i, "id_lefter_minus_node")));

      /// link nodes and impulses
      impulse *imp = find_impulse( database->get_long_value( i, "id_ts0_imp"));
      if( imp)
        imp->add_node_imps_pair( impulse::ImpulseTypeTS0, node_src_ptr);

      imp = find_impulse( database->get_long_value( i, "id_right_plus_imp"));
      if( imp)
        imp->add_node_imps_pair( impulse::ImpulseRightPlus, node_src_ptr);

      imp = find_impulse( database->get_long_value( i, "id_left_plus_imp"));
      if( imp)
        imp->add_node_imps_pair( impulse::ImpulseLeftPlus, node_src_ptr);

      imp = find_impulse( database->get_long_value( i, "id_right_minus_imp"));
      if( imp)
        imp->add_node_imps_pair( impulse::ImpulseRightMinus, node_src_ptr);

      imp = find_impulse( database->get_long_value( i, "id_left_minus_imp"));
      if( imp)
        imp->add_node_imps_pair( impulse::ImpulseLeftMinus, node_src_ptr);
    }
  }
  catch(...) {

    cerr << " Could'not connect to DB: " << db_name << " at: " << db_host << " user name:" << db_user << endl;
    return;
  }
  delete database;
}

void ts_listener::parce_pack( ) {

  tzk_ts tzk( buff);

  /// find channel
  channel *c = 0;
  for( short i = 0; i < channels.size( ); i++)

    if( channels[ i]->get_name( ) == tzk.get_name( )) {

      c = channels[ i];
      break;
    }

  /// this channel we are not interesting in
  if( c == 0)
    return;

  /// find changing imps
  for( short i = 0; i < c->size( ); i++) {

    impulse *impl = ( *c)[ i];

    short old_value = impl->get_value( );
    short new_value = tzk.get_signal( impl->get_group( ), impl->get_impulse( ));

    if( old_value == new_value)
      continue;

    /// set new value to nodes
    impl->set_value( new_value);
  }
}

void ts_listener::wait( ) {

  *this >> buff;

  parce_pack( );
}

impulse *ts_listener::find_impulse( long id) {

  if( !id)
    return 0;

  for( short i = 0; i < channels.size( ); i++)

    for( short j = 0; j < channels[ i]->size( ); j++)

      if( ( *channels[ i]) [ j]->get_id( ) == id)

        return ( *channels[ i]) [ j];

  return 0;
}

node *ts_listener::find_node( long id) {

  if( !id)
    return 0;

  for( short i = 0; i < nodes.size( ); i++)

    if( nodes[ i]->get_id( ) == id)

      return nodes[ i];

  return 0;
}

ts_listener::~ts_listener( ) {
}
