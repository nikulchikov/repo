/*-------------------------------------------------------------------------
 *
 *   FILE
 *     message_sndr.h
 *
 *   AUTHOR
 *     Pavel Nikulcihkov <nikulchikov@mail.ru> - mr
 *
 *   DATE
 *     08/07/2014
 *
 *   CHANGES
 *
 *-------------------------------------------------------------------------
 */

#ifndef MESSAGE_SNDR_H
#define MESSAGE_SNDR_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;

/**
 *      Class message_sndr - хранит информацию о messages queue and send messages to middleware
 */
class message_sndr {

  struct Message {

    long mtype;
    char buff[ 255];
  } in_message;

  int msgid;

  public:

    message_sndr( const char *path, int proj_id);
    message_sndr( const message_sndr &e);
    message_sndr &operator=( const message_sndr &e);

    void send( long time, long srn, short way, short station, short direction, short type);
};

#endif
