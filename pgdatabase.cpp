

#include <iostream>
using std::cerr;
using std::endl;

#include <string.h>
#include <stdlib.h>

#include "pgdatabase.h"

pgdatabase::connection_bad::connection_bad ( ) {

  connection_string = 0;
}

void pgdatabase::connection_bad::set_connection_string( const char *cs ) {

  connection_string = new char [ 255];
  strcpy( connection_string, cs);
}

char *pgdatabase::connection_bad::get_connection_string( ) {

  return connection_string;
}

pgdatabase::connection_bad::~connection_bad ( ) throw ( ) {

  if( connection_string )
    delete []connection_string;
}

pgdatabase::failed_exec_query::failed_exec_query( ) {
}

void pgdatabase::failed_exec_query::set_query( string info) {

  this->query = info;
}

string pgdatabase::failed_exec_query::get_query( ) {

  return query;
}

pgdatabase::failed_exec_query::~failed_exec_query( ) throw ( ) {
}

pgdatabase::pgdatabase( string host, string db, string user) {

  sprintf( this->connection_string,
           "host=%s\ndbname=%s\nuser=%s",
           host.c_str( ), db.c_str( ), user.c_str( ));

  _connection  = 0;
  _transaction = 0;
  _result      = 0;
}

pgdatabase::pgdatabase( string connection_string) {

  strcpy( this->connection_string, connection_string.c_str( ));

  _connection  = 0; 
  _transaction = 0;
  _result      = 0;
}

pgdatabase::pgdatabase( const char *connection_string) {

  strcpy( this->connection_string, connection_string);

  _connection  = 0;
  _transaction = 0;
  _result      = 0;
}

void pgdatabase::activate_connection( ) throw ( connection_bad ) {

  try {

    _connection = new connection( connection_string);
  }
  catch ( const std::exception &e) {

    cbex.set_connection_string( connection_string);
    throw cbex;
  }
}

void pgdatabase::exec_tupl( ) throw( failed_exec_query) {

  if( _transaction) {

    delete _transaction;
    _transaction = 0;
  }

  if( _result) {

    delete _result;
    _result = 0;
  }

  try {

    _transaction = new transaction<>( *_connection);

    _result = new result( _transaction->exec( query.c_str( )));

    _transaction->commit( );
  }
  catch( const std::exception &e) {

    feq.set_query( query.c_str( ));

    cerr << e.what( );

    throw feq;
  }
}

void pgdatabase::exec_comm( ) throw ( failed_exec_query) {

  if( _transaction ) {

    delete _transaction;
    _transaction = 0;
  }

  try {

    _transaction = new transaction<>( *_connection);
    _transaction->exec( query.c_str( ));
    _transaction->commit( );
  }
  catch( const std::exception &e) {

    feq.set_query( query.c_str( ));
    throw feq;
  }
}

void pgdatabase::exec_command_ok_simple( const char *_query) {

  try {

    _transaction->exec( _query);
    _transaction->commit( );
  }
  catch( const std::exception &e) {

    feq.set_query( query.c_str( ));
    throw feq;
  }
}

void pgdatabase::start_transaction( ) {

  if( _transaction ) {

    delete _transaction;
    _transaction = 0;
  }

  _transaction = new transaction<>( *_connection);
}

void pgdatabase::commit_transaction( ) {

  _transaction->commit( );
}

void pgdatabase::exec_tuples_ok( string _query ) {

  this->query = _query;

  exec_tupl( );
}

void pgdatabase::exec_tuples_ok( const char *_query ) {

  this->query.assign( _query );

  exec_tupl( );
}

void pgdatabase::exec_command_ok( string _query ) {

  this->query = _query;

  exec_comm( );
}

void pgdatabase::exec_command_ok( const char *_query ) {

  this->query.assign( _query );

  exec_comm( );
}

long pgdatabase::tuples( ) throw ( failed_exec_query ) {

  try {

    if( _result )

      return _result->size( );
  }
  catch( const std::exception &e ) {

    throw feq;
  }
  return -1;
}

string pgdatabase::get_value( long number, const char *name ) throw ( failed_exec_query ) {

  try {

    string value;
    (*_result)[ number][ name].to( value);
    return value.c_str( );
  }
  catch( const std::exception &e ) {

    throw feq;
  }
}

const long pgdatabase::get_long_value( long number,
                                       const char *name ) throw ( failed_exec_query ) {
  try {

    string value;
    (*_result)[ number][ name].to( value);
    return atol( value.c_str( ));
  }
  catch( const std::exception &e ) {

    throw feq;
  }
}

const bool pgdatabase::get_bool_value( long number,
                                       const char *name ) throw ( failed_exec_query) {
  try {

    string value;
    (*_result)[ number][ name].to( value);
    return ( value=="t");
  }
  catch( const std::exception &e ) {

    throw feq;
  }
}

char *pgdatabase::get_connection_string( ) {

  return connection_string;
}

void pgdatabase::close_connection( ) {

  if( _result ) {

    delete _result;
    _result      = 0;
  }

  if( _transaction ) {

    delete _transaction;
    _transaction = 0;
  }

  if( _connection ) {

    delete _connection;
    _connection  = 0;
  }
}

pgdatabase::~pgdatabase( ) {

  close_connection( );
}
