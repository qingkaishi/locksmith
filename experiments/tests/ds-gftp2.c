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

// Declare existential quantifications
#pragma existential(gftp_transfer,"gftp_transfer.statmutex","gftp_transfer.structmutex")
#pragma existential(gftp_transfer,"&gftp_transfer.fromreq","&gftp_transfer.numfiles")
#pragma existential(gftp_transfer,"&gftp_transfer.started","&gftp_transfer.done")
#pragma existential(gftp_transfer,"&gftp_transfer.cancel","&gftp_transfer.ready")
#pragma existential(gftp_transfer,"&gftp_transfer.fromreq->cancel","&gftp_transfer.fromreq->stopable")
#pragma existential(gftp_transfer,"&gftp_transfer.fromreq->protocol_data")

struct gftp_request 
{
  unsigned int cancel : 1,
               stopable : 1;
  void *protocol_data;
};

struct gftp_transfer
{
  struct gftp_request * fromreq;
  unsigned int started : 1,
               cancel : 1,
               ready : 1,
               done : 1;
  int numfiles;
  pthread_mutex_t statmutex,  structmutex;
};

struct gftp_transfer __attribute__((packed)) * __attribute__((unique))
gftp_tdata_new (void)
{
  struct gftp_transfer __attribute__((packed)) * tdata;
  tdata = malloc (sizeof (struct gftp_transfer));
  pthread_mutex_init (&tdata->statmutex, NULL);
  pthread_mutex_init (&tdata->structmutex, NULL);
  return tdata;
}

static void
cancel_get_trans_password (struct gftp_transfer * tdata)
{
  start_unpack(tdata);
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
  end_unpack(tdata);
}

static void
update_file_status (struct gftp_transfer * tdata)
{
  int n;
  start_unpack(tdata);
  pthread_mutex_lock (&tdata->statmutex);
  n = tdata->numfiles;

  if (n < 1)
    {
      pthread_mutex_unlock (&tdata->statmutex);
      return;
    }

  tdata->numfiles = 5;
  pthread_mutex_unlock (&tdata->statmutex);
  end_unpack(tdata);
}


static int doit1(struct gftp_transfer *tdata) {
  cancel_get_trans_password(tdata);
  return 1;
}

static int doit2(struct gftp_transfer *tdata) {
  update_file_status(tdata);
  return 1;
}


int main() {
  int i = 1;
  pthread_t t1, t2;

  while (1) {
    struct gftp_transfer __attribute__((packed)) *tdata = gftp_tdata_new();
    tdata->numfiles = 1; // thread local at the moment
    struct gftp_transfer *pdata;
    pdata = pack(tdata);
    pthread_create(&t1, NULL, doit1, pdata);
    pthread_create(&t2, NULL, doit2, pdata);
  }
}


