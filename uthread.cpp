
#include "uthread.h"

uthread::uthread( void *( *thr_func_init ) ( void * ), void *param_init ) :

  thr_func( thr_func_init ),

  param( param_init ) {

  th = new pthread_t( );
  attr = new pthread_attr_t( );

  pthread_attr_setdetachstate( attr, PTHREAD_CREATE_DETACHED);
  pthread_mutex_unlock( &mutex);

  ran = false;
}

void uthread::start( ) {

  ran = true;
  pthread_create( th, attr, thr_func, param );
}

void uthread::stop( ) {

  pthread_cancel( *th );
  ran = false;
}

uthread::~uthread( ) {

  if( ran )
    pthread_cancel( *th );

  delete attr;
  delete th;
}

/* There is a simple test

#include <iostream>

using namespace std;

class q {

  public:
  
  static void *qqq( void *param );
};

void *q::qqq( void *param ) {
  
  cerr << "void *q::qqq( void *param ) " << endl;
}

int main(int argc, char** argv) {

  q qq;
  
  uthread t ( qq.qqq, 0 );
  
  t.start();
  
  while(1);
}
*/
