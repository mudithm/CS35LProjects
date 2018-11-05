#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//comparison function between frobnicated char arrays
int frobcmp(char const * a, char const * b)
{
  char a2, b2;
  while (*a != ' ' && *b != ' ')
  {
    a2 = *a^42;
    b2 = *b^42;
    if (a2 < b2)
      return -1;
    else if (a2 > b2)
      return 1;
    else
      {
	a++;
	b++;
	if (*a == ' ' && *b != ' ')
	  return 1;
	else if (*b == ' ' && *a != ' ')
	  return -1;
      }
  }
  return 0;
}

// Wrapper for the frobcmp function, so it can be used in qsort
int frobcmpWrapper(const void* a, const void* b)
{
  return frobcmp((*(const char**) a), (*(const char**) b));

}

// Print out the contents of a char string
void writeCharArray(const char* str)
{
  while (1)
    {
      if (putchar(*str) == EOF)
      {
        fprintf(stderr, "Output Error");
        exit(1);
      }

      if (*str++ == ' ')
	return;
    }
}


void checkInputError()
{
  if (ferror(stdin))
  {
    fprintf(stderr, "Input error!");
    exit(1);
  }
}




int main()
{
  // Initialize "string" variable, index pointer, and size
  char *readChar, *inputString = malloc(100);
  char **arrayToSortEQ, **arrayToSort = malloc(100 * sizeof(char*));
  long size = 0, arrSize = 0;
  int prevCharSpace = 0;
  long i = 0;
  // Traverse through stdin input and collect all chars into an array
  // including EXT characters
  
  while (! feof(stdin) && ! ferror(stdin))
    {
      readChar = inputString + size;
      *readChar = getchar();
      checkInputError();
      
      if (feof(stdin))
	       break;
      size++;
      if (size % 100 == 0)
      {
	       inputString = realloc(inputString, size + 100);
          if (inputString == NULL)
            {
              free(inputString);
              fprintf(stderr, "Memory allocation error");
              exit(1);
            }
      }
    }
  // If stdin is not empty and the last character is not a space, add a space
  if (size > 0)
    if (inputString[size-1] != ' ')
      {
      	inputString = realloc(inputString, size+1);
        if (inputString == NULL)
            {
              free(inputString);
              fprintf(stderr, "Memory allocation error");
              exit(1);
            }
      	inputString[size] = ' ';
      	size++;
      }
  
  // Add the individual space-separated strings to an array for sorting
  arrayToSort[0] = inputString;
  while (i < size)
    {
      if (inputString[i] == ' ' && !prevCharSpace)
    	{
    	  arrSize++;
    	  if (arrSize % 100 == 0)
    	    {
    	      arrayToSort = realloc(arrayToSort, (arrSize * sizeof(char*) + 100 * sizeof(char*)));
            if (arrayToSort == NULL)
            {
              free(arrayToSort);
              fprintf(stderr, "Memory allocation error");
              exit(1);
            }
    	    }
    	  arrayToSort[arrSize] = inputString + i + 1;
    	  prevCharSpace = 1;
    	}
      else
	     prevCharSpace = 0;
      i++;
    }

  // sort the array
  qsort(arrayToSort, arrSize, sizeof(char*), frobcmpWrapper);
   
  // print the output to standard output
   i = 0;
   while (i < arrSize)
     {
       writeCharArray(arrayToSort[i]);
       i++;
     }

   free(arrayToSort);
   free(inputString);

}

