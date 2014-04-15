/* MWH: This example is based on a quick run-through of gftp.  The
   actual program is pretty tricky because it uses gtk's event-based
   libraries to get things going.  Thus in the real program, functions
   are called from the GTK library, which we presumably don't have
   access to (or else we'll need to analyze it too).  The real structs
   are also more complicated.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct gftp_request_tag 
{
  unsigned int cancel : 1,
               stopable : 1;
  void *protocol_data;
} gftp_request;

typedef struct gftp_transfer_tag
{
  gftp_request * fromreq;
  unsigned int started : 1,
               cancel : 1,
               ready : 1,
               done : 1;
  int numfiles;
  pthread_mutex_t statmutex,  structmutex;
} gftp_transfer;

gftp_transfer *
gftp_tdata_new (void)
{
  gftp_transfer * tdata;
  tdata = malloc (sizeof (*tdata));
  pthread_mutex_init (&tdata->statmutex, NULL);
  pthread_mutex_init (&tdata->structmutex, NULL);
  return (tdata);
}

static void
cancel_get_trans_password (gftp_transfer * tdata)
{
  if (tdata->fromreq->stopable == 0)
    return;

  pthread_mutex_lock (&tdata->structmutex);
  if (tdata->started)
    {
      tdata->cancel = 1;
      tdata->fromreq->cancel = 1;
    }
  else
    tdata->done = 1;

  tdata->fromreq->stopable = 0;
  tdata->fromreq->protocol_data = NULL;
  pthread_mutex_unlock (&tdata->structmutex);
}

static void
update_file_status (gftp_transfer * tdata)
{
  int n;

  pthread_mutex_lock (&tdata->statmutex);
  n = tdata->numfiles;

  if (n < 1)
    {
      pthread_mutex_unlock (&tdata->statmutex);
      return;
    }

  tdata->numfiles = 5;
  pthread_mutex_unlock (&tdata->statmutex);
}


static int doit1(gftp_transfer *tdata) {
  cancel_get_trans_password(tdata);
  return 1;
}

static int doit2(gftp_transfer *tdata) {
  update_file_status(tdata);
  return 1;
}


int main() {
  int i = 1;
  pthread_t t1, t2;

  while (1) {
    gftp_transfer *tdata = gftp_tdata_new();
    tdata->numfiles = 1; // thread local at the moment

    pthread_create(&t1, NULL, doit1, tdata);
    pthread_create(&t2, NULL, doit2, tdata);
  }
}


