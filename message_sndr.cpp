#include "message_sndr.h"

message_sndr::message_sndr( const char *path, int proj_id) {

  in_message.mtype = 777;

  key_t key;

//  if( ( key = ftok("/tmp", 'G')) < 0) {
  if( ( key = ftok( path, proj_id)) < 0) {

    cerr  << "Failed create message queue! Key < 0!  key = " << key << endl;
    return;
  }

  if( ( msgid = msgget( key, IPC_CREAT | 0666)) < 0) {

    cerr  << "Failed create message queue!" << endl;
    switch( msgid) {

      case EACCES:
        cerr  << "EACCES" << endl;
        break;

      case EEXIST:
        cerr  << "EEXIST" << endl;
        break;

      case ENOENT:
        cerr  << "ENOENT" << endl;
        break;

      case ENOMEM:
        cerr  << "ENOMEM" << endl;
        break;

      case ENOSPC:
        cerr  << "ENOSPC" << endl;
        break;
    }
    return;
  }
}

message_sndr::message_sndr( const message_sndr &e) {

  in_message = e.in_message;
  msgid      = e.msgid;
}

message_sndr &message_sndr::operator=( const message_sndr &e) {

  in_message = e.in_message;
  msgid      = e.msgid;
}

void message_sndr::send( long time, long srn, short way, short station, short direction, short type) {

  sprintf( in_message.buff, "%d %d %d %d %d %d ", time, srn, way, station, direction, type);

  short n = msgsnd( msgid, ( void *) &in_message, strlen( in_message.buff), IPC_NOWAIT);
  if( n != 0)
    cerr << "Failed send message" << endl;
}
