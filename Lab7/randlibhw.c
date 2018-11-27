#include "randlib.h"
#include <immintrin.h>

// Initialization is no longer necessary for the hardware library
/*
static void
hardware_rand64_init (void)
{
}
*/

/* Return a random value, using hardware operations.  */
static unsigned long long
hardware_rand64 (void)
{
  unsigned long long int x;
  while (! _rdrand64_step (&x))
    continue;
  return x;
}

// Finalizing is no longer necessary for the hardware library
/*
static void
hardware_rand64_fini (void)
{
}
*/
// implementation of the "randlib.h" interface
extern unsigned long long rand64 (void)
{
  return hardware_rand64();
}
