#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//function to compare chars in from array
int cmpChars(const void * a, const void * b)
{
  return ( *(char*)a - *(char*)b );

}



int main(int argc, char *argv[])
{
  // Variable declarations
  char *fromArray;
  int diff, c, i = 0;


  // Checks that there are two arguments
  if (! (argc == 3 || argc == 1))
  {
    fprintf(stderr, "Wrong number of operands: %d\n", argc);
    exit(1);
  }


  //if no arguments are passed, output stdin to stdout
  if (argc == 1)
    {
      while (! feof(stdin) && ! ferror(stdin))
	{
	  c = getchar();
	  if (ferror(stdin))
	    {
	      fprintf(stderr, "Input error!");
	      exit(1);
	    }
	  if (feof(stdin))
	    break;
	  if (putchar(c) == EOF)
	    {
	      fprintf(stderr, "Output Error!");
	      exit(1);
	    }
	}
    
      
      return 0;
    }

  
  //checks that the arguments are the same length
  if (strlen(argv[1]) != strlen(argv[2]))
  {
    fprintf(stderr, "Argument strings are not the same length\n");
    exit(1);
  }

  fromArray = malloc(1 * strlen(argv[1]));
  if (fromArray == NULL)
    {
      free(fromArray);
      fprintf(stderr, "Memory Allocation Error");
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
	  fprintf(stderr, "Duplicate character in the from array\n");
	  exit(1);
	}
      i++;
    }

  free(fromArray);


  //performs the transformation
  while (! feof(stdin) && ! ferror(stdin))
    {
      c = getchar();
      if (ferror(stdin))
	{
	  fprintf(stderr, "Input error!");
	  exit(1);
	}
      if (feof(stdin))
	  break;
      if (strchr(argv[1], c) != NULL)
	{
	  diff = strchr(argv[1], c) - argv[1];
	  if (putchar(argv[2][diff]) == EOF)
	    {
	      fprintf(stderr, "Output Error!");
	      exit(1);
	    }
	  
	}
      else
	{
	  if (putchar(c) == EOF)
	    {
	      fprintf(stderr, "Output Error!");
	      exit(1);
	    }
	}
    }

  
}
