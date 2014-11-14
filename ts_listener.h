/*-------------------------------------------------------------------------
 *
 *   FILE
 *     ts_listener.h
 *
 *   AUTHOR
 *     Pavel Nikulcihkov <nikulchikov@mail.ru> - mr
 *
 *   DATE
 *     17/01/2014
 *
 *   CHANGES
 *
 *-------------------------------------------------------------------------
 */

#ifndef TS_LISTENER
#define TS_LISTENER

#include "message_sndr.h"
#include "channel.h"
#include "udp_receiver.h"
#include "uthread.h"

/**
 *      Class ts_listener - слушает ТС
 */
class ts_listener: public udp_receiver {

  string db_host, db_name, db_user;

  vector< channel *> channels;
  vector< node*> nodes;

  char buff[ 256];

  node    *find_node( long id);
  impulse *find_impulse( long id);

  public:

    ts_listener( string db_host, string db_name, string db_user, short line, message_sndr *messendger);

    void wait( );
    void parce_pack( );

    ~ts_listener( );
};

#endif
