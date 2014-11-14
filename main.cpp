
#include "ts_listener.h"

#include "message_sndr.h"

#include <stdlib.h>

#include <fstream>
#include <iostream>
using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;

int main( int argc, char **argv) {

  cout << endl << endl << " Low level granika component" << endl;

  if( argc < 7) {

    cerr << endl << endl << " Few params." << endl;
    cerr << " Using: " << argv[ 0] << " db_host db_name db_user line queue_msg_path queue_msg_id " << endl;
    return -1;
  }

  message_sndr messndgr( argv[ 5], atoi( argv[ 6]));

  ts_listener lstrn( argv[ 1], argv[ 2], argv[ 3], atoi( argv[ 4]), &messndgr);
  lstrn.wait( );

  return -1;
}
