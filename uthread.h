/*-------------------------------------------------------------------------
 *	
 *   FILE
 *	uthread.h
 *
 *   AUTHOR	
 * 	Pavel Nikulcihkov <nikulchikov@mail.ru> - mr
 *
 *   DATE
 *	02/10/2007
 *
 *   CHANGES
 *
 *-------------------------------------------------------------------------
 */

#ifndef UTHREAD
#define UTHREAD

#include <pthread.h>

/**
 *      Class "uthread" provides functionality for
 *      creation, starting and stoping you own threads of you classes
 *      "static void *" member functions
 */
class uthread {

  bool ran;
  pthread_t *th;
  pthread_attr_t *attr;
  void *( *thr_func) ( void *);
  void *param;

  protected:

    pthread_mutex_t mutex;

  public:

    uthread( void *( *thr_func_init ) ( void * ), void *param);

    void start( );
    void stop( );

    ~uthread( );
};

#endif
