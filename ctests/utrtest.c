#include <stdio.h>
#include <stdlib.h>  /* exit */
#include <unistd.h>  /* getopt */
#include "../gptl.h"
#if ( defined HAVE_LIBMPI ) || ( defined HAVE_LIBMPICH )
#include <mpi.h>
#endif

int main (int argc, char **argv)
{
  int c;
  int papiopt;
  double sum = 0.;
  extern void sub (int, int, char *, double *);
  extern char *optarg;

#if ( defined HAVE_LIBMPI ) || ( defined HAVE_LIBMPICH )
  MPI_Init (&argc, &argv);
#endif

  printf ("Purpose: estimate overhead of GPTL\n");

  while ((c = getopt (argc, argv, "p:")) != -1) {
    switch (c) {
    case 'p':
      if ((papiopt = GPTL_PAPIname2id (optarg)) >= 0) {
	printf ("Failure from GPTL_PAPIname2id\n");
	exit (1);
      }
      if (GPTLsetoption (papiopt, 1) < 0) {
	printf ("Failure from GPTLsetoption (%s,1)\n", optarg);
	exit (1);
      }
      break;
    default:
      printf ("unknown option %c\n", c);
      exit (2);
    }
  }

  GPTLsetoption (GPTLabort_on_error, 0);

  GPTLsetutr (GPTLmpiwtime);
  GPTLsetutr (GPTLrtc);
  GPTLsetutr (GPTLnanotime);
  GPTLsetutr (GPTLclockgettime);
  GPTLsetutr (GPTLgettimeofday);
  GPTLsetutr (GPTLpapitime);

  GPTLinitialize ();

  GPTLstart ("total");
  /*  GPTLdisable (); */
  sub (1, 10000000, "1x1e7", &sum);
  sub (10, 1000000, "10x1e6", &sum);
  sub (100, 100000, "100x1e5", &sum);
  sub (1000, 10000, "1000x1e4", &sum);
  sub (10000, 1000, "1e4x1000", &sum);
  sub (100000, 100, "1e5x100", &sum);
  sub (1000000, 10, "1e6x10", &sum);
  sub (10000000, 1, "1e7x1", &sum);
  /*  GPTLenable (); */
  GPTLstop ("total");

  GPTLpr (0);
  return 0;
}

void sub (int outer, int inner, char *name, double *sum)
{
  int i, j;
  for (i = 0; i < outer; ++i) {
    GPTLstart (name);
    for (j = 0; j < inner; ++j)
      *sum += j;
    GPTLstop (name);
  }
}
