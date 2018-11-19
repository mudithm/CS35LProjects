#include <stdlib.h>
#include <unistd.h>
#include <string.h>




//function to compare chars in from array
int cmpChars(const void * a, const void * b)
{
  return ( *(char*)a - *(char*)b );

}



int main(int argc, char *argv[])
{
  // Variable declarations
  char *fromArray, c[1];
  int diff, currState, i = 0;


  // Checks that there are two arguments
  if (! (argc == 3 || argc == 1))
  {
    write(2, "Wrong number of operands", 25);
    exit(1);
  }


  // if no arguments are passed, write stdin to stdout
  if (argc == 1)
    {
      currState = read(0, c, 1);      
      while (currState > 0)
	{
	      if (write(1, c, 1) == -1)
		{
		  write(2, "Output Error!", 13);
		  exit(1);
		}
	  currState = read(0, c, 1);
	}
      return 0;

    }

  
  //checks that the arguments are the same length
  if (strlen(argv[1]) != strlen(argv[2]))
  {
    write(2, "Argument strings are not the same length\n", 43);
    exit(1);
  }

  fromArray = malloc(1 * strlen(argv[1]));
  if (fromArray == NULL)
    {
      free(fromArray);
      write(2, "Memory Allocation Error", 23);
      exit(1);
    }

  //sort the from array to check for duplicates
  strcpy(fromArray, argv[1]);
  qsort(fromArray, strlen(fromArray), 1, cmpChars);

  //check for duplicates in the from array
  while (i < strlen(fromArray) - 1)
    {
      if (fromArray[i] == fromArray[i+1])
	{
	  write(2, "Duplicate character in the from array\n", 39);
	  exit(1);
	}
      i++;
    }

  free(fromArray);

  currState = read(0, c, 1);
  
  //performs the transformation
  while (currState > 0)
    {

      if (strchr(argv[1], c[0]) != NULL)
	{
	  diff = strchr(argv[1], c[0]) - argv[1];
	  if (write(1, &argv[2][diff], 1) == -1)
	    {
	      write(2, "Output Error!", 13);
	      exit(1);
	    }
	  
	}
      else
	{
	  if (write(1, c, 1) == -1)
	    {
	      write(2, "Output Error!", 13);
	      exit(1);
	    }
	}

      currState = read(0, c, 1);
    }

  
}
