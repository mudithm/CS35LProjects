#include "randlib.h"
#include <stdlib.h>
#include <stdio.h>

/* Software implementation.  */

/* Input stream containing random bytes.  */
static FILE *urandstream;

/* Initialize the software rand64 implementation.  */
// added constructor attribute
static void __attribute__((constructor))
software_rand64_init (void) 
{
  urandstream = fopen ("/dev/urandom", "r");
  if (! urandstream)
    abort ();
}

/* Return a random value, using software operations.  */
static unsigned long long
software_rand64 (void)
{
  unsigned long long int x;
  if (fread (&x, sizeof x, 1, urandstream) != 1)
    abort ();
  return x;
}

/* Finalize the software rand64 implementation.  */
// added destructor attribute
static void __attribute__((destructor))
software_rand64_fini (void)
{
  fclose (urandstream);
}

// implementation of the "randlib.h" interface
extern unsigned long long rand64 (void)
{
  return software_rand64();
}
