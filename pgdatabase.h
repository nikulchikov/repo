/*-------------------------------------------------------------------------
 *	
 *   FILE
 *	pgdatabase.h
 *
 *   AUTHOR
 * 	Pavel Nikulcihkov <nikulchikov@mail.ru> - mr
 *
 *   DATE
 *	25/10/2007
 *
 *   CHANGES
 *
 *-------------------------------------------------------------------------
 */

#ifndef PGDATABASE
#define PGDATABASE

//#include <pqxx/all.h>
#include <pqxx/pqxx>
using namespace pqxx;

using std::string;

class pgdatabase {

  char connection_string[ 255];

  connection    *_connection;
  transaction<> *_transaction;
  result        *_result;

  public:  /// exceptions

    class connection_bad : public std::exception {

      char *connection_string;

      public:

        connection_bad ( );

        virtual ~connection_bad ( ) throw ( ); 

        void set_connection_string( const char *cs );

        char *get_connection_string( );

    } cbex;

    class failed_exec_query : public std::exception {

      string query;

      public:

        failed_exec_query ( );

        virtual ~failed_exec_query ( ) throw ( );

        void set_query( string info );

        string get_query( );

    } feq;

  private:

    string query;

    void exec_tupl( ) throw ( failed_exec_query );
    void exec_comm( ) throw ( failed_exec_query );

  public:

    pgdatabase( string host, string db, string user );
    pgdatabase( string connection_string );
    pgdatabase( const char *connection_string );

    void exec_tuples_ok  ( string _query );
    void exec_tuples_ok  ( const char *_query );

    void exec_command_ok ( string _query );
    void exec_command_ok ( const char *_query);

    /// выполнение запроса без старта и завершения транзакции
    void exec_command_ok_simple( const char *_query);

    long tuples( ) throw ( failed_exec_query );

    string get_value( long number, const char *name ) throw ( failed_exec_query );

    const long get_long_value( long number, const char *name ) throw ( failed_exec_query );

    const bool get_bool_value( long number, const char *name ) throw ( failed_exec_query );

    char *get_connection_string( );

    void activate_connection( ) throw ( connection_bad );

    /// начать транзакцию
    void start_transaction( );

    /// подтвердить транзакцию
    void commit_transaction( );

    void close_connection( );

    ~pgdatabase( );
};

#endif
